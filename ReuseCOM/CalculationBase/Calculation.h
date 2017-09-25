#ifndef __CALCULATION_H__
#define __CALCULATION_H__

#include "ICalc.h"

class INondelegatingUnknown
{
public:
    virtual HRESULT  __stdcall  NondelegationQueryInterface(REFIID riid, void **ppvObject) = 0 ;
    virtual ULONG	 __stdcall  NondelegatingAddRef() = 0; 
    virtual ULONG	 __stdcall  NondelegationRelease() = 0;
};

class CCalcImpl : public ICalc, public INondelegatingUnknown
{
public:
    CCalcImpl(IUnknown *pUnknownOuter);
    ~CCalcImpl();

public:
    //ICalc
    STDMETHOD(Add) (double a, double b, double *fRet);
    STDMETHOD(Sub) (double a, double b, double *fRet);

    //IUnknown
    STDMETHOD(QueryInterface) (REFIID riid, void **ppvObject);
    STDMETHOD_(ULONG, AddRef) ();
    STDMETHOD_(ULONG, Release) ();

    //INondelegatingUnknown
    STDMETHOD(NondelegationQueryInterface) (REFIID riid, void **ppvObject);
    STDMETHOD_(ULONG, NondelegatingAddRef) ();
    STDMETHOD_(ULONG, NondelegationRelease) ();

private:
    ULONG m_cRef;
    IUnknown  *m_pUnknownOuter;
};


class CCalcFactory : public IClassFactory
{
public:
    CCalcFactory();
    ~CCalcFactory();

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

#endif //__CALCULATION_H__


