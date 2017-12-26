#pragma once
class CCalculation
{
public:
    CCalculation(void);
    CCalculation(double dValue1, double dValue2);
    ~CCalculation(void);

public:
    void setValue1(double dValue1) {m_dVal1 = dValue1;}
    void setValue2(double dValue2){m_dVal2 = dValue2;}
    double getValue1() const {return m_dVal1;}
    double getValue2() const {return m_dVal2;}

public:
    bool Add(double& dResult);
    bool Subtract(double& dResult);
    bool Multiply(double& dResult);
    bool Divide(double & dResult);

protected:
    double m_dVal1;
    double m_dVal2;
};

