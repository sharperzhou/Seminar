#include <stdio.h>
#include "..\CalculationSimpleCOM\ICalc.h"
#include "..\CalculationSimpleCOM\Server.h"

int main()
{
    ICalc *pCalc = NULL;
    IUnknown *pUnknown = NULL;
    HRESULT hr;
    double fRet;

    do {
        hr = CoInitialize(NULL);
        if (FAILED(hr)) {
            printf("Error. CoInitialize Failed.\n");
            break;
        }

        hr = CoCreateInstance(CLSID_CalculationSimpleCOM, NULL, CLSCTX_LOCAL_SERVER,
            IID_IUnknown, (void**) &pUnknown);
        if (FAILED(hr)) {
            printf("Error. Create Instance of pUnknown Failed.\n");
            break;
        }

        hr = pUnknown->QueryInterface(IID_ICalc, reinterpret_cast<void**>(&pCalc));
        if (FAILED(hr)) {
            printf("Error. QueryInterface from pUnknown to pCalc Failed.\n");
            break;
        } 

        hr = pCalc->Add(1.2, 3.4, &fRet);
        if (FAILED(hr)) {
            printf("Error. Call Add Method Failed.\n");
            break;
        }

        printf("1.2 + 3.4 = %f\n", fRet);
    } while (false);

    system("pause");

    if (pCalc) pCalc->Release();
    if (pUnknown) pUnknown->Release();
    CoUninitialize();
    return 0;
}