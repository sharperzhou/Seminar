#include "Calculation.h"

extern ULONG g_cObj;
extern ULONG g_cLockServer;

//CCalcImpl实现
CCalcImpl::CCalcImpl()
{
    m_cRef = 0;
    InterlockedIncrement(&g_cObj);

    LoadTypeInfo();
}

CCalcImpl::~CCalcImpl()
{
    InterlockedDecrement(&g_cObj);

    if (g_cLockServer == 0 && g_cObj == 0)
        PostQuitMessage(0);
}

STDAPI CCalcImpl::Add(double a, double b, double *fRet)
{
    *fRet = a + b;
    return S_OK;
}

STDAPI CCalcImpl::Sub(double a, double b, double *fRet)
{
    *fRet = a - b;
    return S_OK;
}

STDAPI CCalcImpl::QueryInterface(REFIID riid, void **ppvObject)
{
    *ppvObject = NULL;

    if (IID_IUnknown == riid || IID_ICalc2 == riid  || IID_IDispatch == riid) {
        *ppvObject = static_cast<ICalc2*>(this);
    }
    else {
        return E_NOINTERFACE;
    }

    reinterpret_cast<IUnknown*>(*ppvObject)->AddRef();
    return S_OK;
}

STDAPI_(ULONG) CCalcImpl::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDAPI_(ULONG) CCalcImpl::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}

STDAPI CCalcImpl::GetTypeInfoCount(UINT *pctinfo)
{
    *pctinfo = 1;
    return S_OK;
}

STDAPI CCalcImpl::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
    *ppTInfo = NULL;

    if (iTInfo) return TYPE_E_ELEMENTNOTFOUND;

    m_pTypeInfo->AddRef();
    *ppTInfo = m_pTypeInfo;

    return S_OK;
}

STDAPI CCalcImpl::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    if (IID_NULL != riid) return DISP_E_UNKNOWNINTERFACE;

    return m_pTypeInfo->GetIDsOfNames(rgszNames, cNames, rgDispId);
}

STDAPI CCalcImpl::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
                         DISPPARAMS *pDispParams, VARIANT *pVarResult,
                         EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    if (IID_NULL != riid) return DISP_E_UNKNOWNINTERFACE;

    return m_pTypeInfo->Invoke(this, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
}

HRESULT CCalcImpl::LoadTypeInfo()
{
    ITypeLib *pTypeLib = NULL;
    HRESULT hr;

    do {
        //Load type library
        hr = LoadRegTypeLib(TLIBID_CalculationAutomation, 1, 0, 0, &pTypeLib);
        if (FAILED(hr))
            break;
        //Get Type Info for Interface
        hr = pTypeLib->GetTypeInfoOfGuid(IID_ICalc2, &m_pTypeInfo);
        if (FAILED(hr))
            break;
    } while (false);

    if (pTypeLib) pTypeLib->Release();

    return hr;
}

//CCalcFactory实现
CCalcFactory::CCalcFactory()
{
    m_cRef = 0;
}

CCalcFactory::~CCalcFactory()
{
    if (g_cLockServer == 0 && g_cObj == 0)
        PostQuitMessage(0);
}

STDAPI CCalcFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject)
{
    CCalcImpl *pCalcImpl = NULL;
    HRESULT hr = E_OUTOFMEMORY;

    if (pUnkOuter) {
        return CLASS_E_NOAGGREGATION;
    }

    pCalcImpl = new CCalcImpl;
    if (!pCalcImpl) {
        return hr;
    }

    hr = pCalcImpl->QueryInterface(riid, ppvObject);
    if (FAILED(hr)) {
        delete pCalcImpl;
    }

    return hr;
}

STDAPI CCalcFactory::LockServer(BOOL fLock)
{
    if (fLock)
        InterlockedIncrement(&g_cLockServer);
    else
        InterlockedDecrement(&g_cLockServer);

    return S_OK;
}

STDAPI CCalcFactory::QueryInterface(REFIID riid, void **ppvObject)
{
    *ppvObject = NULL;

    if (IID_IUnknown == riid || IID_IClassFactory == riid) {
        *ppvObject = static_cast<IClassFactory*>(this);
    }
    else {
        return E_NOINTERFACE;
    }

    reinterpret_cast<IUnknown*>(*ppvObject)->AddRef();
    return S_OK;
}

STDAPI_(ULONG) CCalcFactory::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDAPI_(ULONG) CCalcFactory::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}