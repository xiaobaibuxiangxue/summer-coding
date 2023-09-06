#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <set>
#include <fstream>
using namespace std;
#define BACK 0
#define DOWN 1
#define FRONT 2
#define LEFT 3
#define RIGHT 4
#define UP 5
// map��¼��ʷ��
// flag��¼·��
// check����Ƿ�ԭ
// shun90˳ʱ����ת90��
// ni90��ʱ����ת90��
// 18������
// add_map����map��
set<string> book;
int count = 0;
int n = 0;
struct cube
{
    char martrix[6][3][3];
    int path[10];
    int step = 0;
};
struct cube stack[100000];
int top = 0;
#define pop() stack[--top]
#define push(node) stack[top++] = node
string str321(char mofang[6][3][3])
{
    string s;
    for (int i1 = 0; i1 < 6; i1++)
    {
        for (int i2 = 0; i2 < 3; i2++)
        {
            for (int i3 = 0; i3 < 3; i3++)
            {
                s += mofang[i1][i2][i3];
            }
        }
    }
    // cout << s.c_str() << endl;
    return s;
}
int check(char mofang[6][3][3]) // ��֤�Ƿ�ԭ
{
    int check1(char a[3][3]);
    for (int i = 0; i < 6; i++)
    {
        if (!check1(mofang[i]))
        {
            return 0;
        }
    }
    return 1;
}
int check1(char a[3][3])
{
    char i = a[0][0];
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (i != a[x][y])
                return 0;
        }
    }
    return 1;
}
Cube shun90(char matrix[3][3])
{
    int n = 3;
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = i; j < n - i - 1; j++)
        {
            char temp = matrix[i][j];
            matrix[i][j] = matrix[n - j - 1][i];
            matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
            matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
            matrix[j][n - i - 1] = temp;
        }
    }
}
Cube ni90(char matrix[3][3])
{
    char temp;
    for (int i = 0; i < 3 / 2; i++)
    {
        for (int j = i; j < 3 - i - 1; j++)
        {
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][3 - i - 1];
            matrix[j][3 - i - 1] = matrix[3 - i - 1][3 - j - 1];
            matrix[3 - i - 1][3 - j - 1] = matrix[3 - j - 1][i];
            matrix[3 - j - 1][i] = temp;
        }
    }
}
Cube get(char need[6][3][3])

