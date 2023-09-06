#include <iostream>
#include <stdlib.h>

using namespace std;

// 需要填空
bool isValid(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
{
    int a[9] = {0, i1, i2, i3, i4, i5, i6, i7, i8};
    for (int i = 1; i <= 8; i++)
    {
        if ((i1 == i || i2 == i || i3 == i || i4 == i || i5 == i || i6 == i || i7 == i || i8 == i) != 1) // 检测同一行或同一列
            return false;
        for (int temp = -8; temp <= 8 - i; temp++)
        {
            if (i + temp >= 1 && temp != 0)
            {
                if ((a[i] == a[i + temp] + temp) || (a[i] == a[i + temp] - temp)) // 检测对角线
                {
                    return false;
                }
            }
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    int Num = 0;
    for (int i1 = 1; i1 <= 8; i1++)
    {
        for (int i2 = 1; i2 <= 8; i2++)
        {
            for (int i3 = 1; i3 <= 8; i3++)
            {
                for (int i4 = 1; i4 <= 8; i4++)
                {
                    for (int i5 = 1; i5 <= 8; i5++)
                    {
                        for (int i6 = 1; i6 <= 8; i6++)
                        {
                            for (int i7 = 1; i7 <= 8; i7++)
                            {
                                for (int i8 = 1; i8 <= 8; i8++)
                                {
                                    if (isValid(i1, i2, i3, i4, i5, i6, i7, i8))
                                    {
                                        Num++;
                                        printf("solution %d: %d %d %d %d %d %d %d\n", Num, i1, i2, i3, i4, i5, i6, i7, i8);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d", Num);
    return 0;
}
// 92个解