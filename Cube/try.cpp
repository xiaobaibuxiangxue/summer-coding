#include <bits/stdc++.h>
using namespace std;
struct Cube
{
    Cube() {}

    char matrix[6][3][3];
    int count;
    int path[10];
} a;
set<string> book;
queue<Cube> s;
#define BACK 0
#define DOWN 1
#define FRONT 2
#define LEFT 3
#define RIGHT 4
#define UP 5
#define MAX_STEP 5
Cube get(char need[6][3][3])
{
    FILE *fp;
    char str_temp[30][10];
    int i = 0, m = 0;
    char str[19][10];
    fp = fopen("1 step.txt", "r");
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
int check(char mofang[6][3][3]) // 验证是否复原
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
        martrix[BACK][i][0] = martrix[UP][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][i][0] = martrix[FRONT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[FRONT][i][0] = martrix[UP][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        martrix[UP][i][0] = temp[2 - i];
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
Cube action_list(int n, Cube c)
{
    switch (n)
    {
    case 1:
        move01(c.matrix);
        break;
    case 2:
        move00(c.matrix);
        break;
    case 3:
        move11(c.matrix);
    case 4:
        move10(c.matrix);
        break;
    case 5:
        move21(c.matrix);
        break;
    case 6:
        move20(c.matrix);
        break;
    case 7:
        move31(c.matrix);
        break;
    case 8:
        move30(c.matrix);
        break;
    case 9:
        move41(c.matrix);
        break;
    case 10:
        move40(c.matrix);
        break;
    case 11:
        move51(c.matrix);
        break;
    case 12:
        move50(c.matrix);
        break;
    case 13:
        move61(c.matrix);
        break;
    case 14:
        move60(c.matrix);
        break;
    case 15:
        move71(c.matrix);
        break;
    case 16:
        move70(c.matrix);
        break;
    case 17:
        move81(c.matrix);
        break;
    case 18:
        move81(c.matrix);
        break;
    }
    return c;
}
Cube solve()
{
    while (!s.empty())
    {
        Cube t = s.front();
        s.pop();
        if (check(t.matrix))
        {
            cout << "Successfully solve the magic cube!" << endl;
            cout << "Step is :" << endl;
            cout << endl;
            return;
        }
        if (t.count >= MAX_STEP)
            continue;
        else
        {
            Cube *action = new Cube();
            t.count++;
            for (int i = 0; i < 18; i++)
            {
                *action = action_list(i, t);
                (*action).path[t.count] = i;
                if (t.path[t.count - 1] == t.path[t.count - 2] && i == t.path[t.count - 1])
                    continue;
                if ((i & 1) && t.path[t.count - 1] != i - 1)
                    s.push(*action);
                if (!(i & 1) && t.path[t.count - 1] != i + 1)
                    s.push(*action);
            }
            delete action;
        }
    }
}
int main()
{
    get(a.matrix);
    a.count = 0;
    // cout << a.count;
    // Cube x1 = s.top();
    s.push(a);
    // Cube x = s.top();
    //  cout << str321(x.matrix).c_str() << x.count;
    solve();
    return 0;
}