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
#define FANWEI 30

struct Head
{
    int x;
    int y;
    int id;
} myhead;
int map[maxn][maxm];
int rtime, object_num, player_num, op_num;
int count;
struct Object
{
    int x;
    int y;
    int value;
} *o, list[100];

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
void get_info()
{ // 获取输入信息
    int xx, yy;
    scanf("%d", &rtime);      // 游戏剩余时间
    scanf("%d", &object_num); // 地图上物品的个数
    o = new struct Object[object_num];
    for (int i = 0; i < object_num; i++)
    {
        scanf("%d %d %d", &o[i].x, &o[i].y, &o[i].value); // 地图上物品的位置和信息
    }

    scanf("%d", &player_num); // 存活的玩家数
    p = new struct Player[player_num];
    for (int i = 0; i < player_num; i++)
    {
        scanf("%d %d %d %d %d %d", &p[i].id, &p[i].len, &p[i].score, &p[i].direct, &p[i].shield_cd, &p[i].shield_time); // 存活的玩家信息
        if (p[i].id != my_id)
        {                                               // 不是自己
            scanf("%d %d", &p[i].head.x, &p[i].head.y); // 头的位置
            map[p[i].head.x][p[i].head.y] = -3;
            for (int j = 1; j < p[i].len; j++)
            {
                scanf("%d %d", &xx, &yy); // 身子的位置
                map[xx][yy] = -5;
            }
        }
        else
        { // 是自己
            me = p[i];
            scanf("%d %d", &myhead.x, &myhead.y); // 头的位置
            scanf("%d %d", &body[0], &body[1]);
            for (int j = 2; j < p[i].len; j++)
            {
                scanf("%d %d", &xx, &yy); // 身子的位置
                map[xx][yy] = -1;
            }
        }
    }
}
bool hd2hd(int x, int y)
{
    int temp_x = 0;
    int temp_y = 0;
    for (int i = 0; i < player_num; i++)
    {
        if (p->direct != 4)
        {
            temp_x = p->head.x + move_x[p->direct];
            temp_y = p->head.y + move_y[p->direct];
            if (temp_x > 30 || (temp_y > 40) || (temp_x < 0) || (temp_y < 0))
            {
                map[temp_x][temp_y] = -1;
            }
        }
    }
    if ((map[x][y]) == -1)
    {
        return 1;
    }
    return 0;
}
void toolsearch(int x, int y)
{
    count = 0;
    for (int i = 0; i < object_num; i++)
    {
        // printf("%d ", o[i].x);
        // printf("%d %d %d %d\n", (o[i].x > (x - FANWEI)), o[i].x<(x + FANWEI), o[i].y>(y - FANWEI), o[i].y < (y + FANWEI));
        if ((o[i].x > (x - FANWEI) && o[i].x < (x + FANWEI)) &&
            o[i].y > (y - FANWEI) && o[i].y < (y + FANWEI))
        {
            list[i].x = o[i].x;
            list[i].y = o[i].y;
            list[i].value = o[i].value;
            count++;
            // printf(" %d\n", o[i].value);
            // printf("%d", list[i].value);
        }
        // printf("%d", list[i].value);
    }
    return;
}
inline int object_select(int v)
{
    if (v > 0)
    {
        return v * 100;
    }
    else
    {
        if (v == -1)
            return 5;
        else
            return -20;
    }
}
int reward_count()
{
    // printf("%d %d", body[0], body[1]);
    int x = myhead.x;
    int y = myhead.y;
    action[0] = -100000;
    action[1] = -100000;
    action[2] = -100000;
    action[3] = -100000;
    toolsearch(x, y);
    for (int i = 0; i < 4; i++)
    {
        // printf("%d %d", x, y);

        float cnt = -100000;
        x += move_x[i];
        y += move_y[i];
        // printf("(%d,%d),(%d)", x, y, map[x][y]);
        //  printf("|%d|", me.shield_time);
        bool not_body = x != body[0] && y != body[1];
        bool not_edge = !((x > 30 || (y > 40) || (x < 0) || (y < 0)));
        bool safe = (rtime < 240 && me.shield_time >= 2);
        bool not_other_body = map[x][y] != -5;
        if (not_body && not_edge)
        {
            if (safe || not_other_body)
            {
                cnt = 0;
                for (int i1 = 0; i1 < count; i1++)
                {
                    int x1 = list[i1].x;
                    int y1 = list[i1].y;
                    int v = list[i1].value;
                    if (v != 0)
                    {
                        // printf("|2(%d %d)", x1, y1);
                        //  printf("(%d %d)", list[i1].x, list[i1].y);
                        //  printf("|%0f ", (fabs(x - x1) + fabs(y - y1)));
                        cnt += object_select(v) / (.1 + .1 * (fabs(x - x1) + fabs(y - y1)));
                    }
                }
            }

            // printf("%f ", cnt);
        }
        x -= move_x[i];
        y -= move_y[i];
        action[i] = cnt;
        // printf("  (%d,%d)", body[0], body[1]);
        // printf("!%f\n", action[i]);
    }
    int j = 0;
    for (int i = 0; i < 4; i++)
    {
        // printf("?%f\n", action[i]);
        if (action[j] < action[i])
            j = i;
    }
    if (action[j] == -100000 && rtime >= 130)
    {
        return 4;
    }
    return j;
}
int main()
{
    memset(map, 0, sizeof(map)); // 初始化地图
    get_info();
    map[2][2] = -5;
    map[4][2] = -5;
    map[3][1] = -5;
    map[3][3] = -5;
    int res = reward_count();
    printf("%d", res);
    return 0;
}
