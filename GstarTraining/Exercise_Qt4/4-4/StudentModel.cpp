#include "StudentModel.h"
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QAbstractItemView>
#include <QSqlRecord>
#include <QModelIndex>
#include <QModelIndexList>

StudentModel::StudentModel() : m_table(NULL)
{
}

StudentModel::~StudentModel()
{
}

void StudentModel::create(QObject* parent, QSqlDatabase& database)
{
    m_table = new QSqlTableModel(parent, database);
    m_table->setTable("PersonInfo");
    m_table->setSort(0, Qt::AscendingOrder);
    m_table->setHeaderData(0, Qt::Horizontal, "Id");
    m_table->setHeaderData(1, Qt::Horizontal, "姓名");
    m_table->setHeaderData(2, Qt::Horizontal, "性别");
    m_table->setHeaderData(3, Qt::Horizontal, "年龄");
    m_table->setHeaderData(4, Qt::Horizontal, "地址");
}

void StudentModel::release()
{
    if (m_table != NULL) {
        delete m_table;
        m_table = NULL;
    }
}

void StudentModel::setView(QAbstractItemView* view)
{
    if (view != NULL) {
        view->setModel(m_table);
    }
}

bool StudentModel::select()
{
    return m_table->select();
}

bool StudentModel::insert(const QString& name, const QString& sex,
                          int age, const QString& address)
{
    QSqlRecord rcd = m_table->record();
    //rcd.setValue(0, 0);
    rcd.setValue(1, name);
    rcd.setValue(2, sex);
    rcd.setValue(3, age);
    rcd.setValue(4, address);
    return m_table->insertRecord(m_table->rowCount(), rcd);
}

bool StudentModel::remove(QModelIndexList* SelIndex)
{
    bool bRet = true;
    foreach (QModelIndex index, *SelIndex) {
        int curRow = index.row();
        bRet &= m_table->removeRows(curRow, 1);
    }
    return bRet;
}

bool StudentModel::update(int rowIndex, const QString& name, 
                          const QString& sex, int age, 
                          const QString& address)
{
    bool bRet = true;
    bRet &= m_table->setData(m_table->index(rowIndex, 1), name);
    bRet &= m_table->setData(m_table->index(rowIndex, 2), sex);
    bRet &= m_table->setData(m_table->index(rowIndex, 3), age);
    bRet &= m_table->setData(m_table->index(rowIndex, 4), address);
    return bRet;
}

bool StudentModel::submitAll()
{
    return m_table->submitAll();
}

void StudentModel::rollback()
{
    m_table->revertAll();
}