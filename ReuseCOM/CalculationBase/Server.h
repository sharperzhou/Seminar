#ifndef __SERVER_H__
#define __SERVER_H__

#include <ObjBase.h>

// {F9FE5466-D438-49b6-82AD-FE33A4ECFFC9}
static const GUID CLSID_CalculationBase = 
{ 0xf9fe5466, 0xd438, 0x49b6, { 0x82, 0xad, 0xfe, 0x33, 0xa4, 0xec, 0xff, 0xc9 } };

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv);
STDAPI DllCanUnloadNow();
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();

#endif //