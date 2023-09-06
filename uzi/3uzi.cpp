#include <iostream>
#include <math.h>
#include <queue>
#include <algorithm>
#include <time.h>
using namespace std;
#define INF 1000000
#define Depth 3
int chess[15][15];
int mycolor = 1;
int enemycolor = 0;
bool flag = true; // 初始化标志
struct things
{
    int chang = 0;
    int five = 0;
    int live4 = 0;
    int die4 = 0;
    int die3 = 0;
    int huo3 = 0;
    int die2 = 0;
    int huo2 = 0;
};
things count1;
void get() // 读取输入信息
{
    cin >> mycolor;
    enemycolor = 1 - mycolor;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            cin >> chess[i][j];
            if (chess[i][j] != -1)
                flag = false;
        }
    }
}
void printchess()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            cout << chess[i][j] << ' ';
        }
        cout << '\n';
    }
}
int teststop(); // 禁手检测
// 下一步策略
// 0上1下2右3左4左上5右下6右上7左下
// minmax
int moveX[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
int moveY[8] = {0, 0, -1, 1, -1, 1, 1, -1};
inline int evalue(things count1)
{

    int x = count1.five * 100000 + count1.live4 * 50000;
    if (count1.chang)
        x += -2000;
    if (count1.die4 >= 2)
        x += 10000;
    if (count1.die4 >= 1 && count1.huo3 >= 1)
        x += 10000;
    if (count1.huo3 >= 2)
        x += 5000;
    if (count1.huo3 >= 1 && count1.die3 >= 1)
        x += 1000;
    if (count1.huo3 >= 1)
    {
        x += 300;
    }
    if (count1.die4 >= 1)
        x += 500;
    if (count1.die3 >= 2)
        x += 500;
    if (count1.die3 == 1 && count1.huo2)
        x += 500;
    if (count1.huo2 >= 2)
        x += 200;
    if (count1.huo2 == 1)
        x += 50;
    x += count1.die2 * 10;
    count1.die2 = 0;
    count1.die3 = 0;
    count1.die4 = 0;
    count1.five = 0;
    count1.huo2 = 0;
    count1.huo3 = 0;
    count1.live4 = 0;
    count1.chang = 0;
    return x;
}
// enemy min
// me max
int evluate(int x, int y, int alpha, int beta, int depth, int color) // 评估得分
{
    if (depth <= 0 && color == mycolor)
    {
        return evalue(count1);
    }
    if (depth <= 0 && color == enemycolor)
    {
        return -evalue(count1);
    }
    int nextcolor;
    nextcolor = (color == mycolor) ? enemycolor : mycolor;
    if (color == mycolor)
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                if (chess[i][j] == -1)
                {
                    chess[i][j] = color;
                    alpha = max(alpha, evluate(i, j, alpha, beta, depth - 1, nextcolor));
                    chess[i][j] = -1;
                    if (alpha >= beta)
                    {
                        return alpha;
                    }
                }
            }
        }
        return alpha;
    }
    else
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                if (chess[i][j] == -1)
                {
                    chess[i][j] = color;
                    beta = min(beta, evluate(i, j, alpha, beta, depth - 1, nextcolor));
                    chess[i][j] = -1;
                    if (alpha >= beta)
                    {
                        return beta;
                    }
                }
            }
        }
        return alpha;
    }
}
void search()
{
    int maxv1 = -1000;
    int x1 = 0;
    int y1 = 0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (chess[i][j] == -1)
            {
                int temp = evluate(i, j, -INF, INF, Depth, mycolor);
                printf("%d ", temp);
                if (maxv1 < temp)
                {
                    maxv1 = temp;
                    x1 = i;
                    y1 = j;
                }
            }
        }
    }
    // if (maxv1 >= maxv2)
    // cout << x1 << ' ' << y1 << ' ' << maxv1 << endl;
    // else
    // cout << x2 << ' ' << y2 << ' ' << maxv2;
    cout << x1 << ' ' << y1;
}

int main()
{
    get();
    if (flag)
        cout << "7 7";
    else
        search();
    return 0;
}