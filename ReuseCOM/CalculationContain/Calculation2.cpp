#include "Calculation2.h"
#include "..\CalculationBase\Server.h"
#include "..\CalculationBase\ICalc.h"

extern ULONG g_cLockServer;
extern ULONG g_cObj;

//CCalc2Impl实现
CCalc2Impl::CCalc2Impl(void)
{
    m_cRef = 0;
    InterlockedIncrement(&g_cObj);
}

CCalc2Impl::~CCalc2Impl(void)
{
    InterlockedDecrement(&g_cObj);
    
    if (m_pCalc) {
        m_pCalc->Release();
        m_pCalc = NULL;
    }
}

STDAPI CCalc2Impl::Multiple(double a, double b, double *fRet)
{
    *fRet = a * b;
    return S_OK;
}

STDAPI CCalc2Impl::Add(double a, double b, double *fRet)
{
    return m_pCalc->Add(a, b, fRet);
}

STDAPI CCalc2Impl::Sub(double a, double b, double *fRet)
{
    return m_pCalc->Sub(a, b, fRet);
}

STDAPI CCalc2Impl::QueryInterface(REFIID riid, void **ppvObject)
{
    *ppvObject = NULL;

    if (IID_IUnknown == riid || IID_ICalc2 == riid) {
        *ppvObject = this;
    }
    else {
        return E_NOINTERFACE;
    }

    this->AddRef();
    return S_OK;
}

STDAPI_(ULONG) CCalc2Impl::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDAPI_(ULONG) CCalc2Impl::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}

HRESULT CCalc2Impl::Init()
{
    HRESULT hr = CoCreateInstance(CLSID_CalculationBase, NULL, CLSCTX_INPROC, IID_ICalc, (void**) &m_pCalc);
    return hr;
}

//CCalc2Factory实现
CCalc2Factory::CCalc2Factory()
{
    m_cRef = 0;
}

CCalc2Factory::~CCalc2Factory()
{
}

STDAPI CCalc2Factory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject)
{
    CCalc2Impl *pCalc2Impl = NULL;
    HRESULT hr = E_OUTOFMEMORY;

    if (pUnkOuter) return CLASS_E_NOAGGREGATION;

    pCalc2Impl = new CCalc2Impl;
    if (!pCalc2Impl)
        return hr;

    hr = pCalc2Impl->Init();
    if (FAILED(hr)) {
        delete pCalc2Impl;
        return hr;
    }

    hr = pCalc2Impl->QueryInterface(riid, ppvObject);
    if (FAILED(hr))
        delete pCalc2Impl;

    return hr;
}

STDAPI CCalc2Factory::LockServer(BOOL fLock)
{
    if (fLock)
        InterlockedIncrement(&g_cLockServer);
    else
        InterlockedDecrement(&g_cLockServer);

    return S_OK;
}

STDAPI CCalc2Factory::QueryInterface(REFIID riid, void **ppvObject)
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

STDAPI_(ULONG) CCalc2Factory::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDAPI_(ULONG) CCalc2Factory::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}