#include "Server.h"
#include "Calculation.h"

ULONG g_cObj = 0;
ULONG g_cLockServer = 0;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    MSG msg = {0};
    HRESULT hr;
    DWORD dwRegister;
    CCalcFactory *pCalcFactory = NULL;

    do {
        hr = CoInitialize(NULL);
        if (FAILED(hr)) {
            MessageBoxA(NULL, "Error. CoInitialize Failed.", "Tips", MB_OK | MB_ICONERROR);
            break;
        }

        pCalcFactory = new CCalcFactory;
        if (!pCalcFactory) {
            MessageBoxA(NULL, "Error. Create CCalcFactory Instance Failed.", "Tips", MB_OK | MB_ICONERROR);
            break;
        }

        pCalcFactory->AddRef();
        hr = CoRegisterClassObject(CLSID_CalculationAutomation, static_cast<IUnknown*>(pCalcFactory),
            CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &dwRegister);
        if (FAILED(hr)) {
            MessageBoxA(NULL, "Error. CoRegisterClassObject Failed.", "Tips", MB_OK | MB_ICONERROR);
            break;
        }

        while (GetMessage(&msg, NULL, 0, 0)) {
            DispatchMessage(&msg);
        }

        hr = CoRevokeClassObject(dwRegister);
        if (FAILED(hr)) {
            MessageBoxA(NULL, "Error. CoRevokeClassObject Failed.", "Tips", MB_OK | MB_ICONERROR);
            break;
        }

    } while (false);

    if (pCalcFactory) pCalcFactory->Release();

    CoUninitialize();

    return msg.wParam;
}