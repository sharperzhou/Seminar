#include "Server2.h"
#include "Calculation2.h"

ULONG g_cLockServer = 0;
ULONG g_cObj = 0;

BOOL APIENTRY DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
{
    return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    CCalc2Factory *pCalc2Factory = NULL;
    HRESULT hr = E_OUTOFMEMORY;

    pCalc2Factory = new CCalc2Factory;
    if (!pCalc2Factory)
        return hr;

    hr = pCalc2Factory->QueryInterface(riid, ppv);
    if (FAILED(hr))
        delete pCalc2Factory;

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