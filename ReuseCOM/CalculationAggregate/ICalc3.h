#ifndef __ICALC3_H__
#define __ICALC3_H__

#include <Unknwn.h>

// {4A8C7247-B792-49c0-BF6A-855639FC7C68}
static const GUID IID_ICalc3 = 
{ 0x4a8c7247, 0xb792, 0x49c0, { 0xbf, 0x6a, 0x85, 0x56, 0x39, 0xfc, 0x7c, 0x68 } };

class ICalc3 : public IUnknown
{
public:
    //ICalc3
    STDMETHOD(Divided) (double a, double b, double *fRet) PURE;

    //ICalc
    STDMETHOD(Add) (double a, double b, double *fRet) PURE;
    STDMETHOD(Sub) (double a, double b, double *fRet) PURE;
};

#endif //__ICALC3_H__