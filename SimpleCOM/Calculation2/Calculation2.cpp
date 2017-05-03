#include "Calculation2.h"
#include "CalculationFactory.h"
#include "Registry.h"

ULONG g_cLockServer = 0;
ULONG g_cObj = 0;
HANDLE g_hModule;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    g_hModule = hModule;
    return TRUE;
}

STDAPI DllGetClassObject(const REFCLSID rclsid, const REFIID riid, void **ppv)
{
    CalculationFactory *pCalculationFactory = NULL;
    HRESULT hr = E_OUTOFMEMORY;

    if (!IsEqualCLSID(rclsid, CLSID_Calculation2)) return CLASS_E_CLASSNOTAVAILABLE;

    pCalculationFactory = new CalculationFactory;
    if (!pCalculationFactory) return hr;
    hr = pCalculationFactory->QueryInterface(riid, ppv);
    if (FAILED(hr)) delete pCalculationFactory;

    return hr;
}

STDAPI DllCanUnloadNow()
{
    return (g_cLockServer || g_cObj) ? S_FALSE : S_OK;
}

STDAPI DllRegisterServer()
{
	TCHAR szModule[1024];
	DWORD dwResult = GetModuleFileName((HMODULE) g_hModule, szModule, 1024);
	if (dwResult == 0)
        return E_FAIL;
    return RegisterServer(CLSID_Calculation2,
                            szModule, 
                            TEXT("Calculation2"),
                            TEXT("Calculation2 Component"),
                            NULL);
}

STDAPI DllUnregisterServer()
{
    return UnregisterServer(CLSID_Calculation2, TEXT("Calculation2"), NULL);
}