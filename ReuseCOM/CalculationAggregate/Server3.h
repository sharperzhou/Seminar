#ifndef __SERVER3_H__
#define __SERVER3_H__

#include <ObjBase.h>

// {0CB64628-1E54-488e-8B8A-82FF2B208839}
static const GUID CLSID_CalculationAggregate = 
{ 0xcb64628, 0x1e54, 0x488e, { 0x8b, 0x8a, 0x82, 0xff, 0x2b, 0x20, 0x88, 0x39 } };

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv);
STDAPI DllCanUnloadNow();
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();

#endif //__SERVER3_H__