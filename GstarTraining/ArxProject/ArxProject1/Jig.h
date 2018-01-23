//////////////////////////////////////////////////////////////////////////
// 动态拖放显示块参照、表格和圆的Jig类
//
//////////////////////////////////////////////////////////////////////////

#pragma once

class AcEdJig;

class CInsertJig : public AcEdJig
{
public:
    //重写实现Jig的三个函数
    virtual DragStatus sampler();
    virtual Adesk::Boolean update() {return Adesk::kFalse;}
    virtual AcDbEntity *entity() const {return m_pEnt;}

protected:
    CInsertJig(AcDbEntity *pEnt) : m_pEnt(pEnt) {m_pEnt->setDatabaseDefaults();}
    ~CInsertJig(void) {};

protected:
    AcDbEntity *m_pEnt;
    AcGePoint3d m_ptInsert;
};

//插入块参照的Jig
class CBlockReferenceInsertJig : public CInsertJig
{
public:
    CBlockReferenceInsertJig(AcDbBlockReference *pBlkRef) : CInsertJig(pBlkRef) {}
    ~CBlockReferenceInsertJig() {};

    virtual Adesk::Boolean update();
};

//插入表格的Jig
class CTableInsertJig : public CInsertJig
{
public:
    CTableInsertJig(AcDbTable *pTable) : CInsertJig(pTable) {}
    ~CTableInsertJig() {};

    virtual Adesk::Boolean update();
};

//创建圆的Jig
class CCircleJig : public AcEdJig
{
public:
    CCircleJig(const AcGePoint3d &, Adesk::UInt16);
    ~CCircleJig();

    virtual DragStatus sampler();
    virtual Adesk::Boolean update();
    virtual AcDbEntity *entity() const {return m_pCircle;}

public:
    double getRadius() const {return m_dRadius;}

private:
    double m_dRadius;
    AcGePoint3d m_ptCenter;
    AcDbCircle *m_pCircle;
};
