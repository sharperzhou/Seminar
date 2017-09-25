#ifndef __CALCULATION3_H__
#define __CALCULATION3_H__

#include "ICalc3.h"

class ICalc;

class CCalc3Impl : public ICalc3
{
public:
    CCalc3Impl();
    ~CCalc3Impl();

public:
    //ICalc3
    STDMETHOD(Divided) (double a, double b, double *fRet);

    //ICalc
    STDMETHOD(Add) (double a, double b, double *fRet);
    STDMETHOD(Sub) (double a, double b, double *fRet);

    //IUnknown
    STDMETHOD(QueryInterface) (REFIID riid, void **ppvObject);
    STDMETHOD_(ULONG, AddRef) ();
    STDMETHOD_(ULONG, Release) ();

    HRESULT Init();

private:
    ULONG m_cRef;
    IUnknown *m_pUnknownInner;  //point to CalculationBase
};

class CCalc3Factory : public IClassFactory
{
public:
    CCalc3Factory();
    ~CCalc3Factory();

public:
    //IClassFacotry
    STDMETHOD(CreateInstance) (IUnknown *pUnkOuter, REFIID riid, void **ppvObject);
    STDMETHOD(LockServer) (BOOL fLock);

    //IUnknown
    STDMETHOD(QueryInterface) (REFIID riid, void **ppvObject);
    STDMETHOD_(ULONG, AddRef) ();
    STDMETHOD_(ULONG, Release) ();

private:
    ULONG m_cRef;
};

#endif //__CALCULATION3_H__
