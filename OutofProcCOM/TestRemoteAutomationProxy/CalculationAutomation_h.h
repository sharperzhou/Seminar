

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Oct 16 13:20:24 2017
 */
/* Compiler settings for .\CalculationAutomation.IDL:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CalculationAutomation_h_h__
#define __CalculationAutomation_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICalc2_FWD_DEFINED__
#define __ICalc2_FWD_DEFINED__
typedef interface ICalc2 ICalc2;
#endif 	/* __ICalc2_FWD_DEFINED__ */


#ifndef __CalculationAutomation_FWD_DEFINED__
#define __CalculationAutomation_FWD_DEFINED__

#ifdef __cplusplus
typedef class CalculationAutomation CalculationAutomation;
#else
typedef struct CalculationAutomation CalculationAutomation;
#endif /* __cplusplus */

#endif 	/* __CalculationAutomation_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICalc2_INTERFACE_DEFINED__
#define __ICalc2_INTERFACE_DEFINED__

/* interface ICalc2 */
/* [object][helpstring][oleautomation][dual][uuid] */ 


EXTERN_C const IID IID_ICalc2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CFCC097A-8E57-485f-8C4F-C73D7A50641C")
    ICalc2 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ double a,
            /* [in] */ double b,
            /* [retval][out] */ double *fRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sub( 
            /* [in] */ double a,
            /* [in] */ double b,
            /* [retval][out] */ double *fRet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICalc2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICalc2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICalc2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICalc2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICalc2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICalc2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICalc2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICalc2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ICalc2 * This,
            /* [in] */ double a,
            /* [in] */ double b,
            /* [retval][out] */ double *fRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Sub )( 
            ICalc2 * This,
            /* [in] */ double a,
            /* [in] */ double b,
            /* [retval][out] */ double *fRet);
        
        END_INTERFACE
    } ICalc2Vtbl;

    interface ICalc2
    {
        CONST_VTBL struct ICalc2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICalc2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICalc2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICalc2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICalc2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICalc2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICalc2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICalc2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICalc2_Add(This,a,b,fRet)	\
    ( (This)->lpVtbl -> Add(This,a,b,fRet) ) 

#define ICalc2_Sub(This,a,b,fRet)	\
    ( (This)->lpVtbl -> Sub(This,a,b,fRet) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICalc2_INTERFACE_DEFINED__ */



#ifndef __CalculationAutomation_LIBRARY_DEFINED__
#define __CalculationAutomation_LIBRARY_DEFINED__

/* library CalculationAutomation */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CalculationAutomation;

EXTERN_C const CLSID CLSID_CalculationAutomation;

#ifdef __cplusplus

class DECLSPEC_UUID("565ED9C6-93FF-4e1d-9D79-EA9747BCB41B")
CalculationAutomation;
#endif
#endif /* __CalculationAutomation_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


