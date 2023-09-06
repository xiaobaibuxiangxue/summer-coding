#include <bits/stdc++.h>
using namespace std;
#define MAX 6
#define BACK 0
#define DOWN 1
#define FRONT 2
#define LEFT 3
#define RIGHT 4
#define UP 5
struct Cube // 定义cube结构体，用来装魔方
{
    char matrix[6][3][3];            // 记录魔方
    int count = 0;                   // 记录搜索深度
    int path[10];                    // 由于不会使用指针，所以增加成员来存路径。
} a;                                 // 整一个a，来初始化
queue<Cube> q;                       // 魔方的队列
set<string> book;                    // 用来保存出现过的魔方情况
string str321(char mofang[6][3][3]); // 把三维的魔方拉成一维方便存在book里面
void ni90(char matrix[3][3]);
Cube action_list(int n, Cube c); // 动作空间
void get(char need[6][3][3])     // 读取本地的文件，初始化初始魔方a
{
    FILE *fp;
    char str_temp[40][10];
    int i = 0, m = 0;
    char str[19][10];
    fp = fopen("3 steps.txt", "r");
    if (fp != NULL)
    {
        while (fgets(str_temp[i], 10, fp) != NULL)
        {
            i++;
        }
    }
    fclose(fp);
    for (int i = 0; i < 30; i++)
    {
        if (str_temp[i][0] == 'b' && str_temp[i][1] == 'a')
        {
            strcpy(str[0], str_temp[++i]);
            strcpy(str[1], str_temp[++i]);
            strcpy(str[2], str_temp[++i]);
        }
        if (str_temp[i][0] == 'd' && str_temp[i][1] == 'o')
        {
            strcpy(str[3], str_temp[++i]);
            strcpy(str[4], str_temp[++i]);
            strcpy(str[5], str_temp[++i]);
        }
        if (str_temp[i][0] == 'f' && str_temp[i][1] == 'r')
        {
            strcpy(str[6], str_temp[++i]);
            strcpy(str[7], str_temp[++i]);
            strcpy(str[8], str_temp[++i]);
        }
        if (str_temp[i][0] == 'l' && str_temp[i][1] == 'e')
        {
            strcpy(str[9], str_temp[++i]);
            strcpy(str[10], str_temp[++i]);
            strcpy(str[11], str_temp[++i]);
        }
        if (str_temp[i][0] == 'r' && str_temp[i][1] == 'i')
        {
            strcpy(str[12], str_temp[++i]);
            strcpy(str[13], str_temp[++i]);
            strcpy(str[14], str_temp[++i]);
        }
        if (str_temp[i][0] == 'u' && str_temp[i][1] == 'p')
        {
            strcpy(str[15], str_temp[++i]);
            strcpy(str[16], str_temp[++i]);
            strcpy(str[17], str_temp[++i]);
        }
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
}
int check(char mofang[6][3][3]) // 检查魔方是不是好了
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
void shun90(char matrix[3][3]) // 顺时针旋转90°
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
void ni90(char matrix[3][3]) // 逆时针旋转90°
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
Cube solve() // 解决问题的函数
{
    int n = 0;
    while (!q.empty()) // 检测队列是否为空
    {
        Cube t = q.front(); // 取出队首
        q.pop();            // 去掉队首
        if (t.count > MAX)  // 如果深度超了就退出
            break;
        if (check(t.matrix))
        {
            return t;
        }
        if (book.count(str321(t.matrix))) // 检测是否已经被记录
        {
            continue;
        }

        else
        {

            book.insert(str321(t.matrix)); // 没被记录就加入book
        }
        {
            Cube action = t;
            t.count++;
            for (int i = 1; i <= 18; i++) // 遍历十八个动作
            {
                action = action_list(i, t); // 如果右边用action的话，会出错
                action.path[t.count] = i;   // 记录路径，便于输出
                q.push(action);             // 新状态入队
            }
            n++; // n用来记录队列元素有多少
        }
    }
    printf("%d", n); // 如果没找到答案，输出n，进行原因排查。
    return a;
}
Cube move00(Cube x) // 十八个动作
{
    shun90(x.matrix[LEFT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = x.matrix[UP][i][0];
        x.matrix[UP][i][0] = x.matrix[BACK][i][0];
        x.matrix[BACK][i][0] = x.matrix[DOWN][i][0];
        x.matrix[DOWN][i][0] = x.matrix[FRONT][i][0];
        x.matrix[FRONT][i][0] = temp[i];
    }
    return x;
}
Cube move01(Cube x)
{
    ni90(x.matrix[LEFT]);
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
Cube move20(Cube cube)
{
    ni90(cube.matrix[RIGHT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][2];
        cube.matrix[BACK][i][2] = cube.matrix[DOWN][i][2];
        cube.matrix[DOWN][i][2] = cube.matrix[FRONT][i][2];
        cube.matrix[FRONT][i][2] = cube.matrix[UP][i][2];
        cube.matrix[UP][i][2] = temp[i];
    }
    return cube;
}
Cube move21(Cube cube)
{
    shun90(cube.matrix[RIGHT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][2];
        cube.matrix[BACK][i][2] = cube.matrix[UP][i][2];
        cube.matrix[UP][i][2] = cube.matrix[FRONT][i][2];
        cube.matrix[FRONT][i][2] = cube.matrix[DOWN][i][2];
        cube.matrix[DOWN][i][2] = temp[i];
    }
    return cube;
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
    return x;
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
    return x;
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
        x.matrix[RIGHT][i][0] = temp[i];
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
Cube action_list(int n, Cube c) // 为了简化代码，方便遍历动作
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
        x = move80(c);
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

    return s;
}
int main()
{
    get(a.matrix); // 初始化魔方
    q.push(a);     // 塞进队列里
    a = solve();   // 找解
    for (int i = 1; i <= 10; i++)
    {
        if (a.path[i] > 0)
        {
            printf("%d%c ", a.path[i] / 2, (a.path[i]) % 2 ? '+' : '-'); // 输出操作
        }
        else if (i == 1 && a.path[i] == 0)
        {
            cout << "no answer";
        }
    }
    cout << str321(a.matrix).c_str(); // 输出复原后的魔方图（一维）
    return 0;
}