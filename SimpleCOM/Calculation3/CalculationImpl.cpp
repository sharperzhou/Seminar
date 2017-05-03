#include "CalculationImpl.h"

extern ULONG g_cObj;

CalculationImpl::CalculationImpl()
{
    m_cRef = 0;
    ++g_cObj;
    m_pITypeInfo = NULL;
}

CalculationImpl::~CalculationImpl()
{
    if (m_pITypeInfo) m_pITypeInfo->Release();
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
    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDispatch) || IsEqualIID(riid, IID_ICalc))
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

STDAPI CalculationImpl::GetTypeInfoCount(UINT *pctinfo)
{
    *pctinfo = 1;
    return S_OK;
}

STDAPI CalculationImpl::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
    HRESULT hr;
    *ppTInfo = 0;

    if (iTInfo) hr = TYPE_E_ELEMENTNOTFOUND;
    else if (m_pITypeInfo) {
        m_pITypeInfo->AddRef();
        hr = S_OK;
    }
    else hr = LoadTypeInfo();

    if (SUCCEEDED(hr)) *ppTInfo = m_pITypeInfo;

    return hr;
}

STDAPI CalculationImpl::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    HRESULT hr = S_OK;

    if (!IsEqualIID(riid, IID_NULL)) return DISP_E_UNKNOWNINTERFACE;

    if (!m_pITypeInfo) hr = LoadTypeInfo();

    if (SUCCEEDED(hr)) hr = m_pITypeInfo->GetIDsOfNames(rgszNames, cNames, rgDispId); 

    return hr;
}

STDAPI CalculationImpl::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams,
                               VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    HRESULT hr = S_OK;

    if (!IsEqualIID(riid, IID_NULL)) return DISP_E_UNKNOWNINTERFACE;

    if (!m_pITypeInfo) hr = LoadTypeInfo();

    if (SUCCEEDED(hr)) hr = m_pITypeInfo->Invoke(this, dispIdMember, wFlags, pDispParams,
        pVarResult, pExcepInfo, puArgErr);

    return hr;
}

HRESULT CalculationImpl::LoadTypeInfo()
{
    HRESULT hr;
    ITypeLib *pITypeLib = NULL;
    if (SUCCEEDED(hr = LoadRegTypeLib(TLIBID_Calculation3, 1, 0, 0, &pITypeLib)))
    {
        if (SUCCEEDED(hr = pITypeLib->GetTypeInfoOfGuid(IID_ICalc, &m_pITypeInfo)))
        {
            pITypeLib->Release();
            m_pITypeInfo->AddRef();
        }
    }

    return hr;
}