#include <iostream>
#include <math.h>
#include <queue>
#include <algorithm>
#include <time.h>
using namespace std;
int cnt = 0;
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
            {
                cnt++;
                flag = false;
            }
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

    int x = count1.five * 1000000 + count1.live4 * 100000;
    if (count1.chang)
        x += -2000;
    if (count1.die4 >= 2)
        x += 100000;
    if (count1.die4 >= 1 && count1.huo3 >= 1)
        x += 100000;
    if (count1.huo3 >= 2)
        x += 100000;
    if (count1.huo3 >= 1 && count1.die3 >= 1)
        x += 10000;
    if (count1.huo3 >= 1)
    {
        x += 1000;
    }
    if (count1.die4 >= 1)
        x += 1000;
    if (count1.die3 >= 2)
        x += 500;
    if (count1.die3 == 1 && count1.huo2)
        x += 500;
    if (count1.huo2 >= 2)
        x += 300;
    if (count1.huo2 == 1)
        x += 100;
    x += count1.die2 * 10;
    return x;
}

int evluate(int x, int y, int color) // 评估得分
{
    count1.die2 = 0;
    count1.die3 = 0;
    count1.die4 = 0;
    count1.five = 0;
    count1.huo2 = 0;
    count1.huo3 = 0;
    count1.live4 = 0;
    count1.chang = 0;
    chess[x][y] = color;
    int xup = min(14, x + 4);
    int xdown = max(0, x - 4);
    int yup = min(14, y + 4);
    int ydown = max(0, y - 4);
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
        int leftx3 = 0;
        int lefty3 = 0;
        int rightx3 = 0;
        int righty3 = 0;
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
                            leftx3 = x + moveX[cnt + as] * (i + 3);
                            lefty3 = y + moveY[cnt + as] * (i + 3);
                        }
                        else
                        {
                            rightx1 = x + moveX[cnt + as] * (i + 1);
                            righty1 = y + moveY[cnt + as] * (i + 1);
                            rightx2 = x + moveX[cnt + as] * (i + 2);
                            righty2 = y + moveY[cnt + as] * (i + 2);
                            rightx3 = x + moveX[cnt + as] * (i + 3);
                            righty3 = y + moveY[cnt + as] * (i + 3);
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
        bool lx1in = (leftx1 >= 0 && leftx1 <= 14);
        bool ly1in = (lefty1 >= 0 && lefty2 <= 14);
        bool lx2in = (leftx2 >= 0 && leftx2 <= 14);
        bool ly2in = (lefty2 >= 0 && lefty2 <= 14);
        bool lx3in = (leftx3 >= 0 && leftx3 <= 14);
        bool ly3in = (lefty3 >= 0 && lefty3 <= 14);
        bool rx1in = (rightx1 >= 0 && rightx1 <= 14);
        bool ry1in = (righty1 >= 0 && righty1 <= 14);
        bool rx2in = (rightx2 >= 0 && rightx2 <= 14);
        bool ry2in = (righty2 >= 0 && righty2 <= 14);
        bool rx3in = (rightx3 >= 0 && rightx3 <= 14);
        bool ry3in = (righty3 >= 0 && righty3 <= 14);
        if (orien > 5)
            count1.chang++;
        if (orien == 5)
        {
            count1.five++;
        }
        else if (orien == 4)
        {
            if ((rx1in && ry1in && lx1in && ly1in) && (chess[rightx1][righty1] == -1 && chess[leftx1][lefty1] == -1))
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
        // printf("!%d!", orien);
    }
    chess[x][y] = -1;
    return evalue(count1);
}

int next1(int x, int y, int color)
{
    int maxv = 0;
    for (int i = x; i < 15; i++)
    {
        for (int j = y; j < 15; j++)
        {
            if (chess[i][j] == -1)
            {
                int temp = evluate(i, j, color);
                if (temp > maxv)
                {
                    maxv = temp;
                }
            }
        }
    }
    return maxv;
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
                int temp = evluate(i, j, mycolor);
                // printf("|%d|", temp);
                if (maxv1 < temp)
                {
                    chess[i][j] = mycolor;
                    int temp2 = next1(i, j, enemycolor);
                    // printf("%d!\n", temp2);
                    temp -= temp2;
                    if (maxv1 < temp)
                    {
                        maxv1 = temp;
                        x1 = i;
                        y1 = j;
                        // printf("%d", temp);
                    }
                    chess[i][j] = -1;
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
                int temp = evluate(i, j, mycolor);
                // printf("|%d|", temp);
                if (maxv2 < temp)
                {
                    chess[i][j] = mycolor;
                    int temp2 = next1(i, j, enemycolor);
                    // printf("%d!\n", temp2);
                    temp -= temp2;
                    if (maxv2 < temp)
                    {
                        maxv2 = temp;
                        x2 = i;
                        y2 = j;
                        // printf("%d", temp);
                    }
                    chess[i][j] = -1;
                }
            }
        }
    }
    // if (maxv1 >= maxv2)
    //     cout << x1 << ' ' << y1 << ' ' << maxv1 << endl;
    // else
    //    cout << x2 << ' ' << y2 << ' ' << maxv2;
    if (maxv1 >= maxv2)
        cout << x1 << ' ' << y1;
    else
        cout << x2 << ' ' << y2;
}

int main()