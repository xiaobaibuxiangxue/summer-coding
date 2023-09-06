
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_QUEENS 128    // 皇后的个数
#define MAX_NODES 1000    // 队列大小，存放最好的邻居
#define MAX_SIDE_WAYS 100 // 最多连续水平移动的次数
#define DEBUG_MODE 1      // 为0，不输出调试信息，否则输出调试信息
#define MAX_TRY 100       // 最大random restart 次数
#define NULL_STATE_VALUE -1000000
#define SH_N 5
#define SH_M 5
// 队列操作
#define put_node(st) _queue[_tl++] = st // 放入新的节点
#define get_node() _queue[_hd++];       // 获取队列头部节点
#define reset_queue() _hd = _tl = 0     // 初始化队列
#define queue_not_empty (_hd < _tl)     // 判断队列是否为空
#define reset_queue_head() _hd = 0      // 将队列头重置为0

// 状态
typedef struct state
{
    int value;           // 该状态的价值，value越大，价值越高
    int pos[NUM_QUEENS]; // 每一列皇后的位置
} state;
void generateInit(state *);
// 随机产生一个初始状态, 将状态存入输入参数指针所指向的空间
state findBestNeighbor(state);
// 找到输入状态的最好邻居
int evaluate(state);
// 评估一个状态的价值
void printSolution(state);
// 打印输出一个状态的信息
int isConflict(state);
// 判断一个状态是否是要找的结果
int try_once();
// 产生一个初始状态，并找到局部最优解;若找到了一个目标结果
// （皇后相互不冲突）返回1，否则返回0
int isEqual(state s1, state s2);
// 判断两个状态是否相同

// 注意，全局变量的命名，均以_开始
state _queue[MAX_NODES]; // 队列，存放一个状态的邻居
int _hd = 0, _tl = 0;    // 初始化队列头尾

int main()
{
    clock_t begin = clock();

    int count = 0;                     // 已经尝试的次数
    srand((unsigned int)(time(NULL))); // 设置随机序列器的种子(注意程序其他地方不要再调用srand)
    while (count++ < MAX_TRY)
    {
        if (DEBUG_MODE)
        {
            printf("*********************************\n");
            printf("begin the %d try.\n", count);
        }
        if (try_once())
        {
            break; // 找到了目标
        }
    }

    if (DEBUG_MODE)
    {
        printf("*********************");
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf("trial [%d], %g seconds\n", elapsed_secs);
    return 0;
}

/*
基于一个初始状态，进行尝试
*/
int try_once()
{
    state current, neighbor;
    generateInit(&current); // 新生成一个初始状态

    int side_away_counter = 0; // 重置水平移动次数

    if (DEBUG_MODE)
        printSolution(current); // 输出初始状态

    if (!isConflict(current))
    {
        // 初始状态即是目标
        printf("You are very lucky!\n");
        printSolution(current);
        return 1;
    }
    while (1)
    {
        if (side_away_counter >= MAX_SIDE_WAYS)
        {
            break;
        }
        // 找到一个最好的邻居
        neighbor = findBestNeighbor(current);
        if (neighbor.value == NULL_STATE_VALUE)
        {
            // 没有找到更好邻居，退出
            break;
        }
        // printf("1");
        //  如果  current 与 neighbor 价值相等，说明是水平移动
        if (current.value == neighbor.value)
        {
            side_away_counter++;
            current = _queue[side_away_counter];
        }
        // 如果 找不到更好的邻居，得到局部最优解
        if (isEqual(neighbor, current))
        {
            if (DEBUG_MODE)
                printSolution(current);
            break;
        }
        // 如果 找到更好的邻居，将连续水平移动次数置0
        if (current.value < neighbor.value)
        {
            side_away_counter = 0;
            current = neighbor;
            printSolution(current);
            reset_queue();
        }
        if (current.value >= 0)
            break;
        // 用最好的邻居更换当前状态
        // 如果邻居已经是目标
    }
    if (current.value >= 0)
    {
        printSolution(current);
        return 1;
    }

    else
    {
        return 0;
    }
    // 判断局部最优是否目标
}

// 产生一个随机状态
void generateInit(state *p_st)
{
    int i, p;

    for (i = 0; i < NUM_QUEENS; i++)
    {
        p = rand() % NUM_QUEENS;
        p_st->pos[i] = p;
    }

    p_st->value = evaluate(*p_st);
}

/*
找到当前状态的最好的邻居
邻居的定义可以是固定7个列，更换一个列的皇后的位置，这样共有8*7=56个邻居
注意，若有多个邻居的价值均等于最大值，则随机从中选择一个
*/
state findBestNeighbor(state current)
{
    state nbr, temp;
    int i, j;
    int maxvalue = NULL_STATE_VALUE;
    temp = current;
    for (i = 0; i < NUM_QUEENS; i++)
    {
        for (j = 0; j < current.pos[i]; j++)
        {
            temp.pos[i] = j;
            if ((temp.value = evaluate(temp)) > maxvalue)
            {
                maxvalue = temp.value;
                reset_queue();
                put_node(temp);
            }
            if ((temp.value = evaluate(temp)) == maxvalue)
            {
                put_node(temp);
            }
        }
        for (j = current.pos[i] + 1; j < NUM_QUEENS; j++)
        {
            temp.pos[i] = j;
            if ((temp.value = evaluate(temp)) > maxvalue)
            {
                maxvalue = temp.value;
                reset_queue();
                put_node(temp);
            }
            if ((temp.value = evaluate(temp)) == maxvalue)
            {
                put_node(temp);
            }
        }
        temp = current;
    }
    if (maxvalue == NULL_STATE_VALUE)
    {
        // 没有找到更好的邻居
        nbr.value = NULL_STATE_VALUE;
        return nbr;
    }
    else // 找到更好邻居
        return _queue[rand() % (_tl)];
}

// 判断两个状态是否相同,相同返回1，不同返回0
int isEqual(state s1, state s2)
{
    int i, num = 0;
    for (i = 0; i < NUM_QUEENS; i++)
    {
        if (s1.pos[i] == s2.pos[i])
            num++;
    }
    if (num == NUM_QUEENS)
        return 1;
    return 0;
}

// 评估一个状态的价值
// 可以将价值定义为 -1 * 可以相互攻击的皇后对数
// 提示，可以用三个数组，分别结算每行的皇后个数，
// 每条主对角线和副对角线上的皇后个数，然后计算可以相互攻击的皇后对数
// 比如，若第一行有k个皇后，则该行上可相互攻击的皇后对数为 k*(k-1)/2
int evaluate(state st)
{
    int i, j;
    int value = 0;
    for (i = 0; i < NUM_QUEENS - 1; i++)
    {
        for (j = i + 1; j < NUM_QUEENS; j++)
        {
            if (st.pos[i] == st.pos[j])
                value++;
            if ((st.pos[i] - st.pos[j]) == (i - j))
                value++;
            if ((st.pos[i] - st.pos[j]) == (j - i))
                value++;
        }
    }
    st.value = (-1 * value);
    //	printf("%d\n",st.value);
    return (st.value);
}

// 打印一个状态的信息
void printSolution(state st)
{
    int i;
    for (i = 0; i < NUM_QUEENS; i++)
    {
        printf("%d ", st.pos[i]);
    }
    printf("\n");
    printf("value is %d\n", st.value);
}

// 判断一个状态中是否存在某对皇后，它们可以相互攻击
// 注意，若isConflict返回0，则说明该状态为目标状态
int isConflict(state st)
{

    st.value = evaluate(st);

    return st.value;
}
