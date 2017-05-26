#pragma once
#include "stdafx.h"

class EXPORT Calculation
{
public:
    Calculation(void);
    Calculation(double a, double b);
    ~Calculation(void);
public:
    double Add();
    double Sub();
    void setA(double value);
    double getA();
    void setB(double value);
    double getB();
private:
    double m_a, m_b;
};
