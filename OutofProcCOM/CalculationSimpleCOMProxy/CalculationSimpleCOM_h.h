

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Oct 15 16:08:03 2017
 */
/* Compiler settings for .\CalculationSimpleCOM.idl:
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

#ifndef __CalculationSimpleCOM_h_h__
#define __CalculationSimpleCOM_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICalc_FWD_DEFINED__
#define __ICalc_FWD_DEFINED__
typedef interface ICalc ICalc;
#endif 	/* __ICalc_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICalc_INTERFACE_DEFINED__
#define __ICalc_INTERFACE_DEFINED__

/* interface ICalc */
/* [helpstring][unique][uuid][object] */ 


EXTERN_C const IID IID_ICalc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D3A4AF14-C36F-44f6-8644-B3AE2E341C0D")
    ICalc : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ double a,
            /* [in] */ double b,
            /* [out] */ double *fRet) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Sub( 
            /* [in] */ double a,
            /* [in] */ double b,
            /* [out] */ double *fRet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICalcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICalc * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICalc * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICalc * This);
        
        HRESULT ( STDMETHODCALLTYPE *Add )( 
            ICalc * This,
            /* [in] */ double a,
            /* [in] */ double b,
            /* [out] */ double *fRet);
        
        HRESULT ( STDMETHODCALLTYPE *Sub )( 
            ICalc * This,
            /* [in] */ double a,
            /* [in] */ double b,
            /* [out] */ double *fRet);
        
        END_INTERFACE
    } ICalcVtbl;

    interface ICalc
    {
        CONST_VTBL struct ICalcVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICalc_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICalc_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICalc_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICalc_Add(This,a,b,fRet)	\
    ( (This)->lpVtbl -> Add(This,a,b,fRet) ) 

#define ICalc_Sub(This,a,b,fRet)	\
    ( (This)->lpVtbl -> Sub(This,a,b,fRet) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICalc_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


