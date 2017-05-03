#ifndef __CalculationImpl_H__
#define __CalculationImpl_H__

#include <Unknwn.h>
#include "ICalc.h"

class CalculationImpl : public ICalc
{
public:
    
    STDMETHOD(Add) (double a, double b, double *fRet);
    STDMETHOD(Sub) (double a, double b, double *fRet);

    STDMETHOD(QueryInterface) (REFIID riid, void **ppv);
    STDMETHOD_(ULONG, AddRef) ();
    STDMETHOD_(ULONG, Release) ();

    CalculationImpl();

private:
    ULONG m_cRef;
};

#endif