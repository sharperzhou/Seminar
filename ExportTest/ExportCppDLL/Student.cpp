#define _EXPORTING
#include "Student.h"

Student::Student(void) : m_Id(0), m_Name(""), m_Gender("男"), m_Age(0)
{
}

Student::Student(int Id, string Name, string Gender, int Age) : m_Id(Id), m_Name(Name), m_Gender(Gender), m_Age(Age)
{
}

Student::~Student(void)
{
}

void Student::printInfo() {
    cout << "学号：" << m_Id
        << " 姓名：" << m_Name
        << " 性别：" << m_Gender
        << " 年龄：" << m_Age
        << endl;
}

#undef _EXPORTING