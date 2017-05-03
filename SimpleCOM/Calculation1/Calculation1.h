#ifndef __Calculation1_H__
#define __Calculation1_H__

#include <objbase.h>

// {6AD11BF8-8DDA-4492-A625-71333293526A}
static const GUID CLSID_Calculation1 = 
{ 0x6ad11bf8, 0x8dda, 0x4492, { 0xa6, 0x25, 0x71, 0x33, 0x32, 0x93, 0x52, 0x6a } };

STDAPI DllGetClassObject(const REFCLSID rclsid, const REFIID riid, void **ppv);
STDAPI DllCanUnloadNow();
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();

#endif