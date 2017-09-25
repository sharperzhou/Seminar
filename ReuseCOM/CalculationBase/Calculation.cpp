#include "Calculation.h"

extern ULONG g_cLockServer;
extern ULONG g_cObj;

//CCalcImpl实现
CCalcImpl::CCalcImpl(IUnknown *pUnknownOuter)
{
    m_cRef = 0;
    InterlockedIncrement(&g_cObj);
    m_pUnknownOuter = pUnknownOuter;
}

CCalcImpl::~CCalcImpl()
{
    InterlockedDecrement(&g_cObj);
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
    if (m_pUnknownOuter)
        return m_pUnknownOuter->QueryInterface(riid, ppvObject);
    else
        return NondelegationQueryInterface(riid, ppvObject);
}

STDAPI_(ULONG) CCalcImpl::AddRef()
{
    if (m_pUnknownOuter)
        return m_pUnknownOuter->AddRef();
    else
        return NondelegatingAddRef();
}

STDAPI_(ULONG) CCalcImpl::Release()
{
    if (m_pUnknownOuter)
        return m_pUnknownOuter->Release();
    else
        return NondelegationRelease();
}

STDAPI CCalcImpl::NondelegationQueryInterface(REFIID riid, void **ppvObject)
{
    *ppvObject = NULL;

    if (IID_IUnknown == riid) {
        *ppvObject = (INondelegatingUnknown*) this;
        ((INondelegatingUnknown*) this)->NondelegatingAddRef();
    }
    else if (IID_ICalc == riid) {
        *ppvObject = (ICalc*) this;
        ((ICalc*) this)->AddRef();
    }
    else {
        return E_NOINTERFACE;
    }

    return S_OK;
}

STDAPI_(ULONG) CCalcImpl::NondelegatingAddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDAPI_(ULONG) CCalcImpl::NondelegationRelease()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}

//CCalcFactory实现
CCalcFactory::CCalcFactory()
{
    m_cRef = 0;
}

CCalcFactory::~CCalcFactory()
{
}

STDAPI CCalcFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject)
{
    CCalcImpl *pCalcImpl = NULL;
    HRESULT hr = E_OUTOFMEMORY;

    if (pUnkOuter && (IID_IUnknown != riid)) return CLASS_E_NOAGGREGATION;

    pCalcImpl = new CCalcImpl(pUnkOuter);
    if (!pCalcImpl)
        return hr;

    hr = pCalcImpl->NondelegationQueryInterface(riid, ppvObject);
    if (FAILED(hr))
        delete pCalcImpl;
    
    return hr;
}

STDAPI CCalcFactory::LockServer(BOOL fLock)
{
    if (fLock) InterlockedIncrement(&g_cLockServer);
    else InterlockedDecrement(&g_cLockServer);

    return S_OK;
}

STDAPI CCalcFactory::QueryInterface(REFIID riid, void **ppvObject)
{
    *ppvObject = NULL;

    if (IID_IUnknown == riid || IID_IClassFactory == riid) {
        *ppvObject = this;
    }
    else {
        return E_NOINTERFACE;
    }

    this->AddRef();
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