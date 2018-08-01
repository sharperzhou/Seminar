#pragma once
#include <QSqlDatabase>
class AccessDBA
{
public:
    AccessDBA();
    ~AccessDBA();
    bool open();
    bool is_open();
    void close();
    QSqlDatabase& database() { return m_database; }
private:
    QSqlDatabase m_database;
};
