#include <iostream>
#include "tic.h"
using namespace std;
int player = 1;
int status[SIZE][SIZE];
void Initial()
{ // 初始化状态
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            status[i][j] = 0;
        }
    }
}
char Pic(int x)
{
    if (x == 0)
    {
        return ' ';
    }
    else if (x == 1)
    {
        return 'o';
    }
    else
    {
        return 'x';
    }
}
void Draw()
{ // 画出当前状态
    cout << line << endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << "|" << Pic(status[i][j]);
        }
        cout << "|" << endl;
        cout << line << endl;
    }
}
int main()
{
    Initial();
    Draw();
    while (1)
    {
        int chess;
        if (player == 1)
        {
            cout << "Please input:" << endl;
            cin >> chess;
            chess--;
            if (status[chess / SIZE][chess % SIZE] == 0)
            {
                Result(chess, player);
            }
            else
            {
                cout << "The location is occupied" << endl;
                Draw();
                continue;
            }
        }
        else
        {
            chess = Minimax_Decision(player); // AI 为玩家 -1
            Result(chess, player);
        }
        Draw();
        int re = Check(chess);
        if (re == 2)
        {
            SwitchPlayer();
            continue;
        }
        if (abs(re) == 1)
        {
            cout << "player " << player << " win!" << endl;
            break;
        }
        if (re == 0)
        {
            cout << "No space." << endl;
            break;
        }
    }
}
/*返回值
 * 1 玩家1（人类）获胜
 * -1 玩家-1（AI）获胜
 * 2 还没结束
 * 0 棋盘已满
 */
int Check(int chess)
{ // 判断棋局是否结束
    int row = chess / SIZE;
    int col = chess % SIZE;
    if (status[row][0] == status[row][1] && status[row][0] == status[row][2])
    {
        return status[row][0];
    }
    if (status[0][col] == status[1][col] && status[0][col] == status[2][col])
    {
        return status[0][col];
    }
    if (row == col && status[(row + 2) % SIZE][(col + 2) % SIZE] == status[row][col] && status[row][col] == status[(row + 1) % SIZE][(col + 1) % SIZE])
    {
        return status[(row + 2) % SIZE][(col + 2) % SIZE];
    }
    if (row + col == SIZE - 1 && status[(row + 2) % SIZE][(col + 1) % SIZE] == status[row][col] && status[row][col] == status[(row + 1) % SIZE][(col + 2) % SIZE])
    {
        return status[(row + 2) % SIZE][(col + 1) % SIZE];
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (status[i][j] == 0)
            {
                return 2;
            }
        }
    }
    return 0;
}
void SwitchPlayer()
{
    player = -player;
}

// 将落子写入棋盘状态
void Result(int chess, int player)
{
    status[chess / SIZE][chess % SIZE] = player;
}

// 计算AI的最佳落子
/*
AI 为Min 玩家
对于每一个空位
   尝试落子
   计算 minimax 分值，并更新最小值和最小值对应的落子
   清除落子
返回最佳落子位置
*/
int Minimax_Decision(int player)
{
    int min = INF;
    int choice = -1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (status[i][j] == 0)
            {
                status[i][j] = player;
                // 尝试落子
                int temp = Minimax_Value(i * SIZE + j, player);
                // 计算对应位置的Minimax_Value
                status[i][j] = 0;
                // 清除落子
                if (min > temp)
                {
                    min = temp;
                    choice = i * SIZE + j;
                }
            }
        }
    }
    return choice;
}

/*
 * int Minimax_Value(int chess, int player)
player已在chess位置落子，计算此局面的minimax分值
AI 为Min 玩家,人类为 Max 玩家

若棋局结束，直接返回分值

初始化最大和最小值
设置 nextPlayer = - player

对于每一个空位
  nextPlayer 尝试落子
  计算nextPlayer落子之后的Minimax_Value，并更新最大值/最小值
  清除落子

根据nextPlayer返回最大或最小值
*/

int Minimax_Value(int chess, int player)
{
    int game_result = Check(chess);
    if (game_result != 2)
    { // gameover
        return game_result;
    }

    int best_value;

    if (player == -1)
    {
        best_value = INF;
    }
    else if (player == 1)
    {
        best_value = -INF;
    }
    int nextPlayer = -player;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (status[i][j] == 0)
            {
                status[i][j] = nextPlayer;                          // 尝试落子
                int temp = Minimax_Value(i * SIZE + j, nextPlayer); // 计算对手分值

                if (player == -1 && temp < best_value)
                {
                    best_value = temp; // 更新最小值
                }
                else if (player == 1 && temp > best_value)
                {
                    best_value = temp; // 更新最大值
                }
                status[i][j] = 0;
            }
        }
    }
    return best_value;
}
