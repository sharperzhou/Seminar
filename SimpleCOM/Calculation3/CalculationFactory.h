#ifndef __CalculationFactory_H__
#define __CalculationFactory_H__

#include <Unknwn.h>

class CalculationFactory : public IClassFactory
{
public:
    STDMETHOD(CreateInstance) (IUnknown *pUnkOuter, REFIID riid, void **ppv);
    STDMETHOD(LockServer) (BOOL fLock);

    STDMETHOD(QueryInterface) (REFIID riid, void **ppv);
    STDMETHOD_(ULONG, AddRef) ();
    STDMETHOD_(ULONG, Release) ();

    CalculationFactory();

private:
    ULONG m_cRef;
};

#endif