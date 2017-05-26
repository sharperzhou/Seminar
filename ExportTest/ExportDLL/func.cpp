#include "func.h"
double __stdcall Add(double a, double b)
{
    return a + b;
}

double __stdcall Sub(double a, double b)
{
    return a - b;
}

double __stdcall Mult(double a, double b)
{
    return a * b;
}

double __stdcall Div(double a, double b)
{
    double temp;
    if (b != 0) temp = a / b;
    return temp;
}