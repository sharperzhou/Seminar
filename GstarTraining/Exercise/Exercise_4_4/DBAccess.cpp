#include "stdafx.h"
#include "Exercise_4_4.h"
#include "Exercise_4_4Dlg.h"
#include "DBAccess.h"

DBAccess::DBAccess() {
    if (!adoConn.ConnectAccess(_T("TestDataBase.mdb")))
        AfxMessageBox(_T("连接数据库异常！"));
}

DBAccess::~DBAccess() {
    adoConn.Close();
}

BOOL DBAccess::executeQuery(LPCTSTR sql, CAdoRecordSet& adoRecordSet) {
    adoRecordSet.SetAdoConnection(&adoConn);
    return adoRecordSet.Open(sql);
}

long DBAccess::executeNonQuery(LPCTSTR sql) {
    long affected = 0;
    adoConn.Execute(sql, &affected, adExecuteNoRecords);
    return affected;
}