#ifndef __CALCULATION2_H__
#define __CALCULATION2_H__

#include "ICalc2.h"

class ICalc;

class CCalc2Impl : public ICalc2
{
public:
    CCalc2Impl();
    ~CCalc2Impl();

public:
    //ICalc2
    STDMETHOD(Multiple) (double a, double b, double *fRet);

    //CalculationBase -> ICalc
    STDMETHOD(Add) (double a, double b, double *fRet);
    STDMETHOD(Sub) (double a, double b, double *fRet);

    //IUnknown
    STDMETHOD(QueryInterface) (REFIID riid, void **ppvObject);
    STDMETHOD_(ULONG, AddRef) ();
    STDMETHOD_(ULONG, Release) ();

    HRESULT Init();

private:
    ULONG m_cRef;
    ICalc *m_pCalc;
};

class CCalc2Factory : public IClassFactory
{
public:
    CCalc2Factory();
    ~CCalc2Factory();

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

#endif //__CALCULATION2_H__


