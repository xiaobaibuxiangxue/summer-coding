
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_QUEENS 128 // 皇后的个数
#define MAX_NODES 10000
#define DEBUG_MODE 1 // 为0，不输出调试信息，否则输出调试信息
#define MAX_TRY 100  // 最大random restart 次数
#define COOLING_FACTOR 0.9999

// 状态
typedef struct state
{
    int value;           // 该状态的价值，value越大，价值越高
    int pos[NUM_QUEENS]; // 每一行皇后的位置
} state;
void generateInit(state *);
// 随机产生一个初始状态, 将状态存入输入参数指针所指向的空间
state select_neighbor_at_random(const state);
// 找到输入状态的最好邻居
int evaluate(state);
// 评估一个状态的价值
void printSolution(state);
// 打印输出一个状态的信息
int isConflict(state);
// 判断一个状态是否是要找的结果
int sa_search();
// 产生一个初始状态，并找到局部最优解;若找到了一个目标结果
// （皇后相互不冲突）返回1，否则返回0
int isEqual(state s1, state s2);
// 判断两个状态是否相同

/*
基于一个初始状态，进行尝试
*/
int sa_search()
{
    state current, neighbor;
    generateInit(&current); // 新生成一个初始状态

    if (DEBUG_MODE)
        printSolution(current); // 输出初始状态

    if (!isConflict(current))
    {
        // 初始状态即是目标
        printf("You are very lucky!\n");
        printSolution(current);
        return 1;
    }

    long long t = 1;
    double T = 1e6;
    while (T > 1e-8)
    {
        neighbor = select_neighbor_at_random(current);
        // 根据neighbor和current的值计算DeltaE值
        /*
                if (DEBUG_MODE && t % 10000000 == 0)
                {
                    printf("neighbor-val %d, current-val %d\n", neighbor.value, current.value);
                }*/
        double delta = neighbor.value - current.value;
        // 如果DeltaE的值大于0，则设置neighbor为current，否则以一定概率将neighbor设置为current

        double p = rand() % 100 / 100.0;
        double lim = exp(delta / T);
        if (p < lim)
        {
            current = neighbor;
        }
        /*
                if (DEBUG_MODE && t % 100000 == 0)
                {
                    printf("%d %g %d\n", t, T, current.value);
                }*/
        if (!isConflict(current))
        {
            printSolution(current);
            return 1;
        }
        // double cooling_factor = 0.9999;
        T = T * COOLING_FACTOR; // log(t+1);
        t++;
        if (t > 1e8)
            break;
    }

    printf("*********************\n");
    printf("find a local maximum:\n");
    printSolution(current);
    return 0;
}

// 产生一个随机状态
void generateInit(state *p_st)
{
    for (int i = 0; i < NUM_QUEENS; i++)
    {
        int p = rand() % NUM_QUEENS;
        p_st->pos[i] = p;
    }

    p_st->value = evaluate(*p_st);
}

/*
从当前状态的邻居中随机选取一个
邻居的定义可以是固定n个列，更换一个列的皇后的位置，这样共有n(n-1)个邻居
*/
state select_neighbor_at_random(const state current)
{
    // to-do
    state neibour;
    neibour = current;
    int n = rand() % NUM_QUEENS;
    int m = rand() % NUM_QUEENS;
    if (neibour.pos[n] != m)
        neibour.pos[n] = m;
    neibour.value = evaluate(neibour);
    return neibour;
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
    // printf("%d\n", st.value);
    return (st.value);
}

// 打印一个状态的信息
void printSolution(state st)
{
    for (int i = 0; i < NUM_QUEENS; i++)
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

int main()
{
    int count = 0;                     // 已经尝试的次数
    srand((unsigned int)(time(NULL))); // 设置随机序列器的种子(注意程序其他地方不要再调用srand)

    printf("simulated annealing search (cooling factor: %g) for %d-queens\n", COOLING_FACTOR, NUM_QUEENS);
    while (count++ < MAX_TRY)
    {
        if (DEBUG_MODE)
        {
            printf("*********************************\n");
            printf("begin the %d try.\n", count);
        }

        clock_t begin = clock();
        int okay = sa_search();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        printf("trial [%d], %g seconds\n", count, elapsed_secs);

        if (okay)
        {
            printf("find a valid solution after %d trials\n", count);
            break; // 找到了目标
        }
    }

    if (DEBUG_MODE)
    {
        printf("*********************\n");
    }

    return 0;
}
