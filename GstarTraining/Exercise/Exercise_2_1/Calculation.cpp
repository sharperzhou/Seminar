#include "StdAfx.h"
#include "Calculation.h"
#include <math.h>


CCalculation::CCalculation(void) : m_dVal1(0.0), m_dVal2(0.0)
{
}

CCalculation::CCalculation(double dValue1, double dValue2) 
    : m_dVal1(dValue1), m_dVal2(dValue2)
{
}

CCalculation::~CCalculation(void)
{
}

bool CCalculation::Add(double& dResult)
{
    dResult = m_dVal1 + m_dVal2;
    return true;
}

bool CCalculation::Subtract(double& dResult)
{
    dResult = m_dVal1 - m_dVal2;
    return true;
}

bool CCalculation::Multiply(double& dResult)
{
    dResult = m_dVal1 * m_dVal2;
    return true;
}

bool CCalculation::Divide(double & dResult)
{
    if (abs(m_dVal2) < 1e-15) return false;
    
    dResult = m_dVal1 / m_dVal2;
    return true;
}