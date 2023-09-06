#include <stdio.h>

#define MAX_N 8
#define MAX_NODES 1000 * MAX_N // ջ�Ĵ�С

#define put_node(st) queue[tl++] = st
#define get_node() queue[hd++]
#define queue_not_empty (hd < tl)

typedef struct state_t
{
    short n, q[MAX_N]; // n��ʾ��ǰ�����ϵĻʺ������q��ʾ��ǰ���ϻʺ���к�
} state_t;

state_t queue[MAX_NODES];
int hd = 0;
int tl = 0;
int queens[MAX_N];
int conflict(int q, int p, short queens[]); // �ж���(@q,@p)���ûʺ��Ƿ��ͻ
int queen(int n);                           // �����������Ϸ��� @n ���ʺ�
void print_queens(state_t *st);             // ��ӡĿǰ�����ϵĻʺ�

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
int queen(int n) // ���n�ʺ�����
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
        st.n++; // ��ǰ�����ϵĻʺ�����+1
        for (i = 0; i < n; i++)
        { // ֮ǰ�Ļʺ��뵱ǰ�ʺ�λ��i�Ƿ��ͻ
            if (conflict(st.n - 1, i, st.q))
                continue;
            st.q[st.n - 1] = i; // ����ͻ������i��
            put_node(st);       // �����ɵĽڵ���ջ
        }
    }
    printf("%d\n", nCount);
    return 0;
}
