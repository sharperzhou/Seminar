#include "AccessDBA.h"
#include <QSqlError>
#include <QDebug>

AccessDBA::AccessDBA()
{
    m_database = QSqlDatabase::addDatabase("QODBC");
    m_database.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)}; \
                                FIL={MS Access};DBQ=TestDataBase.mdb");
}

AccessDBA::~AccessDBA()
{
    close();
}

bool AccessDBA::open()
{
    if (is_open()) return true;
    bool bRet = m_database.open();
    if (!bRet)
        qDebug() << m_database.lastError().text();
    return bRet;
}

bool AccessDBA::is_open()
{
    return m_database.isOpen();
}

void AccessDBA::close()
{
    m_database.close();
}
