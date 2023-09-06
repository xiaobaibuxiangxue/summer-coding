#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <queue>
#include <cstring>
#include <vector>
#include <math.h>
using namespace std;
#define INF 10000
#define maxn 30
#define maxm 40
#define threshold 6
#define my_id 2022201538
#define FANWEI 5
#define LIST_MAX 200
struct Head
{
    int x;
    int y;
    int id;
} myhead;
int map[maxn][maxm];
int rtime, object_num, player_num;
int count;
struct Object
{
    int x;
    int y;
    int value;
} *o, list[LIST_MAX];

struct Player
{
    int id;
    int len;
    struct Head head;
    int score;
    int direct;
    int shield_cd;
    int shield_time;
} *p, me;
int move_x[4] = {0, -1, 0, 1};
int move_y[4] = {-1, 0, 1, 0};
int body[2];
float action[7];
bool safed = (me.shield_time >= 2);
// 陷阱-10
// 头附近-7
// 自己身-1
// 别人身体-5
// 别人头 -5
void get_info()
{ // 获取输入信息
    int xx, yy;
    scanf("%d", &rtime);      // 游戏剩余时间
    scanf("%d", &object_num); // 地图上物品的个数
    o = new struct Object[object_num];
    for (int i = 0; i < object_num; i++)
    {
        scanf("%d %d %d", &o[i].x, &o[i].y, &o[i].value); // 地图上物品的位置和信息
        if (map[o[i].x][o[i].y] == -10)
        {
            continue;
        }
        map[o[i].x][o[i].y] == o[i].value;
        if (o[i].value == -2)
        {
            map[o[i].x][o[i].y] = -10;
        }
    }

    scanf("%d", &player_num); // 存活的玩家数
    p = new struct Player[player_num];
    for (int i = 0; i < player_num; i++)
    {
        scanf("%d %d %d %d %d %d", &p[i].id, &p[i].len, &p[i].score, &p[i].direct, &p[i].shield_cd, &p[i].shield_time); // 存活的玩家信息
        if (p[i].id != my_id)
        {                                               // 不是自己
            scanf("%d %d", &p[i].head.x, &p[i].head.y); // 头的位置
            map[p[i].head.x][p[i].head.y] = -5;         // 头
            for (int i1 = 0; i1 <= 3; i1++)
            {
                int tempx = p[i].head.x + move_x[i1];
                int tempy = p[i].head.y + move_y[i1];
                // printf("(%d,%d)", tempx, tempy);
                if (tempx >= 0 && tempx <= 30 && tempy >= 0 && tempy <= 40)
                {
                    if (safed)
                        continue;
                    map[tempx][tempy] = -7; // 敌人的大头附近
                }
            }
            for (int j = 1; j < p[i].len; j++)
            {
                scanf("%d %d", &xx, &yy); // 身子的位置
                map[xx][yy] = -5;         // 别人身体
            }
        }
        else
        { // 是自己
            me = p[i];
            scanf("%d %d", &myhead.x, &myhead.y); // 头的位置
            scanf("%d %d", &body[0], &body[1]);   // 第一节身子
            for (int j = 2; j < p[i].len; j++)
            {
                scanf("%d %d", &xx, &yy); // 身子的位置
                if (map[xx][yy] == -5)
                    continue;
                map[xx][yy] = -1;
            }
        }
    }
}
void toolsearch(int x, int y)
{
    count = 0;
    // 随时间扩大搜索范围
    int time_factor = 3;
    if (rtime < 120)
        time_factor += 1;
    if (rtime < 60)
        time_factor += 1;

    for (int i = 0; i < object_num; i++)
    {
        // printf("%d ", o[i].x);
        // printf("%d %d %d %d\n", (o[i].x > (x - FANWEI)), o[i].x<(x + FANWEI), o[i].y>(y - FANWEI), o[i].y < (y + FANWEI));
        if ((o[i].x > (x - FANWEI * time_factor) && o[i].x < (x + FANWEI * time_factor)) &&
            o[i].y > (y - FANWEI * time_factor) && o[i].y < (y + FANWEI * time_factor) && o[i].value < 20)
        {
            list[count].x = o[i].x;
            list[count].y = o[i].y;
            list[count].value = o[i].value; // 读宝箱表
            count++;
            // printf("|%d. %d)", count, i);
            // printf(" %d ", o[i].value);
            // printf("%d\n", list[count - 1].value);
        }
        // printf("%d", list[i].value);
    }
    return;
}
int object_select(int v, int x, int y)
{ // 增加周围价值作为考量
    int temp = 0;
    temp += map[x + 1][y + 1];
    temp += map[x + 1][y];
    temp += map[x + 1][y - 1];
    temp += map[x][y - 1];
    temp += map[x][y + 1];
    temp += map[x - 1][y - 1];
    temp += map[x][y];
    temp += map[x][y + 1];
    temp *= 2;
    bool danger = false;
    int cnt = 0;
    if (!safed)
    {
        for (int i = 0; i < 4; i++) // 判断是否三方都危险，进去是死局
        {
            if (map[x + move_x[i]][y + move_y[i]] == -7 || // 头附近
                map[x + move_x[i]][y + move_y[i]] == -5 || // 别人头和身体
                map[x + move_x[i]][y + move_y[i]] == -10)  // 陷阱
                cnt++;
        }
    }
    if (cnt == 2)
    { // 两方被围堵,有点危险
        temp -= 5;
    }
    if (cnt >= 3)
        danger = true;
    // printf("danger: %d  (%d,%d)", danger, x, y);
    if (v > 0 && v < 10)
    {
        if (v >= 5)
            return danger ? -10 * v : (v * 100 + 300 + temp);
        return danger ? -10 * v : (v * 100 + temp);
    }
    else
    {
        if (v == -1)
        {
            if (me.score >= 20 && me.score <= 50) // 有套子之后多吃增长豆。
            {
                if (rtime > 120)
                    return danger ? (-20) : (500 + temp);
                else
                    return danger ? (-20) : (200 + temp);
            }
            else
            { // 没套子就降低增长豆子分。
                return danger ? (-10) : (200 + temp);
            }
        }
        else
        {
            return 10 * v + temp;
        }
    }
}

