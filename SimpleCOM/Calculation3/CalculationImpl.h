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

    STDMETHOD(GetTypeInfoCount) (UINT *pctinfo);
    STDMETHOD(GetTypeInfo) (UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
    STDMETHOD(GetIDsOfNames) (REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
    STDMETHOD(Invoke) (DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams,
                        VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);

    CalculationImpl();
    ~CalculationImpl();

private:
    HRESULT LoadTypeInfo();

private:
    ULONG m_cRef;
    ITypeInfo *m_pITypeInfo;
};

#endif