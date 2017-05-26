#define _EXPORTING
#include "Calculation.h"

Calculation::Calculation(void) : m_a(0), m_b(0)
{
}

Calculation::Calculation(double a, double b) : m_a(a), m_b(b)
{
}

Calculation::~Calculation(void)
{
}

double Calculation::Add() {
    return m_a + m_b;
}

double Calculation::Sub() {
    return m_a - m_b;
}

void Calculation::setA(double value) {
    m_a = value;
}

double Calculation::getA() {
    return m_a;
}

void Calculation::setB(double value) {
    m_b = value;
}

double Calculation::getB() {
    return m_b;
}

#undef _EXPORTING