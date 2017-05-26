#include "..\ExportCppDLL\Calculation.h"
#include "..\ExportCppDLL\Student.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    double a = 1.2, b = 3.4;
    Calculation calc(a, b);
    printf("a + b = %f + %f = %f\n", a, b, calc.Add());
    printf("a - b = %f - %f = %f\n", a, b, calc.Sub());
    
    Student stu(1501, "ÖÜÏþ´º", "ÄÐ", 28);
    stu.printInfo();

    system("pause");
    return 0;
}