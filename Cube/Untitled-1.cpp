#include <bits/stdc++.h>
using namespace std;
#define BACK 0
#define DOWN 1
#define FRONT 2
#define LEFT 3
#define RIGHT 4
#define UP 5
struct Cube
{
    Cube()
    {
        for (int i = 0; i < 10; i++)
            path[i] = -1;
    }
    char matrix[6][3][3];
    int count = 0;
    int path[10];
} a;
void shun90(char matrix[3][3])
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
void ni90(char matrix[3][3])
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
Cube move00(Cube x)
{
    ni90(x.matrix[LEFT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][i][0];
        x.matrix[UP][i][0] = x.matrix[BACK][i][0];
        x.matrix[BACK][i][0] = x.matrix[DOWN][i][0];
        x.matrix[DOWN][i][0] = x.matrix[FRONT][i][0];
        x.matrix[FRONT][i][0] = temp[i];
    }
}
Cube move01(Cube x)
{
    shun90(x.matrix[LEFT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][i][0];
        x.matrix[UP][i][0] = x.matrix[FRONT][i][0];
        x.matrix[FRONT][i][0] = x.matrix[DOWN][i][0];
        x.matrix[DOWN][i][0] = x.matrix[BACK][i][0];
        x.matrix[BACK][i][0] = temp[i];
    }
    return x;
}
Cube move10(Cube x)
{

    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][i][1];
        x.matrix[UP][i][1] = x.matrix[BACK][i][1];
        x.matrix[BACK][i][1] = x.matrix[DOWN][i][1];
        x.matrix[DOWN][i][1] = x.matrix[FRONT][i][1];
        x.matrix[FRONT][i][1] = temp[i];
    }
    return x;
}
Cube move11(Cube x)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][i][1];
        x.matrix[UP][i][1] = x.matrix[FRONT][i][1];
        x.matrix[FRONT][i][1] = x.matrix[DOWN][i][1];
        x.matrix[DOWN][i][1] = x.matrix[BACK][i][1];
        x.matrix[BACK][i][1] = temp[i];
    }
    return x;
}
Cube move20(Cube x)
{
    ni90(x.matrix[RIGHT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][i][2];
        x.matrix[UP][i][2] = x.matrix[BACK][i][2];
        x.matrix[BACK][i][2] = x.matrix[DOWN][i][2];
        x.matrix[DOWN][i][2] = x.matrix[FRONT][i][2];
        x.matrix[BACK][i][2] = temp[i];
    }
    return x;
}
Cube move21(Cube x)
{
    shun90(x.matrix[RIGHT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][i][2];
        x.matrix[UP][i][2] = x.matrix[FRONT][i][2];
        x.matrix[FRONT][i][2] = x.matrix[DOWN][i][2];
        x.matrix[DOWN][i][2] = x.matrix[BACK][i][2];
        x.matrix[BACK][i][2] = temp[i];
    }
    return x;
}
Cube move30(Cube x)
{
    ni90(x.matrix[DOWN]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[BACK][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[BACK][0][i] = x.matrix[LEFT][2 - i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][i][0] = x.matrix[FRONT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[FRONT][2][i] = x.matrix[RIGHT][2 - i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][i][2] = temp[i];
    }
}
Cube move31(Cube x)
{
    shun90(x.matrix[DOWN]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[BACK][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[BACK][0][i] = x.matrix[RIGHT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][i][2] = x.matrix[FRONT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[FRONT][2][i] = x.matrix[LEFT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][i][0] = temp[2 - i];
    }
}

Cube move40(Cube x)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[BACK][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[BACK][1][i] = x.matrix[LEFT][2 - i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][i][1] = x.matrix[FRONT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[FRONT][1][i] = x.matrix[RIGHT][2 - i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][i][1] = temp[i];
    }
    return x;
}
Cube move41(Cube x)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[BACK][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[BACK][1][i] = x.matrix[RIGHT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][i][1] = x.matrix[FRONT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[FRONT][1][i] = x.matrix[LEFT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][i][1] = temp[2 - i];
    }
    return x;
}
Cube move50(Cube x)
{
    shun90(x.matrix[UP]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[BACK][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[BACK][2][i] = x.matrix[LEFT][2 - i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][i][2] = x.matrix[FRONT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[FRONT][0][i] = x.matrix[RIGHT][2 - i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][i][2] = temp[i];
    }
    return x;
}
Cube move51(Cube x)
{
    ni90(x.matrix[UP]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[BACK][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[BACK][2][i] = x.matrix[RIGHT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][i][0] = x.matrix[FRONT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[FRONT][0][i] = x.matrix[LEFT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][i][2] = temp[2 - i];
    }
    return x;
}
Cube move60(Cube x)
{
    shun90(x.matrix[FRONT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[UP][2][i] = x.matrix[LEFT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][2][i] = x.matrix[DOWN][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[DOWN][0][i] = x.matrix[RIGHT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][2][i] = temp[i];
    }
    return x;
}
Cube move61(Cube x)
{
    ni90(x.matrix[FRONT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[UP][2][i] = x.matrix[RIGHT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][2][i] = x.matrix[DOWN][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[DOWN][0][i] = x.matrix[LEFT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][2][i] = temp[i];
    }
    return x;
}
Cube move70(Cube x)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[UP][1][i] = x.matrix[LEFT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][1][i] = x.matrix[DOWN][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[DOWN][1][i] = x.matrix[RIGHT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][1][i] = temp[i];
    }
    return x;
}
Cube move71(Cube x)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[UP][1][i] = x.matrix[RIGHT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][1][i] = x.matrix[DOWN][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[DOWN][1][i] = x.matrix[LEFT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][1][i] = temp[i];
    }
    return x;
}
Cube move81(Cube x)
{
    shun90(x.matrix[BACK]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[UP][0][i] = x.matrix[RIGHT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][0][i] = x.matrix[DOWN][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[DOWN][2][i] = x.matrix[LEFT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][0][i] = temp[i];
    }
    return x;
}
Cube move80(Cube x)
{
    ni90(x.matrix[BACK]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[UP][0][i] = x.matrix[LEFT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[LEFT][0][i] = x.matrix[DOWN][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[DOWN][2][i] = x.matrix[RIGHT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        x.matrix[RIGHT][0][i] = temp[i];
    }
    return x;
}