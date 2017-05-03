#include "CalculationImpl.h"

extern ULONG g_cObj;

CalculationImpl::CalculationImpl()
{
    m_cRef = 0;
    ++g_cObj;
}

STDAPI CalculationImpl::Add(double a, double b, double *fRet)
{
    *fRet = a + b;
    return S_OK;
}

STDAPI CalculationImpl::Sub(double a, double b, double *fRet)
{
    *fRet = a - b;
    return S_OK;
}

STDAPI CalculationImpl::QueryInterface(const IID &riid, void **ppv)
{
    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_ICalc))
        *ppv = this;
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