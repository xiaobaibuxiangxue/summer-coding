#include <iostream>
#include <math.h>
#include <queue>
#include <algorithm>
#include <time.h>
using namespace std;

int chess[15][15];
int mycolor = 1;
int enemycolor = 0;
bool flag = true; // 初始化标志
struct things
{
    int five = 0;
    int huo4 = 0;
};
things count1;
struct point
{
    int x;
    int y;
    int value;
};
int situcation[15][15];
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
int moveX[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
int moveY[8] = {0, 0, -1, 1, -1, 1, 1, -1};
int evluate(int x, int y) // 评估得分
{

    chess[x][y] = mycolor;
    int value = 0;
    int xup = min(14, x + 4);
    int xdown = max(0, x - 4);
    int yup = min(14, y + 4);
    int ydown = max(0, y - 4);
    // 检测五连
    // printf("%d %d %d %d ", xup, xdown, yup, ydown);
    for (int cnt = 0; cnt < 8; cnt += 2)
    {
        int leftx1 = 0;
        int rightx1 = 0;
        int lefty1 = 0;
        int righty1 = 0;
        int orien = 1;
        for (int as = 0; as < 2; as++)
        {

            for (int i = 0; i < 4; i++)
            {
                if ((x + moveX[cnt * 2 + as] * i >= xdown) && (x + moveX[cnt * 2 + as] * i <= xup) &&
                    (y + moveY[cnt * 2 + as] * i >= ydown) && (y + moveY[cnt * 2 + as] * i <= yup))
                {
                    if (chess[x][y] == chess[x + moveX[cnt * 2 + as] * i][y + moveY[cnt * 2 + as] * i])
                    {
                        orien++;
                        if (as == 0)
                        {
                            leftx1 = x + moveX[cnt * 2 + as] * i;
                            lefty1 = y + moveY[cnt * 2 + as] * i;
                        }
                        else
                        {
                            rightx1 = x + moveX[cnt * 2 + as] * i;
                            righty1 = y + moveY[cnt * 2 + as] * i;
                        }
                    }
                    else
                        break;
                }
            }
        }
        if (orien >= 5)
            count1.five++;
        if (orien == 4)
        {
        }
        cout << count1.five;
        /*int n = 0;
        // printf("|%d| ", cnt);
        // printf("!%d,%d!", moveX[cnt], moveY[cnt]);
        for (int i = 0; i < 5; i++)
        {
            // if ((x + moveX[cnt] * i > xup) || (x + moveX[cnt] * i < xdown) ||
            //  (y + moveY[cnt] * i > yup) || (y + moveY[cnt] * i < ydown))
            // break;
            printf("(%d,%d)", x + moveX[cnt] * i, y + moveY[cnt] * i);
            if (chess[x][y] == chess[x + moveX[cnt] * i][y + moveY[cnt] * i])
                n++;
        }
        // printf("(%d)\n", n);
        if (n == 5)
            count1.five++;*/
    }
    // 活四
    /*for (int cnt = 0; cnt < 8; cnt += 2)
    {
        int count = 0;
        for (int n = 0; n < 2; n++)
        {
            int temp = 0;
            for (int i = 0; i < 4; i++)
            {
                if (chess[x][y] == chess[x + moveX[cnt] * i][y + moveY[cnt] * i])
                    count++;
                if (chess[x][y] == chess[x + moveX[cnt + 1] * i][y + moveY[cnt + 1] * i])
                    count++;
            }
        }
        if (count < 3)
            break;
        else
        {
            int n = 0;

        }
    }*/

    // printf("%d ", count1.five);
    chess[x][y] = -1;
    // 检测中心有四个
    {
        int count = 0;
    }
}
void search()
{
    int maxvl = 0;
    int x;
    int y;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            situcation[i][j] = evluate(i, j);
            if (maxvl < situcation[i][j])
            {
                maxvl = situcation[i][j];

                x = i;
                y = j;
            }
        }
    }
    cout << maxvl << ' ';
    cout << x << ' ' << y;
}

int main()
{
    get();
    // printchess();
    evluate(6, 5);
    if (flag)
        cout << "7"
             << " "
             << "7";
    else
        // search();

        return 0;
}