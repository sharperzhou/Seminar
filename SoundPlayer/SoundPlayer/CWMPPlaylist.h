// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "C:\\Windows\\System32\\wmp.dll" no_namespace
// CWMPPlaylist 包装器类

class CWMPPlaylist : public COleDispatchDriver
{
public:
    CWMPPlaylist() {} // 调用 COleDispatchDriver 默认构造函数
    CWMPPlaylist(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
    CWMPPlaylist(const CWMPPlaylist& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

    // 特性
public:

    // 操作
public:


    // IWMPPlaylist 方法
public:
    long get_count()
    {
        long result;
        InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
        return result;
    }
    CString get_name()
    {
        CString result;
        InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
        return result;
    }
    void put_name(LPCTSTR newValue)
    {
        static BYTE parms[] = VTS_BSTR;
        InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
    }
    long get_attributeCount()
    {
        long result;
        InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
        return result;
    }
    CString get_attributeName(long lIndex)
    {
        CString result;
        static BYTE parms[] = VTS_I4;
        InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, lIndex);
        return result;
    }
    LPDISPATCH get_Item(long lIndex)
    {
        LPDISPATCH result;
        static BYTE parms[] = VTS_I4;
        InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, lIndex);
        return result;
    }
    CString getItemInfo(LPCTSTR bstrName)
    {
        CString result;
        static BYTE parms[] = VTS_BSTR;
        InvokeHelper(0xcb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, bstrName);
        return result;
    }
    void setItemInfo(LPCTSTR bstrName, LPCTSTR bstrValue)
    {
        static BYTE parms[] = VTS_BSTR VTS_BSTR;
        InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, bstrName, bstrValue);
    }
    BOOL get_isIdentical(LPDISPATCH pIWMPPlaylist)
    {
        BOOL result;
        static BYTE parms[] = VTS_DISPATCH;
        InvokeHelper(0xd5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, pIWMPPlaylist);
        return result;
    }
    void clear()
    {
        InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
    }
    void insertItem(long lIndex, LPDISPATCH pIWMPMedia)
    {
        static BYTE parms[] = VTS_I4 VTS_DISPATCH;
        InvokeHelper(0xce, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, lIndex, pIWMPMedia);
    }
    void appendItem(LPDISPATCH pIWMPMedia)
    {
        static BYTE parms[] = VTS_DISPATCH;
        InvokeHelper(0xcf, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pIWMPMedia);
    }
    void removeItem(LPDISPATCH pIWMPMedia)
    {
        static BYTE parms[] = VTS_DISPATCH;
        InvokeHelper(0xd0, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pIWMPMedia);
    }
    void moveItem(long lIndexOld, long lIndexNew)
    {
        static BYTE parms[] = VTS_I4 VTS_I4;
        InvokeHelper(0xd1, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, lIndexOld, lIndexNew);
    }

    // IWMPPlaylist 属性
public:

};
