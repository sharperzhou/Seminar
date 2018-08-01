#pragma once
#include <QModelIndexList>
class QObject;
class QSqlTableModel;
class QAbstractItemView;
class QSqlDatabase;
class QString;

class StudentModel
{
public:
    StudentModel();
    ~StudentModel();
    void create(QObject* parent, QSqlDatabase& database);
    void release();
    void setView(QAbstractItemView* view);
    bool select();
    bool insert(const QString& name, const QString& sex,
        int age, const QString& address);
    bool remove(QModelIndexList* SelIndex);
    bool update(int rowIndex, const QString& name, const QString& sex,
        int age, const QString& address);
    bool submitAll();
    void rollback();
    QSqlTableModel* table() const { return m_table; }

private:
    QSqlTableModel* m_table;
};
