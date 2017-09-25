#include <stdio.h>
#include <stdlib.h>

#include "..\CalculationBase\ICalc.h"
#include "..\CalculationBase\Server.h"

#include "..\CalculationContain\ICalc2.h"
#include "..\CalculationContain\Server2.h"

#include "..\CalculationAggregate\ICalc3.h"
#include "..\CalculationAggregate\Server3.h"


int main()
{
    
    HRESULT hr;
    double fRet;

    CoInitialize(NULL);

    //COM Containing
    ICalc2 *pCalc2 = NULL;
    hr = CoCreateInstance(CLSID_CalculationContain, NULL, CLSCTX_INPROC_SERVER, IID_ICalc2, (void**) &pCalc2);
    hr = pCalc2->Multiple(1.2, 3.4, &fRet);
    hr = pCalc2->Add(1.2, 3.4, &fRet);
    pCalc2->Release();

    //COM Aggregating
    ICalc3 *pCalc3 = NULL;
    hr = CoCreateInstance(CLSID_CalculationAggregate, NULL, CLSCTX_INPROC_SERVER, IID_ICalc3, (void**) &pCalc3);
    hr = pCalc3->Divided(1.2, 3.4, &fRet);
    hr = pCalc3->Add(1.2, 3.4, &fRet);
    pCalc3->Release();

    CoUninitialize();
    return 0;
}