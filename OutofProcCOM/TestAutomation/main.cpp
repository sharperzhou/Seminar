#include <stdio.h>
#include "..\CalculationAutomation\ICalc2.h"
#include "..\CalculationAutomation\Server.h"

int main()
{
    ICalc2 *pCalc2 = NULL;
    IUnknown *pUnknown = NULL;
    HRESULT hr;
    double fRet;

    do {
        hr = CoInitialize(NULL);
        if (FAILED(hr)) {
            printf("Error. CoInitialize Failed.\n");
            break;
        }

        hr = CoCreateInstance(CLSID_CalculationAutomation, NULL, CLSCTX_LOCAL_SERVER,
            IID_IUnknown, (void**) &pUnknown);
        if (FAILED(hr)) {
            printf("Error. Create Instance of pUnknown Failed.\n");
            break;
        }

        hr = pUnknown->QueryInterface(IID_ICalc2, reinterpret_cast<void**>(&pCalc2));
        if (FAILED(hr)) {
            printf("Error. QueryInterface from pUnknown to pCalc2 Failed.\n");
            break;
        } 

        hr = pCalc2->Add(1.2, 3.4, &fRet);
        if (FAILED(hr)) {
            printf("Error. Call Add Method Failed.\n");
            break;
        }

        printf("1.2 + 3.4 = %f\n", fRet);
    } while (false);

    system("pause");

    if (pCalc2) pCalc2->Release();
    if (pUnknown) pUnknown->Release();
    CoUninitialize();
    return 0;
}