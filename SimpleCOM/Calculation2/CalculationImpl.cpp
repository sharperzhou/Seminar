#include "CalculationImpl.h"

extern ULONG g_cObj;

CalculationImpl::CalculationImpl()
{
    m_cRef = 0;
    m_CalcObj.m_pParent = this;
    ++g_cObj;
}

STDAPI CalculationImpl::QueryInterface(const IID &riid, void **ppv)
{
    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_ICalc))
        *ppv = &m_CalcObj;
    else {
        *ppv = 0;
        return E_NOINTERFACE;
    }
    this->AddRef();
    return S_OK;
}

STDAPI_(ULONG) CalculationImpl::AddRef()
{
    return ++m_cRef;
}

STDAPI_(ULONG) CalculationImpl::Release()
{
    if (!--m_cRef) {
        --g_cObj;
        delete this;
        return 0;
    }
    return m_cRef;
}

STDAPI CalculationImpl::CalcObj::Add(double a, double b, double *fRet)
{
    *fRet = a + b;
    return S_OK;
}

STDAPI CalculationImpl::CalcObj::Sub(double a, double b, double *fRet)
{
    *fRet = a - b;
    return S_OK;
}

STDAPI CalculationImpl::CalcObj::QueryInterface(const IID &riid, void **ppv)
{
    return m_pParent->QueryInterface(riid, ppv);
}

STDAPI_(ULONG) CalculationImpl::CalcObj::AddRef()
{
    return m_pParent->AddRef();
}

STDAPI_(ULONG) CalculationImpl::CalcObj::Release()
{
    return m_pParent->Release();
}