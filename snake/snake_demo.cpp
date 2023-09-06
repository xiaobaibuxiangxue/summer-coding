#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;
#define INF 10000
#define maxn 30
#define maxm 40
#define threshold 6
#define my_id 2022201538

int map[maxn][maxm];
int rtime, object_num, player_num, op_num;

struct Head
{
    int x;
    int y;
    int id;
} myhead;

struct Object
{
    int x;
    int y;
    int value;
} *o;

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
                map[xx][yy] = -3;
            }
        }
        else
        { // 是自己
            me = p[i];
            scanf("%d %d", &myhead.x, &myhead.y); // 头的位置
            for (int j = 1; j < p[i].len; j++)
            {
                scanf("%d %d", &xx, &yy); // 身子的位置
            }
        }
    }
}

// 进行下一步决策
// 0为左，1为上，2为右，3为下，4为开盾
int judge()
{
    srand((unsigned)time(NULL));
    int j = rand() % 4;
    int flag = 0;
    int x = myhead.x;
    int y = myhead.y;
    while (flag < 4)
    {
        if (j == 0)
        {
            if (y > 0 && me.direct != 2 && map[x][y - 1] != -3) // 避免碰撞以及出界
                return j;
            else
            {
                j = (j + 1) % 4;
                flag++;
                continue;
            }
        }
        if (j == 1)
        {
            if (x > 0 && me.direct != 3 && map[x - 1][y] != -3) // 避免碰撞以及出界
                return j;
            else
            {
                j = (j + 1) % 4;
                flag++;
                continue;
            }
        }
        if (j == 2)
        {
            if (y < 39 && me.direct != 0 && map[x][y + 1] != -3) // 避免碰撞以及出界
                return j;
            else
            {
                j = (j + 1) % 4;
                flag++;
                continue;
            }
        }
        if (j == 3)
        {
            if (x < 29 && me.direct != 1 && map[x + 1][y] != -3) // 避免碰撞以及出界
                return j;
            else
            {
                j = (j + 1) % 4;
                flag++;
                continue;
            }
        }
    }
    return 4; // 四个方向都危险就开盾
}

int main()
{
    memset(map, 0, sizeof(map)); // 初始化地图
    get_info();
    int res = judge();
    printf("%d", res);
    return 0;
}
