#ifndef __ICALC_H__
#define __ICALC_H__

#include <Unknwn.h>

// {ED9962A4-C14F-4da3-916D-4ACB61FBA6F8}
static const GUID IID_ICalc = 
{ 0xed9962a4, 0xc14f, 0x4da3, { 0x91, 0x6d, 0x4a, 0xcb, 0x61, 0xfb, 0xa6, 0xf8 } };

class ICalc : public IUnknown
{
public:
    STDMETHOD(Add) (double a, double b, double *fRet) PURE;
    STDMETHOD(Sub) (double a, double b, double *fRet) PURE;
};
#endif //__ICALC_H__