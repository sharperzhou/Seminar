#ifndef __ICALC2_H__
#define __ICALC2_H__

#include <Unknwn.h>

// {CC564AE2-CC21-4988-A446-A8286D76C0EB}
static const GUID IID_ICalc2 = 
{ 0xcc564ae2, 0xcc21, 0x4988, { 0xa4, 0x46, 0xa8, 0x28, 0x6d, 0x76, 0xc0, 0xeb } };

class ICalc2 : public IUnknown
{
public:
    STDMETHOD(Multiple) (double a, double b, double *fRet) PURE;
    //From ICalc
    STDMETHOD(Add) (double a, double b, double *fRet) PURE;
    STDMETHOD(Sub) (double a, double b, double *fRet) PURE;
};

#endif //__ICALC2_H__