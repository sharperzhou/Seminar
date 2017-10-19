#ifndef __CALCULATION_H__
#define __CALCULATION_H__

#include "ICalc2.h"

class CCalcImpl : public ICalc2
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

    //IDispatch
    STDMETHOD(GetTypeInfoCount) (UINT *pctinfo);
    STDMETHOD(GetTypeInfo) (UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
    STDMETHOD(GetIDsOfNames) (REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
    STDMETHOD(Invoke) (DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams,
        VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);

private:
    HRESULT LoadTypeInfo();

private:
    ULONG m_cRef;
    ITypeInfo *m_pTypeInfo;
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

