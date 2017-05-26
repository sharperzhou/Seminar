#include "..\\ExportDLL\\func.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("a + b = 1.2 + 3.4 = %f\n", Add(1.2, 3.4));
    printf("a - b = 1.2 - 3.4 = %f\n", Sub(1.2, 3.4));
    printf("a * b = 1.2 * 3.4 = %f\n", Mult(1.2, 3.4));
    printf("a / b = 1.2 / 3.4 = %f\n", Div(1.2, 3.4));
    system("pause");
    return 0;
}