//////////////////////////////////////////////////////////////////////////
// ObjectARX练习项目帮助类，对完成MFG内部培训计划第三部分1~8题过程中
// 所需要的方法进行封装，方便使用。
//
//////////////////////////////////////////////////////////////////////////

#pragma once

class CArxProjectHelper
{
public:
    CArxProjectHelper(void){};
    ~CArxProjectHelper(void){};

public:
    //该结构体用于创建属性块参照传递数据，其中TextString可由用户指定新值，
    //其他的字段不可修改，tag、prompt和testString仅用作ListCtrl界面展示。
    struct BlockAttribute {
    public:
        // 构造函数
        BlockAttribute() {}
        BlockAttribute(const CString& tag, const CString& prompt,
            const CString& textSting, const AcDbObjectId& attrId)
            : m_tag(tag), m_prompt(prompt)
            , m_textString(textSting), m_attrId(attrId) {}
        //属性
        const CString& getTag() const {return m_tag;}
        const CString& getPompt() const {return m_prompt;}
        const CString& getTextString() const {return m_textString;}
        const AcDbObjectId& getAttrId() const {return m_attrId;}
        void setTextString(const CString& newTextSting)
            {m_textString = newTextSting;}
    private:
        CString m_tag;
        CString m_prompt;
        CString m_textString;
        AcDbObjectId m_attrId;
    };

    //第8题插入表格时使用的二维数组
    typedef std::vector<std::vector<CString> > TableContent;

public:
    //在指定图层上绘制指定颜色的圆
    static AcDbObjectId createCircle(const AcGePoint3d &center,
        double radius, const ACHAR *layer, Adesk::UInt16 color);
    
    //返回指定符号表记录的名称
    template<typename SymbolTableType>
    static bool getSymbolRecord(AcStringArray &outputName);

    template<typename SymbolTableType>
    static bool getSymbolRecord(AcStringArray &outputName,
        AcDbObjectIdArray &outputObjId);
    
    //返回组名称
    static bool getGroupName(AcStringArray &outputName);

    //获取当前图层名称
    static bool getCurrentLayerName(AcString &outputName);

    //返回块属性
    static bool getBlockAttribute(CArray<BlockAttribute> &outputBlkAttr,
        AcDbObjectId &outputBlkId, const TCHAR *szBlkName);

    //创建带属性的块参照
    static AcDbObjectId createBlockReference(AcDbObjectId blkDefId, double dRotation,
        const AcGeScale3d &scale, const CArray<BlockAttribute> &aNewAttr);

    //获取块记录缩略图
    static HBITMAP getBlockPreviewBitmap(AcDbObjectId blkId, HDC hdc);

    //打印指定的符号表
    static void printSymbolRecord(const ACHAR *szSymbolType,
        const AcStringArray &recordName);

    //根据行列数、对齐方式、线宽、线型、线框颜色插入表格，返回表格对象Id
    static AcDbObjectId createTable(int iRowCount, int iColCount,
        AcDb::CellAlignment cellAlignment);

    //填充表格文字
    static bool fillTableContent(const TableContent &aTableContent,
        const AcDbObjectId &tableId);

    //设置表格线框属性
    static bool setTableLineAttribute(AcDb::LineWeight lineWidth,
        const AcDbObjectId &lineType, const AcCmColor &lineColor,
        const AcDbObjectId &tableId);

    //设置表格文字属性
    static bool setTableTextAttribute(const AcDbObjectId &textStyle,
        double dTextHeight, double dTextWidthFactor,
        const AcCmColor &textColor, const AcDbObjectId &tableId);
private:
    static bool postToModelSpace(AcDbObjectId &outputId, AcDbEntity *pEntity);
    static bool createLayer(AcDbObjectId &layerId, const ACHAR *layerName);
};

template<typename SymbolTableType>
bool CArxProjectHelper::getSymbolRecord(AcStringArray &outputName,
    AcDbObjectIdArray &outputObjId)
{
    Acad::ErrorStatus es;
    AcDbSymbolTable *pSymbolTbl = NULL;
    AcDbSymbolTableRecord *pSymbolTblRecord = NULL;
    AcDbSymbolTableIterator *pSymbolTblIter = NULL;
    AcString strBuf;

    outputName.removeAll();
    outputObjId.removeAll();

    do {
        //按指定符号类型打开符号表
        es = acdbHostApplicationServices()->workingDatabase()
            ->getSymbolTable((SymbolTableType*&) pSymbolTbl, AcDb::kForRead);
        if (Acad::eOk != es) break;

        //新建符号表迭代器
        es = pSymbolTbl->newIterator(pSymbolTblIter);
        if (Acad::eOk != es) break;

        //获取符号表记录
        for (; !pSymbolTblIter->done(); pSymbolTblIter->step()) {
            pSymbolTblIter->getRecord(pSymbolTblRecord, AcDb::kForRead);
            pSymbolTblRecord->getName(strBuf);
            outputName.append(strBuf);
            outputObjId.append(pSymbolTblRecord->id());
            pSymbolTblRecord->close();
        }
    } while (false);

    if (pSymbolTbl) pSymbolTbl->close();
    if (pSymbolTblIter) delete pSymbolTblIter;

    return Acad::eOk == es;
}


template<typename SymbolTableType> inline
bool CArxProjectHelper::getSymbolRecord(AcStringArray &outputName)
{
    AcDbObjectIdArray aObjId;
    return getSymbolRecord<SymbolTableType>(outputName, aObjId);
}