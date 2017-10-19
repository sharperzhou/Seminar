#include "Calculation.h"

extern ULONG g_cObj;
extern ULONG g_cLockServer;

//CCalcImpl实现
CCalcImpl::CCalcImpl()
{
    m_cRef = 0;
    InterlockedIncrement(&g_cObj);
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

    if (IID_IUnknown == riid || IID_ICalc == riid) {
        *ppvObject = static_cast<ICalc*>(this);
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