#ifndef __ICALC_H__
#define __ICALC_H__

#include <Unknwn.h>

// {D3A4AF14-C36F-44f6-8644-B3AE2E341C0D}
static const GUID IID_ICalc = 
{ 0xd3a4af14, 0xc36f, 0x44f6, { 0x86, 0x44, 0xb3, 0xae, 0x2e, 0x34, 0x1c, 0xd } };

class ICalc : public IUnknown
{
public:
    STDMETHOD(Add) (double a, double b, double *fRet) PURE;
    STDMETHOD(Sub) (double a, double b, double *fRet) PURE;
};

#endif