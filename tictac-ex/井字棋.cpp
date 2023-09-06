#include <iostream>
#include "tic.h"
using namespace std;
int player = 1;
int status[SIZE][SIZE];
void Initial()
{ // ��ʼ��״̬
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
{ // ������ǰ״̬
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
            chess = Minimax_Decision(player); // AI Ϊ��� -1
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
/*����ֵ
 * 1 ���1�����ࣩ��ʤ
 * -1 ���-1��AI����ʤ
 * 2 ��û����
 * 0 ��������
 */
int Check(int chess)
{ // �ж�����Ƿ����
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

// ������д������״̬
void Result(int chess, int player)
{
    status[chess / SIZE][chess % SIZE] = player;
}

// ����AI���������
/*
AI ΪMin ���
����ÿһ����λ
   ��������
   ���� minimax ��ֵ����������Сֵ����Сֵ��Ӧ������
   �������
�����������λ��
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
                // ��������
                int temp = Minimax_Value(i * SIZE + j, player);
                // �����Ӧλ�õ�Minimax_Value
                status[i][j] = 0;
                // �������
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
player����chessλ�����ӣ�����˾����minimax��ֵ
AI ΪMin ���,����Ϊ Max ���

����ֽ�����ֱ�ӷ��ط�ֵ

��ʼ��������Сֵ
���� nextPlayer = - player

����ÿһ����λ
  nextPlayer ��������
  ����nextPlayer����֮���Minimax_Value�����������ֵ/��Сֵ
  �������

����nextPlayer����������Сֵ
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
                status[i][j] = nextPlayer;                          // ��������
                int temp = Minimax_Value(i * SIZE + j, nextPlayer); // ������ַ�ֵ

                if (player == -1 && temp < best_value)
                {
                    best_value = temp; // ������Сֵ
                }
                else if (player == 1 && temp > best_value)
                {
                    best_value = temp; // �������ֵ
                }
                status[i][j] = 0;
            }
        }
    }
    return best_value;
}
