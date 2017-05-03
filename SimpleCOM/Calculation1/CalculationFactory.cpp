#include "CalculationFactory.h"
#include "CalculationImpl.h"

extern ULONG g_cLockServer;
extern ULONG g_cObj;

CalculationFactory::CalculationFactory()
{
    m_cRef = 0;
}

STDAPI CalculationFactory::CreateInstance(IUnknown *pUnkOuter, const IID &riid, void **ppv)
{
    CalculationImpl *pCalculationImpl = NULL;
    HRESULT hr = E_OUTOFMEMORY;

    if (pUnkOuter) return CLASS_E_NOAGGREGATION;

    pCalculationImpl = new CalculationImpl;
    if (!pCalculationImpl) return hr;

    hr = pCalculationImpl->QueryInterface(riid, ppv);
    if (FAILED(hr)) {
        --g_cObj;
        delete pCalculationImpl;
    }

    return hr;
}

STDAPI CalculationFactory::LockServer(BOOL fLock)
{
    if (fLock) ++g_cLockServer;
    else --g_cLockServer;
    return S_OK;
}

STDAPI CalculationFactory::QueryInterface(const IID &riid, void **ppv)
{
    if (IsEqualIID(riid, IID_IClassFactory) || IsEqualIID(riid, IID_IUnknown))
        *ppv = this;
    else {
        *ppv = 0;
        return E_NOINTERFACE;
    }
    this->AddRef();
    return S_OK;
}

STDAPI_(ULONG) CalculationFactory::AddRef()
{
    return ++m_cRef;
}

STDAPI_(ULONG) CalculationFactory::Release()
{
    if (!--m_cRef) {
        delete this;
        return 0;
    }
    return m_cRef;
}