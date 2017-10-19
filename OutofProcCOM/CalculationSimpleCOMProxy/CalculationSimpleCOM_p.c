

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "CalculationSimpleCOM_h.h"

#define TYPE_FORMAT_STRING_SIZE   7                                 
#define PROC_FORMAT_STRING_SIZE   97                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _CalculationSimpleCOM_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } CalculationSimpleCOM_MIDL_TYPE_FORMAT_STRING;

typedef struct _CalculationSimpleCOM_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } CalculationSimpleCOM_MIDL_PROC_FORMAT_STRING;

typedef struct _CalculationSimpleCOM_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } CalculationSimpleCOM_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const CalculationSimpleCOM_MIDL_TYPE_FORMAT_STRING CalculationSimpleCOM__MIDL_TypeFormatString;
extern const CalculationSimpleCOM_MIDL_PROC_FORMAT_STRING CalculationSimpleCOM__MIDL_ProcFormatString;
extern const CalculationSimpleCOM_MIDL_EXPR_FORMAT_STRING CalculationSimpleCOM__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ICalc_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICalc_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const CalculationSimpleCOM_MIDL_PROC_FORMAT_STRING CalculationSimpleCOM__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Add */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 10 */	NdrFcShort( 0x20 ),	/* 32 */
/* 12 */	NdrFcShort( 0x2c ),	/* 44 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter a */

/* 24 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter b */

/* 30 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 32 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 34 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter fRet */

/* 36 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 38 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 40 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 42 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 44 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 46 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Sub */

/* 48 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 50 */	NdrFcLong( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0x4 ),	/* 4 */
/* 56 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 58 */	NdrFcShort( 0x20 ),	/* 32 */
/* 60 */	NdrFcShort( 0x2c ),	/* 44 */
/* 62 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 64 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x0 ),	/* 0 */
/* 70 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter a */

/* 72 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 74 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 76 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter b */

/* 78 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 80 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 82 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter fRet */

/* 84 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 86 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 88 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 90 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 92 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 94 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const CalculationSimpleCOM_MIDL_TYPE_FORMAT_STRING CalculationSimpleCOM__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ICalc, ver. 0.0,
   GUID={0xD3A4AF14,0xC36F,0x44f6,{0x86,0x44,0xB3,0xAE,0x2E,0x34,0x1C,0x0D}} */

#pragma code_seg(".orpc")
static const unsigned short ICalc_FormatStringOffsetTable[] =
    {
    0,
    48
    };

static const MIDL_STUBLESS_PROXY_INFO ICalc_ProxyInfo =
    {
    &Object_StubDesc,
    CalculationSimpleCOM__MIDL_ProcFormatString.Format,
    &ICalc_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICalc_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    CalculationSimpleCOM__MIDL_ProcFormatString.Format,
    &ICalc_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _ICalcProxyVtbl = 
{
    &ICalc_ProxyInfo,
    &IID_ICalc,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ICalc::Add */ ,
    (void *) (INT_PTR) -1 /* ICalc::Sub */
};

const CInterfaceStubVtbl _ICalcStubVtbl =
{
    &IID_ICalc,
    &ICalc_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    CalculationSimpleCOM__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _CalculationSimpleCOM_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ICalcProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _CalculationSimpleCOM_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ICalcStubVtbl,
    0
};

PCInterfaceName const _CalculationSimpleCOM_InterfaceNamesList[] = 
{
    "ICalc",
    0
};


#define _CalculationSimpleCOM_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _CalculationSimpleCOM, pIID, n)

int __stdcall _CalculationSimpleCOM_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_CalculationSimpleCOM_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo CalculationSimpleCOM_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _CalculationSimpleCOM_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _CalculationSimpleCOM_StubVtblList,
    (const PCInterfaceName * ) & _CalculationSimpleCOM_InterfaceNamesList,
    0, /* no delegation */
    & _CalculationSimpleCOM_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

