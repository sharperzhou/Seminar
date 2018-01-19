#include "stdafx.h"
#include "ArxProjectHelper.h"
#include "Jig.h"


AcDbObjectId CArxProjectHelper::createCircle(const AcGePoint3d &center, double radius,
    const ACHAR *layer, Adesk::UInt16 color)
{
    AcDbObjectId circleId, layerId;
    AcGeVector3d normal(0, 0, 1);
    AcDbCircle *pCircle = NULL;
    Acad::ErrorStatus es;

    do {
        if (!createLayer(layerId, layer)) {
            acutPrintf(_T("错误: 打开或创建图层 %s 失败\n"), layer);
            break;
        }

        pCircle = new AcDbCircle(center, normal, radius);
        if (!postToModelSpace(circleId, pCircle)) {
            acutPrintf(_T("错误: 绘制圆失败\n"));
            break;
        }

        es = pCircle->setColorIndex(color);
        es = pCircle->setLayer(layer);
    } while (false);

    if (pCircle) pCircle->close();

    return circleId;
}

bool CArxProjectHelper::getGroupName(AcStringArray &outputName)
{
    Acad::ErrorStatus es;
    AcDbDictionary *pDict = NULL;
    AcDbDictionaryIterator *pDictIter = NULL;

    outputName.removeAll();

    do {
        //获取组字典
        es = acdbHostApplicationServices()->workingDatabase()
            ->getGroupDictionary(pDict, AcDb::kForRead);
        if (Acad::eOk != es) break;

        //建立字典迭代器
        pDictIter = pDict->newIterator();
        if (!pDictIter) {
            es = Acad::eNullIterator;
            break;
        }

        //获取组名称
        for (; !pDictIter->done(); pDictIter->next()) {
            AcDbGroup *pGroup = NULL;
            if (Acad::eOk != pDictIter->getObject((AcDbObject*&) pGroup, AcDb::kForRead))
                continue;

            ACHAR *pBuf = NULL;
            if (Acad::eOk == pGroup->getName(pBuf)) {
                outputName.append(pBuf);
                acutDelString(pBuf);
            }

            if (pGroup) pGroup->close();
        }
    } while (false);

    if (pDict) pDict->close();
    if (pDictIter) delete pDictIter;

    return Acad::eOk == es;
}

bool CArxProjectHelper::getCurrentLayerName(AcString &outputName)
{
    AcDbObjectId clayerId = acdbHostApplicationServices()->workingDatabase()->clayer();
    AcDbLayerTableRecord *pCLayer = NULL;
    if (Acad::eOk != acdbOpenObject(pCLayer, clayerId, AcDb::kForRead))
        return false;

    pCLayer->getName(outputName);

    pCLayer->close();
    return true;
}

bool CArxProjectHelper::getBlockAttribute(CArray<BlockAttribute> &outputBlkAttr,
    AcDbObjectId &outputBlkId, const TCHAR *szBlkName)
{
    AcDbBlockTable *pBlkTbl = NULL;
    AcDbBlockTableRecord *pBlkTblRecord = NULL;
    AcDbBlockTableRecordIterator *pBlkTblRecordIter = NULL;
    Acad::ErrorStatus es;

    outputBlkAttr.RemoveAll();
    outputBlkId.setNull();

    do {
        //打开块表
        es = acdbHostApplicationServices()->workingDatabase()
            ->getBlockTable(pBlkTbl, AcDb::kForRead);
        if (Acad::eOk != es) break;

        //根据块表名称获取块表记录
        es = pBlkTbl->getAt(szBlkName, pBlkTblRecord, AcDb::kForRead);
        if (Acad::eOk != es) break;

        //获取块表Id
        outputBlkId = pBlkTblRecord->id();

        //检查该块表记录是否有属性
        if (!pBlkTblRecord->hasAttributeDefinitions()) {
            break;
        }

        //创建该块表记录的迭代器，来获取属性
        es = pBlkTblRecord->newIterator(pBlkTblRecordIter);
        if (Acad::eOk != es) break;

        for (; !pBlkTblRecordIter->done(); pBlkTblRecordIter->step()) {
            //通过迭代器获取实体，再属性定义来获取属性
            AcDbEntity *pEntity = NULL;
            pBlkTblRecordIter->getEntity(pEntity, AcDb::kForRead);
            AcDbAttributeDefinition *pAttrDef = AcDbAttributeDefinition::cast(pEntity);
            if (pAttrDef) {
                BlockAttribute blkAttr(
                    pAttrDef->tagConst(),
                    pAttrDef->promptConst(),
                    pAttrDef->textStringConst(),
                    pAttrDef->id()
                );
                outputBlkAttr.Add(blkAttr);
            }
            pEntity->close();
        }
    } while (false);

    //清理对象
    if (pBlkTbl) pBlkTbl->close();
    if (pBlkTblRecord) pBlkTblRecord->close();
    if (pBlkTblRecordIter) delete pBlkTblRecordIter;

    return (Acad::eOk == es && outputBlkId.isValid());
}

