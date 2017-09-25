#include "Server.h"
#include "Calculation.h"

ULONG g_cLockServer = 0;
ULONG g_cObj = 0;

BOOL APIENTRY DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
{
    return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    CCalcFactory *pCalcFactory = NULL;
    HRESULT hr = E_OUTOFMEMORY;

    if (CLSID_CalculationBase != rclsid) return CLASS_E_CLASSNOTAVAILABLE;

    pCalcFactory = new CCalcFactory;
    if (!pCalcFactory)
        return hr;

    hr = pCalcFactory->QueryInterface(riid, ppv);
    if (FAILED(hr))
        delete pCalcFactory;

    return hr;
}

STDAPI DllCanUnloadNow()
{
    if (g_cObj || g_cLockServer)
        return S_FALSE;
    else
        return S_OK;
}

STDAPI DllRegisterServer()
{
    return S_OK;
}

STDAPI DllUnregisterServer()
{
    return S_OK;
}