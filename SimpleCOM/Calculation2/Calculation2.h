#ifndef __Calculation2_H__
#define __Calculation2_H__

#include <objbase.h>

// {47265619-8902-410f-A8A3-1A9BA5967891}
static const GUID CLSID_Calculation2 = 
{ 0x47265619, 0x8902, 0x410f, { 0xa8, 0xa3, 0x1a, 0x9b, 0xa5, 0x96, 0x78, 0x91 } };


STDAPI DllGetClassObject(const REFCLSID rclsid, const REFIID riid, void **ppv);
STDAPI DllCanUnloadNow();
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();

#endif