AcDbObjectId CArxProjectHelper::createBlockReference(AcDbObjectId blkDefId,
    double dRotation, const AcGeScale3d &scale, const CArray<BlockAttribute> &aNewAttr)
{
    assert(blkDefId.isValid());
    AcDbBlockReference *pBlkRef = new AcDbBlockReference;

    //设置块参照到定义块、旋转角和放大系数
    pBlkRef->setBlockTableRecord(blkDefId);
    pBlkRef->setRotation(dRotation);
    pBlkRef->setScaleFactors(scale);

    AcDbObjectId blkRefId;
    //进行块参照的拖放插入
    CBlockReferenceInsertJig blkRefInsertJig(pBlkRef);
    blkRefInsertJig.setDispPrompt(_T("指定块参照的插入点: \n"));
    if (AcEdJig::kNormal == blkRefInsertJig.drag()) {

        INT_PTR len = aNewAttr.GetCount();
        for (int i = 0; i < len; ++i) {
            const BlockAttribute *pNewAttr = &(aNewAttr.GetAt(i));
            AcDbAttribute *pAttr = new AcDbAttribute;
        
            //1、从块定义中拷贝属性
            {
                AcDbAttributeDefinition *pAttrDef = NULL;
                acdbOpenAcDbEntity((AcDbEntity*&) pAttrDef,
                    pNewAttr->getAttrId(), AcDb::kForRead);

                pAttr->setAttributeFromBlock(pAttrDef, pBlkRef->blockTransform());
            
                pAttrDef->close();
            }

            //2、从传递的数据中替换属性值，TextString可能是用户指定的新值
            pAttr->setTextString(pNewAttr->getTextString());

            //将属性实例附加到块参照
            pBlkRef->appendAttribute(pAttr);
            pAttr->close();
        }

        //将块参照放入模型空间
        blkRefId = blkRefInsertJig.append();
    }

    pBlkRef->close();

    return blkRefId;
}

//注：HBITMAP由调用者通过DeleteObject函数释放
HBITMAP CArxProjectHelper::getBlockPreviewBitmap(AcDbObjectId blkId, HDC hdc)
{
    AcDbBlockTableRecord *pBlkTblRcd = NULL;
    AcArray<Adesk::UInt8> icon;
    HBITMAP hBmp = NULL;
    Acad::ErrorStatus es;

    do {
        es = acdbOpenObject(pBlkTblRcd, blkId, AcDb::kForRead);
        if (Acad::eOk != es) break;

        //尝试构建缩略图
        AcString str;
        pBlkTblRcd->getName(str);
        if (!pBlkTblRcd->hasPreviewIcon()) {
            int rt = acedCommand(RTSTR, _T("BLOCKICON"), RTSTR, str.kACharPtr(), RTNONE);
        }

        if (!pBlkTblRcd->hasPreviewIcon())
            break;

        es = pBlkTblRcd->getPreviewIcon(icon);
        if (Acad::eOk != es) break;

        BITMAPINFOHEADER infoHeader;
        memcpy(&infoHeader, icon.asArrayPtr(), sizeof(BITMAPINFOHEADER));
        size_t memSize = sizeof(BITMAPINFOHEADER) + ((__int64)1<<infoHeader.biBitCount)*sizeof(RGBQUAD);
        BITMAPINFO *pInfo = new BITMAPINFO[memSize];
        memcpy(pInfo, icon.asArrayPtr(), memSize);

        //创建与设备无关的位图并返回句柄
        hBmp = CreateDIBitmap(hdc, &infoHeader, CBM_INIT, icon.asArrayPtr()+memSize, pInfo, DIB_RGB_COLORS);
        delete [] pInfo;

    } while (false);

    if (pBlkTblRcd) pBlkTblRcd->close();

    return hBmp;
}

