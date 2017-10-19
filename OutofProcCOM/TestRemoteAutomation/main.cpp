#include <stdio.h>
#ifdef _DEBUG
#import "../debug/CalculationAutomation.tlb" no_namespace
#else
#import "../release/CalculationAutomation.tlb" no_namespace
#endif

// 下述为客户端调用DCOM的代码，客户端可以为普通用户，服务端一定要是足够权限的用户，
// 如Administrator，否则即使客户端成功调用CoCreateInstanceEx后，在调用接口时将出现
// E_ACCESSDENIED错误。

int main()
{
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
        MULTI_QI qi = {&__uuidof(ICalc2), 0, 0};
        hr = CoCreateInstanceEx(__uuidof(CalculationAutomation), NULL, CLSCTX_REMOTE_SERVER,
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

        hr = pCalc2->raw_Sub(1.2, 3.4, &ret);
        if (FAILED(hr)) {
            printf("Call Sub method of automation failed.\n");
            break;
        }
        
        printf("Automation result 1.2 - 3.4 = %f\n", ret);
    } while (false);

    system("pause");

    if (pCalc2) pCalc2->Release();
    CoUninitialize();
    return 0;
}