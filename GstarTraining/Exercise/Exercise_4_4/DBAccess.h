#pragma once
#include "Ado.h"

class DBAccess
{
public:
    DBAccess();
    ~DBAccess();

public:
    BOOL DBAccess::executeQuery(LPCTSTR sql, CAdoRecordSet& adoRecordSet);
    long executeNonQuery(LPCTSTR sql);

private:
    CAdoConnection adoConn;
};