void CArxProjectHelper::printSymbolRecord(const ACHAR *szSymbolType, const AcStringArray &recordName)
{
    int count = recordName.length();
    acutPrintf(_T("%s: "), szSymbolType);

    if (count <= 0) {
        acutPrintf(_T("<无>\n"));
        return;
    }

    for (int i = 0; i < count; ++i) {
        acutPrintf(recordName.at(i).kACharPtr());

        if (i < count-1)
            acutPrintf(_T(","));
    }
    acutPrintf(_T("\n"));  //结束后打印换行
}

AcDbObjectId CArxProjectHelper::createTable(int iRowCount, int iColCount,
    AcDb::CellAlignment cellAlignment)
{
    AcDbObjectId tableId;
    Acad::ErrorStatus es;
    AcDbTable *pTbl = new AcDbTable;

    //设置行列数
    es = pTbl->setNumRows(iRowCount);
    assert(Acad::eOk == es);
    es = pTbl->setNumColumns(iColCount);
    assert(Acad::eOk == es);

    //设置单元格对齐方式
    for (int i = 0; i < iRowCount; ++i)
        for (int j = 0; j < iColCount; ++j)
            es = pTbl->setAlignment(i, j, cellAlignment);
    assert(Acad::eOk == es);

    //禁用标题行
    es = pTbl->suppressHeaderRow(false);
    assert(Acad::eOk == es);

    pTbl->setColumnWidth(30); //固定列宽为30

    es = pTbl->generateLayout();
    assert(Acad::eOk == es);

    //通过动态拖放插入表格
    CTableInsertJig tblJig(pTbl);
    tblJig.setDispPrompt(_T("指定表格插入点: \n"));
    if (AcEdJig::kNormal == tblJig.drag()) {
        tableId = tblJig.append();
    }

    pTbl->close();

    return tableId;
}

bool CArxProjectHelper::fillTableContent(const TableContent &aTableContent,
    const AcDbObjectId &tableId)
{
    AcDbTable *pTbl = NULL;
    Acad::ErrorStatus es;
    if (Acad::eOk != acdbOpenObject(pTbl, tableId, AcDb::kForWrite))
        return false;

    for (int i = 0; i < (int) pTbl->numRows(); ++i) {
        for (int j = 0; j < (int) pTbl->numColumns(); ++j) {
            es = pTbl->setTextString(i, j, aTableContent[i][j]);
            assert(Acad::eOk == es);
        }
    }

    pTbl->close();
    return true;
}

