#include <stdio.h>

#define MAX_N 8
#define MAX_NODES 1000 * MAX_N // 栈的大小

#define put_node(st) queue[tl++] = st
#define get_node() queue[hd++]
#define queue_not_empty (hd < tl)

typedef struct state_t
{
    short n, q[MAX_N]; // n表示当前棋盘上的皇后个数；q表示当前列上皇后的行号
} state_t;

state_t queue[MAX_NODES];
int hd = 0;
int tl = 0;
int queens[MAX_N];
int conflict(int q, int p, short queens[]); // 判断在(@q,@p)放置皇后是否冲突
int queen(int n);                           // 尝试在棋盘上放置 @n 个皇后
void print_queens(state_t *st);             // 打印目前棋盘上的皇后

int main()
{
    state_t init_st;

    init_st.n = 0;
    put_node(init_st);
    queen(MAX_N);
    return 0;
}

void print_queens(state_t *st)
{
    int l = sizeof(st->q) / sizeof(st->q[0]);
    for (int i = 0; i < l; i++)
        printf("%d ", st->q[i]);
    printf("\n");
}
int conflict(int q, int p, short queens[])
{
    for (int i = 1; i <= q; i++)
    {
        if (queens[q - i] == p)
            return 1;
        if (queens[q - i] == p + i)
            return 1;
        if (queens[q - i] == p - i)
            return 1;
    }
    return 0;
}
int queen(int n) // 解决n皇后问题
{
    int i, nCount = 0;
    state_t st;
    while (queue_not_empty)
    {

        st = get_node();
        // printf("%d", st.n);
        if (st.n >= n)
        {
            print_queens(&st);
            nCount++;
            continue;
        }
        st.n++; // 当前棋盘上的皇后数量+1
        for (i = 0; i < n; i++)
        { // 之前的皇后与当前皇后位置i是否冲突
            if (conflict(st.n - 1, i, st.q))
                continue;
            st.q[st.n - 1] = i; // 不冲突，放在i行
            put_node(st);       // 新生成的节点入栈
        }
    }
    printf("%d\n", nCount);
    return 0;
}
