#ifndef __ICalc_H__
#define __ICalc_H__

#include <Unknwn.h>

// {07054FA4-2E22-45d6-B6B3-5451163122B5}
static const GUID IID_ICalc = 
{ 0x7054fa4, 0x2e22, 0x45d6, { 0xb6, 0xb3, 0x54, 0x51, 0x16, 0x31, 0x22, 0xb5 } };

class ICalc : public IUnknown
{
public:
    STDMETHOD(Add) (double a, double b, double *fRet) PURE;
    STDMETHOD(Sub) (double a, double b, double *fRet) PURE;
};

#endif