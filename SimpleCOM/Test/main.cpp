#define CALCULATION3

#ifdef CALCULATION1
#include "..\Calculation1\Calculation1.h"
#include "..\Calculation1\ICalc.h"
#endif

#ifdef CALCULATION2
#include "..\Calculation2\Calculation2.h"
#include "..\Calculation2\ICalc.h"
#endif

#ifdef CALCULATION3
#include "..\Calculation3\Calculation3.h"
#include "..\Calculation3\ICalc.h"
#endif

int main()
{
    ICalc *pICalc = NULL;
    double fRet = 0;
    double a = 1.2, b = 3.4;
    HRESULT hr;

    CoInitialize(NULL);

    #ifdef CALCULATION1
    hr = CoCreateInstance(CLSID_Calculation1, NULL, CLSCTX_INPROC_SERVER, IID_ICalc, (LPVOID*) &pICalc);
    #endif

    #ifdef CALCULATION2
    hr = CoCreateInstance(CLSID_Calculation2, NULL, CLSCTX_INPROC_SERVER, IID_ICalc, (LPVOID*) &pICalc);
    #endif

    #ifdef CALCULATION3
    //hr = CoCreateInstance(CLSID_Calculation3, NULL, CLSCTX_INPROC_SERVER, IID_ICalc, (LPVOID*) &pICalc);
    
    IDispatch *pDisp = NULL;
    LPOLESTR pFuncName = L"Add";
    DISPID dispID;
    VARIANTARG vArg[2];
    VARIANT vRet;
    hr = CoCreateInstance(CLSID_Calculation3, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (LPVOID*) &pDisp);
    if (FAILED(hr)) return -1;
    hr = pDisp->GetIDsOfNames(IID_NULL, &pFuncName, 1, 0, &dispID);
    if (FAILED(hr)) return -1;
    vArg[0].vt = VT_R8; vArg[0].dblVal = b;
    vArg[1].vt = VT_R8; vArg[1].dblVal = a;

    DISPPARAMS dispParams = {vArg, NULL, 2, 0};

    hr = pDisp->Invoke(dispID, IID_NULL, 0, DISPATCH_METHOD, &dispParams, &vRet, NULL, NULL);

    fRet = vRet.dblVal;

    pDisp->Release();

    return 0;
    
    #endif
    
    system("pause");

    if (SUCCEEDED(hr)) {
        hr = pICalc->Add(a, b, &fRet);
        pICalc->Release();
    }

    CoUninitialize();
    
    
    return 0;
}