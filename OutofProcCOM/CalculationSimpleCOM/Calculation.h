#ifndef __CALCULATION_H__
#define __CALCULATION_H__

#include "ICalc.h"

class CCalcImpl : public ICalc
{
public:
    CCalcImpl();
    ~CCalcImpl();

public:
    //ICalc
    STDMETHOD(Add) (double a, double b, double *fRet);
    STDMETHOD(Sub) (double a, double b, double *fRet);

    //IUnknown
    STDMETHOD(QueryInterface) (REFIID riid, void **ppvObject);
    STDMETHOD_(ULONG, AddRef) ();
    STDMETHOD_(ULONG, Release) ();

private:
    ULONG m_cRef;
};

class CCalcFactory : public IClassFactory
{
public:
    CCalcFactory();
    ~CCalcFactory();

public:
    //IClassFactory
    STDMETHOD(CreateInstance) (IUnknown *pUnkOuter, REFIID riid, void **ppvObject);
    STDMETHOD(LockServer) (BOOL fLock);

    //IUnknown
    STDMETHOD(QueryInterface) (REFIID riid, void **ppvObject);
    STDMETHOD_(ULONG, AddRef) ();
    STDMETHOD_(ULONG, Release) ();

private:
    ULONG m_cRef;
};

#endif

