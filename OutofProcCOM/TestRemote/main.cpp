#include <stdio.h>
#include "..\CalculationSimpleCOM\Server.h"
#include "..\CalculationSimpleCOM\ICalc.h"

#ifdef __SERVER_H__
#undef __SERVER_H__
#endif
#ifdef __ICALC_H__
#undef __ICALC_H__
#endif

#include "..\CalculationAutomation\Server.h"
#include "..\CalculationAutomation\ICalc2.h"

// 下述为客户端调用DCOM的代码，客户端可以为普通用户，服务端一定要是足够权限的用户，
// 如Administrator，否则即使客户端成功调用CoCreateInstanceEx后，在调用接口时将出现
// E_ACCESSDENIED错误。

int main()
{
    ICalc *pCalc = NULL;
    ICalc2 *pCalc2 = NULL;
    HRESULT hr;
    double ret;

    wchar_t szInAddr[32] = {0};
    wchar_t szUserName[32] = {0};
    wchar_t szPassword[32] = {0};

    COSERVERINFO svrInfo = {0};
    COAUTHINFO authInfo = {0};
    COAUTHIDENTITY authIdentity = {0};

    printf("远程服务器IP地址：");
    wscanf_s(L"%s", szInAddr, 32);
    printf("\n远程服务器用户名：");
    wscanf_s(L"%s", szUserName, 32);
    printf("\n远程服务器密码：");
    wscanf_s(L"%s", szPassword, 32);
    printf("\n-----------------------------------------\n");

    authIdentity.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
    authIdentity.Domain = NULL;
    authIdentity.DomainLength = 0;
    authIdentity.Password = reinterpret_cast<USHORT*>(szPassword);
    authIdentity.PasswordLength = wcslen(szPassword);
    authIdentity.User = reinterpret_cast<USHORT*>(szUserName);
    authIdentity.UserLength = wcslen(szUserName);

    authInfo.dwAuthnLevel = RPC_C_AUTHN_LEVEL_CONNECT;
    authInfo.dwAuthnSvc = RPC_C_AUTHN_WINNT;
    authInfo.dwAuthzSvc = RPC_C_AUTHZ_NONE;
    authInfo.dwCapabilities = EOAC_NONE;
    authInfo.dwImpersonationLevel = RPC_C_IMP_LEVEL_IMPERSONATE;
    authInfo.pAuthIdentityData = &authIdentity;
    authInfo.pwszServerPrincName = NULL;

    svrInfo.pAuthInfo = &authInfo;
    svrInfo.pwszName = szInAddr;

    hr = CoInitialize(NULL);

    hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_NONE,
        RPC_C_IMP_LEVEL_IDENTIFY, NULL, EOAC_NONE, NULL);

    do {
        MULTI_QI qi = {&IID_ICalc, 0, 0};
        hr = CoCreateInstanceEx(CLSID_CalculationSimpleCOM, NULL, CLSCTX_REMOTE_SERVER,
            &svrInfo, 1, &qi);
        if (FAILED(hr)) {
            printf("Create instance of simple com failed.\n");
            break;
        }
        pCalc = static_cast<ICalc*>(qi.pItf);

        hr = CoSetProxyBlanket(static_cast<IUnknown*>(pCalc), authInfo.dwAuthnSvc, authInfo.dwAuthzSvc,
            NULL, authInfo.dwAuthnLevel, authInfo.dwImpersonationLevel, &authIdentity, authInfo.dwCapabilities);
        if (FAILED(hr)) {
            printf("CoSetProxyBlanket of simple com failed.\n");
            break;
        }

        hr = pCalc->Add(1.2, 3.4, &ret);
        if (FAILED(hr)) {
            printf("Call Add method of simple com failed.\n");
            break;
        }

        printf("Simple com result 1.2 + 3.4 = %f\n", ret);
    } while (false);

    do {
        MULTI_QI qi = {&IID_ICalc2, 0, 0};
        hr = CoCreateInstanceEx(CLSID_CalculationAutomation, NULL, CLSCTX_REMOTE_SERVER,
            &svrInfo, 1, &qi);
        if (FAILED(hr)) {
            printf("Create instance of automation failed.\n");
            break;
        }
        pCalc2 = static_cast<ICalc2*>(qi.pItf);

        hr = CoSetProxyBlanket(static_cast<IUnknown*>(pCalc2), authInfo.dwAuthnSvc, authInfo.dwAuthzSvc,
            NULL, authInfo.dwAuthnLevel, authInfo.dwImpersonationLevel, &authIdentity, authInfo.dwCapabilities);
        if (FAILED(hr)) {
            printf("CoSetProxyBlanket of automation failed.\n");
            break;
        }

        hr = pCalc2->Sub(1.2, 3.4, &ret);
        if (FAILED(hr)) {
            printf("Call Sub method of automation failed.\n");
            break;
        }
        
        printf("Automation result 1.2 - 3.4 = %f\n", ret);
    } while (false);

    system("pause");

    if (pCalc) pCalc->Release();
    if (pCalc2) pCalc2->Release();
    CoUninitialize();
    return 0;
}