{
    FILE *fp;
    char str_temp[30][10];
    int i = 0, m = 0;
    char str[19][10];
    fp = fopen("input.txt", "r");
    if (fp != NULL)
    {
        while (fgets(str_temp[i], 1000, fp) != NULL)
        {
            if (str_temp[i][0] != '\n' && i % 5 != 0)
            {
                strcpy(str[m], str_temp[i]);
                // std::cout << str[m] << std::endl;
                m++;
            }
            i++;
        }
    }
    fclose(fp);
    for (int i = 0; i < 6; i++)
    {
        for (int i1 = 0; i1 < 3; i1++)
        {
            for (int i2 = 0; i2 < 3; i2++)
            {
                need[i][i1][i2] = str[i * 3 + i1][i2 * 2];
            }
        }
    }
}
Cube solve(char mofang[6][3][3])
{
    Cube move00(char mofang[6][3][3]);
    Cube move10(char mofang[6][3][3]);
    Cube move20(char mofang[6][3][3]);
    Cube move30(char mofang[6][3][3]);
    Cube move40(char mofang[6][3][3]);
    Cube move50(char mofang[6][3][3]);
    Cube move60(char mofang[6][3][3]);
    Cube move70(char mofang[6][3][3]);
    Cube move80(char mofang[6][3][3]);
    Cube move01(char mofang[6][3][3]);
    Cube move11(char mofang[6][3][3]);
    Cube move21(char mofang[6][3][3]);
    Cube move31(char mofang[6][3][3]);
    Cube move41(char mofang[6][3][3]);
    Cube move51(char mofang[6][3][3]);
    Cube move61(char mofang[6][3][3]);
    Cube move71(char mofang[6][3][3]);
    Cube move81(char mofang[6][3][3]);
    int check(char mofang[6][3][3]);
    if (check(mofang))
    {
    }
    string s = str321(mofang);
    if (book.count(s) >= 1)
        return;
    else
        book.insert(s);
    cout << s.c_str() << endl;
    if (count >= 2000)
        return;
    return;
}
Cube move00(char martrix[6][3][3])
{
    Cube ni90(char matrix[3][3]);
    ni90(martrix[LEFT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][i][0] = martrix[UP][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][i][0] = martrix[FRONT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][i][0] = martrix[DOWN][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][i][0] = temp[i];
    }
}
Cube move01(char martrix[6][3][3])
{
    Cube shun90(char martrix[3][3]);
    shun90(martrix[LEFT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][i][0] = martrix[DOWN][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][i][0] = martrix[FRONT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][i][0] = martrix[UP][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][i][0] = temp[i];
    }
}
Cube move10(char martrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][i][1] = martrix[DOWN][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][i][1] = martrix[FRONT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][i][1] = martrix[UP][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][i][1] = temp[i];
    }
}
Cube move11(char martrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][i][1] = martrix[UP][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][i][1] = martrix[FRONT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][i][1] = martrix[DOWN][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][i][1] = temp[i];
    }
}
Cube move21(char martrix[6][3][3])
{
    shun90(martrix[RIGHT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][i][2] = martrix[DOWN][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][i][2] = martrix[FRONT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][i][2] = martrix[UP][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][i][2] = temp[i];
    }
}
Cube move20(char martrix[6][3][3])
{
    ni90(martrix[RIGHT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][i][2] = martrix[UP][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][i][2] = martrix[FRONT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][i][2] = martrix[DOWN][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][i][2] = temp[i];
    }
}
Cube move31(char martrix[6][3][3])
{
    ni90(martrix[DOWN]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][0][i] = martrix[LEFT][2 - i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][i][0] = martrix[FRONT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][2][i] = martrix[RIGHT][2 - i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][i][2] = temp[i];
    }
}
Cube move30(char martrix[6][3][3])
{
    shun90(martrix[DOWN]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][0][i] = martrix[RIGHT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][i][2] = martrix[FRONT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][2][i] = martrix[LEFT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][i][0] = temp[2 - i];
    }
}
Cube move41(char martrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][1][i] = martrix[LEFT][2 - i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][i][1] = martrix[FRONT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][1][i] = martrix[RIGHT][2 - i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][i][1] = temp[i];
    }
}
Cube move40(char martrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][1][i] = martrix[RIGHT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][i][1] = martrix[FRONT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][1][i] = martrix[LEFT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][i][1] = temp[2 - i];
    }
}
Cube move51(char martrix[6][3][3])
{
    shun90(martrix[UP]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][2][i] = martrix[LEFT][2 - i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][i][2] = martrix[FRONT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][0][i] = martrix[RIGHT][2 - i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][i][2] = temp[i];
    }
}
Cube move50(char martrix[6][3][3])
{
    ni90(martrix[UP]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[BACK][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[BACK][2][i] = martrix[RIGHT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][i][0] = martrix[FRONT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][0][i] = martrix[LEFT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][i][2] = temp[2 - i];
    }
}
Cube move61(char martrix[6][3][3])
{
    shun90(martrix[FRONT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[UP][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][2][i] = martrix[LEFT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][2][i] = martrix[DOWN][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][0][i] = martrix[RIGHT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][2][i] = temp[i];
    }
}
Cube move60(char martrix[6][3][3])
{
    ni90(martrix[FRONT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[UP][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][2][i] = martrix[RIGHT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][2][i] = martrix[DOWN][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][0][i] = martrix[LEFT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][2][i] = temp[i];
    }
}
Cube move71(char martrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[UP][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][1][i] = martrix[LEFT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][1][i] = martrix[DOWN][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][1][i] = martrix[RIGHT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][1][i] = temp[i];
    }
}
Cube move70(char martrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[UP][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][1][i] = martrix[RIGHT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][1][i] = martrix[DOWN][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][1][i] = martrix[LEFT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][1][i] = temp[i];
    }
}
Cube move80(char martrix[6][3][3])
{
    shun90(martrix[BACK]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[UP][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][0][i] = martrix[RIGHT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][0][i] = martrix[DOWN][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][2][i] = martrix[LEFT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][0][i] = temp[i];
    }
}
Cube move81(char martrix[6][3][3])
{
    ni90(martrix[BACK]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = martrix[UP][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][0][i] = martrix[LEFT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[LEFT][0][i] = martrix[DOWN][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[DOWN][2][i] = martrix[RIGHT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[RIGHT][0][i] = temp[i];
    }
}
int main()
{
    // char o[6][10] = {"back", "down", "front", "left", "right", "up"};
    char str[6][3][3];
    get(stack[0].martrix);
    int top = 0;
    // move81(str);
    solve(stack[0].martrix);
    cout << str321(str).c_str();
    printf("%d", n);
    return 0;
}