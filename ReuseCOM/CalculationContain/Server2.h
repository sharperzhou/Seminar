#ifndef __SERVER2_H__
#define __SERVER2_H__

#include <ObjBase.h>

// {6245A8E9-997E-4283-B7F6-37EFB63CB798}
static const GUID CLSID_CalculationContain = 
{ 0x6245a8e9, 0x997e, 0x4283, { 0xb7, 0xf6, 0x37, 0xef, 0xb6, 0x3c, 0xb7, 0x98 } };

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv);
STDAPI DllCanUnloadNow();
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();

#endif //__SERVER2_H__