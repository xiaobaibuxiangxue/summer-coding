#include <bits/stdc++.h>
using namespace std;
const int N = 2;
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
queue<Cube> q;
void ni90(char matrix[3][3]);
set<string> book;
Cube action_list(int n, Cube c);
string str321(char mofang[6][3][3]);
void get(char need[6][3][3])
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
            if (str_temp[i] ==)
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
int check(char mofang[6][3][3]) // 验证是否复原
{
    for (int i = 0; i < 6; i++)
    {
        char c = mofang[i][0][0];
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                if (c != mofang[i][x][y])
                    return 0;
            }
        }
    }
    return 1;
}
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
void bfs()
{
    while (!q.empty())
    {
        Cube t = q.front();
        q.pop();
        if (check(t.matrix))
        {
            printf("%d ", t.count);
            cout << "Successfully solve the magic cube!" << endl;
            cout << endl;
            for (int i = 0; i < 10; i++)
            {
                if (t.path[i] >= 0)
                    printf("%d%d", t.path[i] / 2, t.path[i] % 2);
            }
            return;
        }
        if (book.count(str321(t.matrix)))
        {
            continue;
        }
        else
        {
            book.insert(str321(t.matrix));
        }
        if (t.count >= N)
            continue;
        else
        {
            Cube *action = new Cube();
            t.count++;
            for (int i = 0; i <= 18; i++)
            {
                *action = action_list(i, t);
                (*action).path[t.count] = i;
                if (t.path[t.count - 1] == t.path[t.count - 2] && i == t.path[t.count - 1])
                    continue;
                if ((i & 1) && t.path[t.count - 1] != i - 1)
                    q.push(*action);
                if (!(i & 1) && t.path[t.count - 1] != i + 1)
                    q.push(*action);
            }
            delete action;
        }
    }
}
Cube move00(Cube cube)
{
    ni90(cube.matrix[LEFT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][0] = cube.matrix[UP][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][0] = cube.matrix[FRONT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][0] = cube.matrix[DOWN][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][0] = temp[i];
    }
    return cube;
}
Cube move01(Cube cube)
{
    shun90(cube.matrix[LEFT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][0] = cube.matrix[UP][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][0] = cube.matrix[FRONT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][0] = cube.matrix[UP][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][0] = temp[i];
    }
    return cube;
}
Cube move10(Cube cube)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][1] = cube.matrix[DOWN][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][1] = cube.matrix[FRONT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][1] = cube.matrix[UP][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][1] = temp[i];
    }
    return cube;
}
Cube move11(Cube cube)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][1] = cube.matrix[UP][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][1] = cube.matrix[FRONT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][1] = cube.matrix[DOWN][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][1] = temp[i];
    }
    return cube;
}
Cube move20(Cube cube)
{
    shun90(cube.matrix[RIGHT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][2] = cube.matrix[DOWN][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][2] = cube.matrix[FRONT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][2] = cube.matrix[UP][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][2] = temp[i];
    }
    return cube;
}
Cube move21(Cube cube)
{
    ni90(cube.matrix[RIGHT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][2] = cube.matrix[UP][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][2] = cube.matrix[FRONT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][2] = cube.matrix[DOWN][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][2] = temp[i];
    }
    return cube;
}
Cube move31(Cube cube)
{
    ni90(cube.matrix[DOWN]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][0][i] = cube.matrix[LEFT][2 - i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][0] = cube.matrix[FRONT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][2][i] = cube.matrix[RIGHT][2 - i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][2] = temp[i];
    }
    return cube;
}
Cube move30(Cube cube)
{
    shun90(cube.matrix[DOWN]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][0][i] = cube.matrix[RIGHT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][2] = cube.matrix[FRONT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][2][i] = cube.matrix[LEFT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][0] = temp[2 - i];
    }
    return cube;
}
Cube move41(Cube cube)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][1][i] = cube.matrix[LEFT][2 - i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][1] = cube.matrix[FRONT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][1][i] = cube.matrix[RIGHT][2 - i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][1] = temp[i];
    }
    return cube;
}
Cube move40(Cube cube)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][1][i] = cube.matrix[RIGHT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][1] = cube.matrix[FRONT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][1][i] = cube.matrix[LEFT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][1] = temp[2 - i];
    }
    return cube;
}
Cube move51(Cube cube)
{
    shun90(cube.matrix[UP]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][2][i] = cube.matrix[LEFT][2 - i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][2] = cube.matrix[FRONT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][0][i] = cube.matrix[RIGHT][2 - i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][2] = temp[i];
    }
    return cube;
}
Cube move50(Cube cube)
{
    ni90(cube.matrix[UP]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][2][i] = cube.matrix[RIGHT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][0] = cube.matrix[FRONT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][0][i] = cube.matrix[LEFT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][2] = temp[2 - i];
    }
    return cube;
}
Cube move61(Cube cube)
{
    shun90(cube.matrix[FRONT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][2][i] = cube.matrix[LEFT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][2][i] = cube.matrix[DOWN][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][0][i] = cube.matrix[RIGHT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][2][i] = temp[i];
    }
    return cube;
}
Cube move60(Cube cube)
{
    ni90(cube.matrix[FRONT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][2][i] = cube.matrix[RIGHT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][2][i] = cube.matrix[DOWN][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][0][i] = cube.matrix[LEFT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][2][i] = temp[i];
    }
    return cube;
}
Cube move71(Cube cube)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][1][i] = cube.matrix[LEFT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][1][i] = cube.matrix[DOWN][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][1][i] = cube.matrix[RIGHT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][1][i] = temp[i];
    }
    return cube;
}
Cube move70(Cube cube)
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][1][i] = cube.matrix[RIGHT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][1][i] = cube.matrix[DOWN][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][1][i] = cube.matrix[LEFT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][1][i] = temp[i];
    }
    return cube;
}
Cube move80(Cube cube)
{
    shun90(cube.matrix[BACK]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][0][i] = cube.matrix[RIGHT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][0][i] = cube.matrix[DOWN][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][2][i] = cube.matrix[LEFT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][0][i] = temp[i];
    }
    return cube;
}
Cube move81(Cube cube)
{
    ni90(cube.matrix[BACK]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][0][i] = cube.matrix[LEFT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][0][i] = cube.matrix[DOWN][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][2][i] = cube.matrix[RIGHT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][0][i] = temp[i];
    }
    return cube;
}
Cube action_list(int n, Cube c)
{
    Cube x;
    switch (n)
    {
    case 1:
        x = move01(c);
        break;
    case 2:
        x = move00(c);
        break;
    case 3:
        x = move11(c);
    case 4:
        x = move10(c);
        break;
    case 5:
        x = move21(c);
        break;
    case 6:
        x = move20(c);
        break;
    case 7:
        x = move31(c);
        break;
    case 8:
        x = move30(c);
        break;
    case 9:
        x = move41(c);
        break;
    case 10:
        x = move40(c);
        break;
    case 11:
        x = move51(c);
        break;
    case 12:
        x = move50(c);
        break;
    case 13:
        x = move61(c);
        break;
    case 14:
        x = move60(c);
        break;
    case 15:
        x = move71(c);
        break;
    case 16:
        x = move70(c);
        break;
    case 17:
        x = move81(c);
        break;
    case 18:
        x = move81(c);
        break;
    }
    return x;
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
int main()
{
    get(a.matrix);
    q.push(a);
    // cout << str321(a.matrix).c_str();
    bfs();
    return 0;
}