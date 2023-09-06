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
int moveX[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
int moveY[8] = {0, 0, -1, 1, -1, 1, 1, -1};
inline int evalue(things count1)
{
    int x = count1.five * 1000000 + count1.live4 * 1000000 + count1.die4 * count1.die4 * 40000 + count1.huo3 * 10000 + count1.die3 * 3000 + count1.huo2 * 1000 + count1.die2 * 100;
    return x;
}

int evluate(int x, int y) // 评估得分
{
    count1.die2 = 0;
    count1.die3 = 0;
    count1.die4 = 0;
    count1.five = 0;
    count1.huo2 = 0;
    count1.huo3 = 0;
    count1.live4 = 0;
    chess[x][y] = mycolor;
    int xup = min(14, x + 4);
    int xdown = max(0, x - 4);
    int yup = min(14, y + 4);
    int ydown = max(0, y - 4);
    // 检测五连
    // printf("%d %d %d %d ", xup, xdown, yup, ydown);
    for (int cnt = 0; cnt < 8; cnt += 2)
    {
        int orien = 1;
        int leftx1 = 0;
        int rightx1 = 0;
        int lefty1 = 0;
        int righty1 = 0;
        int leftx2 = 0;
        int lefty2 = 0;
        int righty2 = 0;
        int rightx2 = 0;
        for (int as = 0; as < 2; as++)
        {
            for (int i = 1; i <= 4; i++)
            {

                // printf("|%d| ", cnt + as);
                // printf("(%d,%d) ", x + moveX[cnt + as] * i, y + moveY[cnt + as] * i);
                if ((x + moveX[cnt + as] * i >= xdown) && (x + moveX[cnt + as] * i <= xup) &&
                    (y + moveY[cnt + as] * i >= ydown) && (y + moveY[cnt + as] * i <= yup))
                {
                    if (chess[x][y] == chess[x + moveX[cnt + as] * i][y + moveY[cnt + as] * i])
                    {
                        orien++;
                        if (as == 0)
                        {
                            leftx1 = x + moveX[cnt + as] * (i + 1);
                            lefty1 = y + moveY[cnt + as] * (i + 1);
                            leftx2 = x + moveX[cnt + as] * (i + 2);
                            lefty2 = y + moveY[cnt + as] * (i + 2);
                        }
                        else
                        {
                            rightx1 = x + moveX[cnt + as] * (i + 1);
                            righty1 = y + moveY[cnt + as] * (i + 1);
                            rightx2 = x + moveX[cnt + as] * (i + 2);
                            righty2 = y + moveY[cnt + as] * (i + 2);
                        }
                    }
                    else
                    {
                        break;
                        // printf("/%d %d %d/", chess[x + moveX[cnt + as] * i][y + moveY[cnt + as] * i], x + moveX[cnt + as] * i, y + moveY[cnt + as] * i);
                    }
                }
            }
        }
        if (orien >= 5)
        {
            // printf("!%d ", count1.five);
            // printf("%d", orien);
            count1.five++;
        }
        else if (orien == 4)
        {
            if (chess[rightx1][righty1] == -1 && chess[leftx1][lefty1] == -1)
            {
                count1.live4++;
            }
            else if (chess[rightx1][righty1] == -1 || chess[leftx1][lefty1] == -1)
            {
                count1.die4++;
            }
        }
        else if (orien == 3)
        {
            if (chess[leftx1][lefty1] == -1 && chess[rightx1][righty1] == -1) // 左右都空
            {
                if (chess[leftx2][lefty2] == mycolor)
                {
                    count1.die4++;
                }
                if (chess[rightx2][righty2] == mycolor)
                {
                    count1.die4++;
                }
                if (chess[rightx2][righty2] == enemycolor && chess[leftx2][lefty2] == enemycolor)
                {
                    count1.die3++;
                }
                else if (chess[rightx2][righty2] == -1)
                {
                    count1.huo3++;
                }
                else if (chess[leftx2][lefty2] == -1)
                {
                    count1.huo3++;
                }
            }

            else if (chess[leftx1][lefty1] == -1 && chess[leftx2][lefty2] == mycolor)
            {

                count1.die4++;
            }

            else if (chess[rightx1][righty1] == -1 && chess[rightx2][righty2] == mycolor)
            {
                count1.die4++;
            }
        }
        else if (orien == 2)
        {
            if (chess[leftx1][lefty1] == -1 && chess[leftx2][lefty2] == -1)
            {
                if (chess[leftx2][lefty2] == -1 && chess[rightx2][righty2] == -1)
                {
                    count1.huo2++;
                }

                else if (chess[leftx1][lefty1] == -1 && chess[leftx2][lefty2] == mycolor)
                {
                    count1.huo3++;
                }

                else if (chess[rightx1][righty1] == -1 && chess[rightx2][righty2] == mycolor)
                {
                    count1.huo3++;
                }
            }

            else if (chess[leftx1][lefty1] == -1 && chess[leftx2][lefty2] == mycolor)
            {
                count1.die3++;
            }

            else if (chess[rightx1][righty1] == -1 && chess[rightx2][righty2] == mycolor)
            {
                count1.die3++;
            }
        }
        else if (orien == 1)
        {
            if (chess[leftx1][lefty1] == -1 && chess[rightx1][righty1] == -1)
            {
                if (chess[leftx2][leftx2] == -1 && chess[rightx2][righty2] == mycolor)
                {
                    count1.huo2++;
                }

                else if (chess[leftx2][leftx2] == mycolor && chess[rightx2][righty2] == -1)
                {
                    count1.huo2++;
                }

                else if (chess[leftx2][leftx2] == mycolor && chess[rightx2][righty2] == mycolor)
                {
                    count1.die3++;
                }
            }

            else if (chess[leftx1][lefty1] == -1 && chess[rightx1][righty1] == enemycolor && chess[leftx2][lefty2] == mycolor)
            {

                count1.die2++;
            }

            else if (chess[leftx1][lefty1] == enemycolor && chess[rightx1][righty1] == -1 && chess[rightx2][righty2] == mycolor)
            {
                count1.die2++;
            }
        }
    }
    chess[x][y] = -1;
    return evalue(count1);
}

void search()
{
    int maxv1 = -1000;
    int maxv2 = -1000;
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (chess[i][j] == -1)
            {
                int temp = evluate(i, j);
                if (maxv1 < temp)
                {
                    maxv1 = temp;
                    x1 = i;
                    y1 = j;
                }
            }
        }
    }
    int temp = 0;
    temp = mycolor;
    mycolor = enemycolor;
    enemycolor = temp;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (chess[i][j] == -1)
            {
                int temp = evluate(i, j);
                if (maxv2 < temp)
                {
                    maxv2 = temp;
                    x2 = i;
                    y2 = j;
                }
            }
        }
    }
    if (maxv1 >= maxv2)
        cout << x1 << ' ' << y1; //<< ' ' << maxv1 << endl;
    else
        cout << x2 << ' ' << y2; //<< ' ' << maxv2;
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