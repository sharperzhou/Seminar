#ifndef __ICalc_H__
#define __ICalc_H__

#include <Unknwn.h>

// {0988827B-5A81-4abf-BFEB-3E5D472E1392}
static const GUID IID_ICalc = 
{ 0x988827b, 0x5a81, 0x4abf, { 0xbf, 0xeb, 0x3e, 0x5d, 0x47, 0x2e, 0x13, 0x92 } };


class ICalc : public IUnknown
{
public:
    STDMETHOD(Add) (double a, double b, double *fRet) PURE;
    STDMETHOD(Sub) (double a, double b, double *fRet) PURE;
};

#endif