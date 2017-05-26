#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

class EXPORT Student
{
public:
    Student(void);
    Student(int Id, string Name, string Gender, int Age);
    void printInfo();
public:
    ~Student(void);
private:
    int m_Id, m_Age;
    string m_Name, m_Gender;
};
