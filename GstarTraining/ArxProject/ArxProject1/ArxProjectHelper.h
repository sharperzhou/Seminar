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
    //----------------------------------------------------------
    // Summary:
    //    在指定图层上绘制指定颜色的圆
    // Parameter:
    //    center - 圆心
    //    radius - 半径
    //    layer - 图层名
    //    color - 颜色索引值
    // Returns:
    //    AcDbObjectId
    //----------------------------------------------------------
    static AcDbObjectId createCircle(const AcGePoint3d &center,
        double radius, const ACHAR *layer, Adesk::UInt16 color);
    
    //----------------------------------------------------------
    // Summary:
    //    返回指定符号表记录的名称
    // Parameter:
    //    outputName - 返回符号记录名
    //    [outputObjId] - 返回符号记录的对象Id
    // Returns:
    //    bool
    //----------------------------------------------------------
    template<typename SymbolTableType>
    static bool getSymbolRecord(AcStringArray &outputName);

    template<typename SymbolTableType>
    static bool getSymbolRecord(AcStringArray &outputName,
        AcDbObjectIdArray &outputObjId);
    
    //----------------------------------------------------------
    // Summary:
    //    返回组名称
    // Parameter:
    //    outputName - 返回组名
    // Returns:
    //    bool
    //----------------------------------------------------------
    static bool getGroupName(AcStringArray &outputName);

    //----------------------------------------------------------
    // Summary:
    //    获取当前图层名称
    // Parameter:
    //    outputName - 
    // Returns:
    //    bool
    //----------------------------------------------------------
    static bool getCurrentLayerName(AcString &outputName);

    //----------------------------------------------------------
    // Summary:
    //    返回单个块的所有属性
    // Parameter:
    //    outputBlkAttr - 属性数组
    //    outputBlkId - 块定义的Id
    //    szBlkName - 块定义的名称
    // Returns:
    //    bool
    //----------------------------------------------------------
    static bool getBlockAttribute(CArray<BlockAttribute> &outputBlkAttr,
        AcDbObjectId &outputBlkId, const TCHAR *szBlkName);

    //----------------------------------------------------------
    // Summary:
    //    根据块定义创建带属性的块参照
    // Parameter:
    //    blkDefId - 块定义的Id
    //    dRotation - 块参照的旋转角度，单位°
    //    scale - 块参照的放大系数，默认为1
    //    aNewAttr - 块参照需要设定的属性值
    // Returns:
    //    AcDbObjectId
    //----------------------------------------------------------
    static AcDbObjectId createBlockReference(AcDbObjectId blkDefId, double dRotation,
        const AcGeScale3d &scale, const CArray<BlockAttribute> &aNewAttr);

    //----------------------------------------------------------
    // Summary:
    //    从块定义中获取块记录缩略图，返回的位图句柄需要由
    //    调用者释放
    // Parameter:
    //    blkId - 块定义的Id
    //    hdc - 需要显示缩略图的窗口的DC句柄
    // Returns:
    //    HBITMAP
    //----------------------------------------------------------
    static HBITMAP getBlockPreviewBitmap(AcDbObjectId blkId, HDC hdc);

    //----------------------------------------------------------
    // Summary:
    //    打印指定的符号表名称
    // Parameter:
    //    szSymbolType - 符号表类型名称
    //    recordName - 符号表名称
    // Returns:
    //    void
    //----------------------------------------------------------
    static void printSymbolRecord(const ACHAR *szSymbolType,
        const AcStringArray &recordName);

    //----------------------------------------------------------
    // Summary:
    //    根据行列数、对齐方式插入表格，返回表格对象Id
    // Parameter:
    //    iRowCount - 表格的行数
    //    iColCount - 表格的列数
    //    cellAlignment - 单元格对齐方式
    // Returns:
    //    AcDbObjectId
    //----------------------------------------------------------
    static AcDbObjectId createTable(int iRowCount, int iColCount,
        AcDb::CellAlignment cellAlignment);

    //----------------------------------------------------------
    // Summary:
    //    根据表格Id填充表格文字
    // Parameter:
    //    aTableContent - 表格文字内容
    //    tableId - 表格Id
    // Returns:
    //    bool
    //----------------------------------------------------------
    static bool fillTableContent(const TableContent &aTableContent,
        const AcDbObjectId &tableId);

    //----------------------------------------------------------
    // Summary:
    //    根据表格Id设置表格线框属性
    // Parameter:
    //    lineWidth - 线宽
    //    lineType - 线型
    //    lineColor - 颜色
    //    tableId - 表格Id
    // Returns:
    //    bool
    //----------------------------------------------------------
    static bool setTableLineAttribute(AcDb::LineWeight lineWidth,
        const AcDbObjectId &lineType, const AcCmColor &lineColor,
        const AcDbObjectId &tableId);

    //----------------------------------------------------------
    // Summary:
    //    根据表格Id设置表格文字属性
    //    注：改变宽度因子会改变文字样式
    // Parameter:
    //    textStyle - 文字样式
    //    dTextHeight - 文字高度
    //    dTextWidthFactor - 文字宽度因子
    //    textColor - 文字颜色
    //    tableId - 表格Id
    // Returns:
    //    bool
    //----------------------------------------------------------
    static bool setTableTextAttribute(const AcDbObjectId &textStyle,
        double dTextHeight, double dTextWidthFactor,
        const AcCmColor &textColor, const AcDbObjectId &tableId);
private:
    //----------------------------------------------------------
    // Summary:
    //    将实体放入模型空间，并返回实体的Id
    // Parameter:
    //    outputId - 实体Id
    //    pEntity - 实体对象指针
    // Returns:
    //    bool
    //----------------------------------------------------------
    static bool postToModelSpace(AcDbObjectId &outputId, AcDbEntity *pEntity);

    //----------------------------------------------------------
    // Summary:
    //    根据图层名称创建图层，并返回图层Id
    // Parameter:
    //    layerId - 图层Id
    //    layerName - 图层名称
    // Returns:
    //    bool
    //----------------------------------------------------------
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