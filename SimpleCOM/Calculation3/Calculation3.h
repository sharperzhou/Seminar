#ifndef __Calculation3_H__
#define __Calculation3_H__

#include <objbase.h>

// {4A313E30-A5D1-4fa7-A3C2-1523A3E64B06}
static const GUID CLSID_Calculation3 = 
{ 0x4a313e30, 0xa5d1, 0x4fa7, { 0xa3, 0xc2, 0x15, 0x23, 0xa3, 0xe6, 0x4b, 0x06 } };

STDAPI DllGetClassObject(const REFCLSID rclsid, const REFIID riid, void **ppv);
STDAPI DllCanUnloadNow();
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();

#endif