int reward_count()
{
    // printf("%d %d", body[0], body[1]);
    int x = myhead.x;
    int y = myhead.y;
    action[0] = -10000000;
    action[1] = -10000000;
    action[2] = -10000000;
    action[3] = -10000000;
    toolsearch(x, y);
    for (int i = 0; i < 4; i++) // 遍历方向
    {
        // printf("%d %d", x, y);
        float cnt = -10000000;
        x += move_x[i];
        y += move_y[i];
        // printf("(%d,%d),(%d)", x, y, map[x][y]);
        //     printf("|%d|", me.shield_time);
        //    printf("%d", hd2hd(x, y));
        bool not_body = (x != body[0] || y != body[1]);
        bool not_edge = !((x > 30 || (y > 40) || (x < 0) || (y < 0)));

        bool not_other_body = map[x][y] != -5;
        bool not_near_head = (map[x][y] != -7);
        bool not_trap = (map[x][y] != -10);
        bool xianjing = false;
        bool not_selfbody = (map[x][y] == -1);
        if (!safed)
        {
            // printf("1");
            int temp = 0;
            for (int i = 0; i < 4; i++) // 判断是否三方都危险，进去是死局
            {
                // printf("%d(%d,%d,%d)", i, x + move_x[i], y + move_y[i], map[x + move_x[i]][y + move_y[i]]);
                if (map[x + move_x[i]][y + move_y[i]] == -7 || // 头附近
                    map[x + move_x[i]][y + move_y[i]] == -5 || // 别人头和身体
                    map[x + move_x[i]][y + move_y[i]] == -10)  // 陷阱
                    temp++;
            }

            if (temp >= 3)
                xianjing = true;
        }
        // printf("%d!", xianjing);
        // printf("\nnot body: %d not edge:%d safe: %d not_other_body:%d not_near_head:%d not_trap:%d not_selfbody:%d xianjing:%d\n",
        //       not_body, not_edge, start, not_other_body, not_near_head, not_trap, not_selfbody, xianjing);

        if (not_body && not_edge)
        {
            if (safed || (not_other_body && not_near_head && not_trap && !xianjing))
            {
                cnt = 0;
                for (int i1 = 0; i1 < LIST_MAX; i1++)
                {
                    int x1 = list[i1].x;
                    int y1 = list[i1].y;
                    int v = list[i1].value;
                    // printf("v:|%d| ", v);
                    if (v != 0 && (x1 != 0 || y1 != 0) && v <= 20)
                    {
                        // printf("v:|%d| ", v);
                        // printf("|2(%d %d)", x1, y1);
                        // printf("(%d %d)", list[i1].x, list[i1].y);
                        // printf("|%.1f(%d,%d)", (fabs(x - x1) + fabs(y - y1)), x1, y1);
                        // float temp = object_select(v, x1, y1) / (.1 + (fabs(x - x1) + fabs(y - y1)));
                        // printf("score:%f\n", temp);
                        cnt += object_select(v, x1, y1) / (.01 + 0.1 * (fabs(x - x1) + fabs(y - y1)));
                    }
                }
                // printf("\n");
            }

            // printf("cnt:%.1f ", cnt);
        }
        x -= move_x[i];
        y -= move_y[i];
        action[i] = cnt;
        // printf("  (%d,%d)", body[0], body[1]);
        // printf("\n!%f\n", action[i]);
    }
    int j = 0;
    for (int i = 0; i < 4; i++)
    {
        // printf("?%f\n", action[i]);
        if (action[j] < action[i])
            j = i;
    }
    if (action[j] == -10000000 && rtime >= 10)
    {
        return 4;
    }
    return j;
}
int main()
{
    memset(map, 0, sizeof(map)); // 初始化地图
    get_info();
    int res = reward_count();
    printf("%d", res);
    return 0;
}
