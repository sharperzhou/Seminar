#include <Windows.h>
#include "xlcall.h"

#define NUM_FUNCTIONS 1
#define NUM_REGISTER_ARGS 11
#define MAX_LENGTH 255

static char g_Funcs[NUM_FUNCTIONS][NUM_REGISTER_ARGS][MAX_LENGTH] = 
{
    {
        " AddNum",
        " BBB",      //XLOPER: R; double: B
        " AddNum",
        " first,second",
        " 1",
        " Custom Function",
        " ",
        " ",
        " 求两数之和",
        " 第一个参数",
        " 第二个参数"
    }
};

int _stdcall xlAutoOpen()
{
    int i = 0, j = 0;
    XLOPER xlDll, xlRegArgs[NUM_REGISTER_ARGS];

    for ( ; i < NUM_FUNCTIONS; ++i)
        for ( ; j < NUM_REGISTER_ARGS; ++j)
            g_Funcs[i][j][0] = strlen(g_Funcs[i][j]) - 1;

    //register:
    Excel4(xlGetName, &xlDll, 0);

    for (j = 0; j < NUM_REGISTER_ARGS; ++j)
        xlRegArgs[j].xltype = xltypeStr;

    for (i = 0; i < NUM_FUNCTIONS; ++i) {

        for (j = 0; j < NUM_REGISTER_ARGS; ++j)
            xlRegArgs[j].val.str = g_Funcs[i][j];

        Excel4(xlfRegister, 0, NUM_REGISTER_ARGS + 1, &xlDll,
            &xlRegArgs[0], &xlRegArgs[1], &xlRegArgs[2],
            &xlRegArgs[3], &xlRegArgs[4], &xlRegArgs[5],
            &xlRegArgs[6], &xlRegArgs[7], &xlRegArgs[8],
            &xlRegArgs[9], &xlRegArgs[10]);
    }

    Excel4(xlFree, 0, 1, &xlDll);

    return 1;
}

int _stdcall xlAutoClose()
{
    //unregister:

    //Method 1:
    /*
    int i = 0, j = 0;
    XLOPER xlDll, xlRegArgs[NUM_REGISTER_ARGS], xlRegId;

    Excel4(xlGetName, &xlDll, 0);

    for (j = 0; j < NUM_REGISTER_ARGS; ++j)
        xlRegArgs[j].xltype = xltypeStr;

    for (i = 0; i < NUM_FUNCTIONS; ++i) {

        for (j = 0; j < NUM_REGISTER_ARGS; ++j)
            xlRegArgs[j].val.str = g_Funcs[i][j];

        xlRegArgs[4].val.str = "\0010";

        Excel4(xlfRegister, 0, NUM_REGISTER_ARGS + 1, &xlDll,
            &xlRegArgs[0], &xlRegArgs[1], &xlRegArgs[2],
            &xlRegArgs[3], &xlRegArgs[4], &xlRegArgs[5],
            &xlRegArgs[6], &xlRegArgs[7], &xlRegArgs[8],
            &xlRegArgs[9], &xlRegArgs[10]);

        Excel4(xlfRegisterId, &xlRegId, 2, &xlDll, &xlRegArgs[0]);

        Excel4(xlfUnregister, 0, 1, &xlRegId);
    }

    Excel4(xlFree, 0, 1, &xlDll);
    */

    //Method 2:
    int i = 0;
    XLOPER xlRegArgFuncName;
    xlRegArgFuncName.xltype = xltypeStr;

    for ( ; i < NUM_FUNCTIONS; ++i) {
        xlRegArgFuncName.val.str = g_Funcs[i][2];
        Excel4(xlfSetName, 0, 1, &xlRegArgFuncName);
    }


    return 1;
}

LPXLOPER _stdcall xlAddInManagerInfo(LPXLOPER xlAction)
{
    static XLOPER xlRet, xlName, xlTemp;

    xlTemp.xltype = xltypeInt;
    xlTemp.val.w = xltypeInt;

    Excel4(xlCoerce, &xlRet, 2, xlAction, &xlTemp);

    if (1 == xlRet.val.w) {
        xlName.xltype = xltypeStr;
        xlName.val.str = "\020Sample XLL AddIn";
    }
    else {
        xlName.xltype = xltypeErr;
        xlName.val.err = xlerrValue;
    }
    
    return &xlName;
}

double _stdcall AddNum(double a, double b)
{
    return a + b;
}

//LPXLOPER _stdcall AddNum(LPXLOPER a, LPXLOPER b)
//{
//    static XLOPER xlRet;
//    if (a->xltype == xltypeNum && b->xltype == xltypeNum) {
//        xlRet.xltype = xltypeNum;
//        xlRet.val.num = a->val.num + b->val.num;
//    }
//    else {
//        xlRet.xltype = xltypeErr;
//        xlRet.val.err = xlerrNum;
//    }
//
//    return &xlRet;
//}