bool CArxProjectHelper::setTableTextAttribute(const AcDbObjectId &textStyle,
    double dTextHeight, double dTextWidthFactor,
    const AcCmColor &textColor, const AcDbObjectId &tableId)
{
    AcDbTable *pTbl = NULL;
    Acad::ErrorStatus es;
    if (Acad::eOk != acdbOpenObject(pTbl, tableId, AcDb::kForWrite))
        return false;

    for (int i = 0; i < (int) pTbl->numRows(); ++i) {
        for (int j = 0; j < (int) pTbl->numColumns(); ++j) {
            es = pTbl->setTextStyle(i, j, textStyle);  //文字样式
            assert(Acad::eOk == es);
            es = pTbl->setTextHeight(i, j, dTextHeight); //文字高度
            assert(Acad::eOk == es);
            es = pTbl->setContentColor(i, j, textColor); //文字颜色
            assert(Acad::eOk == es);            
        }
    }

    //修改指定字体样式的宽度因子，达到修改表格中文字的宽高比，该做法不好！
    AcDbObjectPointer<AcDbTextStyleTableRecord> pTextStyleRcd(textStyle, AcDb::kForWrite);
    if (Acad::eOk == pTextStyleRcd.openStatus()) {
        pTextStyleRcd->setXScale(dTextWidthFactor);
    }

    pTbl->close();
    return true;
}

bool CArxProjectHelper::setTableLineAttribute(AcDb::LineWeight lineWidth,
    const AcDbObjectId &lineType, const AcCmColor &lineColor,
    const AcDbObjectId &tableId)
{
    AcDbTable *pTbl = NULL;
    Acad::ErrorStatus es;
    if (Acad::eOk != acdbOpenObject(pTbl, tableId, AcDb::kForWrite))
        return false;

    for (int i = 0; i < (int) pTbl->numRows(); ++i) {
        for (int j = 0; j < (int) pTbl->numColumns(); ++j) {
            //线框线宽
            es = pTbl->setGridLineWeight(i, j, AcDb::kAllGridLineTypes, lineWidth);
            assert(Acad::eOk == es);
            //线框线框线型
            es = pTbl->setGridLinetype(i, j, AcDb::kAllGridLineTypes, lineType);
            assert(Acad::eOk == es);
            //线框颜色
            es = pTbl->setGridColor(i, j, AcDb::kAllGridLineTypes, lineColor);
            assert(Acad::eOk == es);
        }
    }

    pTbl->close();
    return true;
}

bool CArxProjectHelper::postToModelSpace(AcDbObjectId &outputId, AcDbEntity *pEntity)
{
    Acad::ErrorStatus es;
    AcDbBlockTable *pBlkTbl = NULL;
    AcDbBlockTableRecord *pBlkTblRecord = NULL;

    outputId.setNull();

    do {
        //打开块表
        es = acdbHostApplicationServices()->workingDatabase()
            ->getBlockTable(pBlkTbl, AcDb::kForRead);
        if (Acad::eOk != es) break;

        //打开块表记录
        es = pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRecord, AcDb::kForWrite);
        if (Acad::eOk != es) break;

        //添加实体并返回其Id
        es = pBlkTblRecord->appendAcDbEntity(outputId, pEntity);
    } while (false);
    
    if (pBlkTbl) pBlkTbl->close();
    if (pBlkTblRecord) pBlkTblRecord->close();

    return Acad::eOk == es;
}

bool CArxProjectHelper::createLayer(AcDbObjectId &layerId, const ACHAR *layerName)
{
    AcDbLayerTable *pLayerTbl = NULL;
    AcDbLayerTableRecord *pLayerTblRecord = NULL;
    Acad::ErrorStatus es;

    layerId.setNull();

    do {
        es = acdbHostApplicationServices()->workingDatabase()
            ->getLayerTable(pLayerTbl, AcDb::kForWrite);
        if (Acad::eOk != es) break;

        //判断图层是否存在，如果不存在则创建
        if (pLayerTbl->has(layerName)) {
            es = pLayerTbl->getAt(layerName, pLayerTblRecord, AcDb::kForWrite);
        }
        else {
            pLayerTblRecord = new AcDbLayerTableRecord();
            pLayerTblRecord->setName(layerName);
            es = pLayerTbl->add(pLayerTblRecord);
        }
        if (Acad::eOk != es) break;

        //返回图层Id
        layerId = pLayerTblRecord->id();

    } while (false);

    if (pLayerTbl) pLayerTbl->close();
    if (pLayerTblRecord) pLayerTblRecord->close();

    return Acad::eOk == es;
}