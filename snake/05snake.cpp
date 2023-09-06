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
#define FANWEI 20
#define LIST_MAX 150
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
// 陷阱-10
// 头附近-7
// 自己身-1
// 别人身体-5
void get_info()
{ // 获取输入信息
    int xx, yy;
    scanf("%d", &rtime);      // 游戏剩余时间
    scanf("%d", &object_num); // 地图上物品的个数
    o = new struct Object[object_num];
    for (int i = 0; i < object_num; i++)
    {
        scanf("%d %d %d", &o[i].x, &o[i].y, &o[i].value); // 地图上物品的位置和信息
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
            map[p[i].head.x][p[i].head.y] = -5;
            for (int i1 = 0; i1 <= 3; i1++)
            {
                int tempx = p[i].head.x + move_x[i1];
                int tempy = p[i].head.y + move_y[i1];
                // printf("(%d,%d)", tempx, tempy);
                if (tempx >= 0 && tempx <= 30 && tempy >= 0 && tempy <= 40)
                {
                    map[tempx][tempy] = -7;
                }
            }
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
void toolsearch(int x, int y)
{
    count = 0;
    for (int i = 0; i < LIST_MAX; i++)
    {
        // printf("%d ", o[i].x);
        // printf("%d %d %d %d\n", (o[i].x > (x - FANWEI)), o[i].x<(x + FANWEI), o[i].y>(y - FANWEI), o[i].y < (y + FANWEI));
        if ((o[i].x > (x - FANWEI) && o[i].x < (x + FANWEI)) &&
            o[i].y > (y - FANWEI) && o[i].y < (y + FANWEI))
        {
            list[count].x = o[i].x;
            list[count].y = o[i].y;
            list[count].value = o[i].value;
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
        return v * 10;
    }
    else
    {
        if (v == -1 && rtime >= 120)
            return 500;
        else if (v == -1)
            return 50;
        else
            return v;
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
        //    printf("|%d|", me.shield_time);
        //   printf("%d", hd2hd(x, y));
        bool not_body = (x != body[0] || y != body[1]);
        bool not_edge = !((x > 30 || (y > 40) || (x < 0) || (y < 0)));
        bool safe = (rtime < 240 && me.shield_time >= 2);
        bool not_other_body = map[x][y] != -5;
        bool not_near_head = (map[x][y] != -7);
        bool not_trap = (map[x][y] != -10);

        // bool not_selfbody = (map[x][y] = -1);
        //  printf("\nnot body: %d not edge:%d safe: %d not_other_body:%d not_near_head:%d not_trap:%d not_selfbody:%d\n",
        //       not_body,not_edge, safe, not_other_body, not_near_head, not_trap, not_selfbody);
        if (not_body && not_edge)
        {
            if (safe || (not_other_body && not_near_head && not_trap))
            {
                cnt = 0;
                for (int i1 = 0; i1 < LIST_MAX; i1++)
                {
                    int x1 = list[i1].x;
                    int y1 = list[i1].y;
                    int v = list[i1].value;
                    // printf("v:|%d| ", v);
                    if (v != 0 && (x1 != 0 && y1 != 0))
                    {
                        // printf("v:|%d| ", v);
                        //  printf("|2(%d %d)", x1, y1);
                        //   printf("(%d %d)", list[i1].x, list[i1].y);
                        // printf("|%.1f(%d,%d)", (fabs(x - x1) + fabs(y - y1)), x1, y1);
                        // float temp = object_select(v) / (.1 + (fabs(x - x1) + fabs(y - y1)));
                        // printf("%f\n", temp);
                        cnt += object_select(v) / (.01 + 0.1 * (fabs(x - x1) + fabs(y - y1)));
                    }
                }
            }

            // printf("cnt:%。1f ", cnt);
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
    int res = reward_count();
    printf("%d", res);
    return 0;
}
