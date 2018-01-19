#include "stdafx.h"
#include "Jig.h"

AcEdJig::DragStatus CInsertJig::sampler()
{
    DragStatus stat;

    //输入控制允许三维坐标
    setUserInputControls((UserInputControls) (AcEdJig::kAccept3dCoordinates));

    static AcGePoint3d ptTemp;
    stat = acquirePoint(ptTemp);

    if (ptTemp == m_ptInsert && AcEdJig::kNormal == stat)
        return AcEdJig::kNoChange;

    m_ptInsert = ptTemp;

    return stat;
}

Adesk::Boolean CBlockReferenceInsertJig::update()
{
    ((AcDbBlockReference*) m_pEnt)->setPosition(m_ptInsert);
    return Adesk::kTrue;
}

Adesk::Boolean CTableInsertJig::update()
{
    ((AcDbTable*) m_pEnt)->setPosition(m_ptInsert);
    return Adesk::kTrue;
}

CCircleJig::CCircleJig(const AcGePoint3d &ptCenter, Adesk::UInt16 color)
    : m_dRadius(0)
    , m_ptCenter(ptCenter)
{
    m_pCircle = new AcDbCircle(ptCenter, AcGeVector3d(0, 0, 1), m_dRadius);
    m_pCircle->setColorIndex(color);
}

CCircleJig::~CCircleJig()
{
    if (m_pCircle)
        m_pCircle->close();
}

AcEdJig::DragStatus CCircleJig::sampler()
{
    DragStatus stat;

    //距离非零非负值
    setUserInputControls((UserInputControls)
        (AcEdJig::kNoNegativeResponseAccepted
        | AcEdJig::kNoZeroResponseAccepted));

    static double dTemp = 0;
    stat = acquireDist(dTemp, m_ptCenter);

    //精度控制1e-15
    if (abs(dTemp - m_dRadius) < 1e-15 && AcEdJig::kNormal == stat)
        return AcEdJig::kNoChange;

    m_dRadius = dTemp;

    return stat;
}

Adesk::Boolean CCircleJig::update()
{
    m_pCircle->setRadius(m_dRadius);
    return Adesk::kTrue;
}