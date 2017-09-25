#include "Server3.h"
#include "Calculation3.h"

ULONG g_cLockServer = 0;
ULONG g_cObj = 0;

BOOL APIENTRY DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
{
    return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    CCalc3Factory *pCacl3Factory = NULL;
    HRESULT hr = E_OUTOFMEMORY;

    pCacl3Factory = new CCalc3Factory;
    if (!pCacl3Factory)
        return hr;

    hr = pCacl3Factory->QueryInterface(riid, ppv);
    if (FAILED(hr))
        delete pCacl3Factory;

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