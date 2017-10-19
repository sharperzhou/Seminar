#ifndef __ICALC_H__
#define __ICALC_H__

#include <Unknwn.h>

// {CFCC097A-8E57-485f-8C4F-C73D7A50641C}
static const GUID IID_ICalc2 = 
{ 0xcfcc097a, 0x8e57, 0x485f, { 0x8c, 0x4f, 0xc7, 0x3d, 0x7a, 0x50, 0x64, 0x1c } };

// {6F4EBEA4-BD6C-4633-A560-C37F0715769A}
static const GUID TLIBID_CalculationAutomation = 
{ 0x6f4ebea4, 0xbd6c, 0x4633, { 0xa5, 0x60, 0xc3, 0x7f, 0x7, 0x15, 0x76, 0x9a } };


class ICalc2 : public IDispatch
{
public:
    STDMETHOD(Add) (double a, double b, double *fRet) PURE;
    STDMETHOD(Sub) (double a, double b, double *fRet) PURE;
};

#endif