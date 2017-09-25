#include "Calculation3.h"
#include "..\CalculationBase\Server.h"
#include "..\CalculationBase\ICalc.h"

extern ULONG g_cLockServer;
extern ULONG g_cObj;

//CCalc3Impl实现
CCalc3Impl::CCalc3Impl(void)
{
    m_cRef = 0;
    InterlockedIncrement(&g_cObj);
}

CCalc3Impl::~CCalc3Impl(void)
{
    InterlockedDecrement(&g_cObj);

    if (m_pUnknownInner) {
        m_pUnknownInner->Release();
        m_pUnknownInner = NULL;
    }
}


STDAPI CCalc3Impl::Divided(double a, double b, double *fRet)
{
    if (b == 0) {
        throw "Divided by zero.";
        return E_FAIL;
    }

    *fRet = a / b;
    return S_OK;
}

STDAPI CCalc3Impl::Add(double a, double b, double *fRet)
{
    ICalc *pICalc;
    HRESULT hr = m_pUnknownInner->QueryInterface(IID_ICalc, (void**) &pICalc);
    if (SUCCEEDED(hr)) {
        hr = pICalc->Add(a, b, fRet);
    }
    pICalc->Release();
    return hr;
}

STDAPI CCalc3Impl::Sub(double a, double b, double *fRet)
{
    ICalc *pICalc;
    HRESULT hr = m_pUnknownInner->QueryInterface(IID_ICalc, (void**) &pICalc);
    if (SUCCEEDED(hr)) {
        hr = pICalc->Sub(a, b, fRet);
    }
    pICalc->Release();
    return hr;
}

STDAPI CCalc3Impl::QueryInterface(REFIID riid, void **ppvObject)
{
    *ppvObject = NULL;

    if (IID_ICalc3 == riid || IID_IUnknown == riid) {
        *ppvObject = this;
    }
    else if (IID_ICalc == riid) {
        return m_pUnknownInner->QueryInterface(riid, ppvObject);
    }
    else {
        return E_NOINTERFACE;
    }

    this->AddRef();
    return S_OK;
}

STDAPI_(ULONG) CCalc3Impl::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDAPI_(ULONG) CCalc3Impl::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}

HRESULT CCalc3Impl::Init()
{
    HRESULT hr = CoCreateInstance(CLSID_CalculationBase, (IUnknown *)this, CLSCTX_INPROC_SERVER,
        IID_IUnknown, (void**) &m_pUnknownInner);
    if (FAILED(hr))
        return hr;

    ICalc *pCalc = NULL;
    hr = m_pUnknownInner->QueryInterface(IID_ICalc, (void**) &pCalc);
    if (FAILED(hr)) {
        m_pUnknownInner->Release();
        return hr;
    }
    pCalc->Release();
    return S_OK;
}

//CCalc3Factory实现
CCalc3Factory::CCalc3Factory()
{
    m_cRef = 0;
}

CCalc3Factory::~CCalc3Factory()
{
}

STDAPI CCalc3Factory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject)
{
    CCalc3Impl *pCalc3Impl = NULL;
    HRESULT hr = E_OUTOFMEMORY;

    if (pUnkOuter) return CLASS_E_NOAGGREGATION;
    
    pCalc3Impl = new CCalc3Impl;
    if (!pCalc3Impl)
        return hr;

    pCalc3Impl->AddRef();   //1.防止在Init中因调用pCalc->Release()使对象已经销毁
    hr = pCalc3Impl->Init();
    if (FAILED(hr)) {
        delete pCalc3Impl;
        return hr;
    }

    hr = pCalc3Impl->QueryInterface(riid, ppvObject);
    if (FAILED(hr)) {
        delete pCalc3Impl;
        return hr;
    }

    pCalc3Impl->Release();  //2.与1配对
    return hr;
}

STDAPI CCalc3Factory::LockServer(BOOL fLock)
{
    if (fLock)
        InterlockedIncrement(&g_cLockServer);
    else
        InterlockedDecrement(&g_cLockServer);

    return S_OK;
}

STDAPI CCalc3Factory::QueryInterface(REFIID riid, void **ppvObject)
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

STDAPI_(ULONG) CCalc3Factory::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

STDAPI_(ULONG) CCalc3Factory::Release()
{
    if (InterlockedDecrement(&m_cRef) == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}