#ifndef __ICalc_H__
#define __ICalc_H__

#include <Unknwn.h>

// {9F860E29-318A-4592-8E63-318DB00A2339}
static const GUID IID_ICalc = 
{ 0x9f860e29, 0x318a, 0x4592, { 0x8e, 0x63, 0x31, 0x8d, 0xb0, 0xa, 0x23, 0x39 } };

// {9934449A-CD56-409c-A6FC-E67B9A8D5902}
static const GUID TLIBID_Calculation3 = 
{ 0x9934449a, 0xcd56, 0x409c, { 0xa6, 0xfc, 0xe6, 0x7b, 0x9a, 0x8d, 0x59, 0x2 } };

class ICalc : public IDispatch
{
public:
    STDMETHOD(Add) (double a, double b, double *fRet) PURE;
    STDMETHOD(Sub) (double a, double b, double *fRet) PURE;
};

#endif