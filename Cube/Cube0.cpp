#include <bits/stdc++.h>

using namespace std;

const int N = 5;

time_t beg, endd;

struct Cube
{
    Cube()
    {
        for (int i = 0; i < 10; i++)
            path[i] = -1;
    }
    char Left[3][3], Front[3][3], Right[3][3], Up[3][3], Down[3][3], Back[3][3];
    int cnt = 0;
    int path[10];
} a;

queue<Cube> q;

void open_txt();
bool check_one(char str[3][3]);
bool check_all(Cube c);
void spin_false(char str[3][3]); // 逆时针旋转
void spin_true(char str[3][3]);  // 顺时针旋转
Cube move_0_true(Cube c);
Cube move_0_false(Cube c);
Cube move_1_true(Cube c);
Cube move_1_false(Cube c);
Cube move_2_true(Cube c);
Cube move_2_false(Cube c);
Cube move_3_true(Cube c);
Cube move_3_false(Cube c);
Cube move_4_true(Cube c);
Cube move_4_false(Cube c);
Cube move_5_true(Cube c);
Cube move_5_false(Cube c);
Cube move_6_true(Cube c);
Cube move_6_false(Cube c);
Cube move_7_true(Cube c);
Cube move_7_false(Cube c);
Cube move_8_true(Cube c);
Cube move_8_false(Cube c);
Cube create_action(int num, Cube c);
void print_soluton(Cube c);
string ex();

void print_solution(Cube c)
{
    for (int i = 1; i <= c.cnt; i++)
        if (c.path[i] & 1)
            cout << to_string(c.path[i] / 2) + "- ";
        else
            cout << to_string(c.path[i] / 2) + "+ ";
}

void bfs()
{
    while (!q.empty())
    {
        Cube t = q.front();
        q.pop();
        if (check_all(t))
        {
            cout << "Successfully solve the magic cube!" << endl;
            cout << "Step is :" << endl;
            print_solution(t);
            endd = clock();
            cout << endl;
            cout << "Run time:" << (double)(endd - beg) / CLOCKS_PER_SEC << 's' << endl;
            // print
            return;
        }
        if (t.cnt >= N)
            continue;
        else
        {
            Cube *action = new Cube();
            t.cnt++;
            for (int i = 0; i < 18; i++)
            {
                *action = create_action(i, t);
                (*action).path[t.cnt] = i;
                if (t.path[t.cnt - 1] == t.path[t.cnt - 2] && i == t.path[t.cnt - 1])
                    continue;
                if ((i & 1) && t.path[t.cnt - 1] != i - 1)
                    q.push(*action);
                if (!(i & 1) && t.path[t.cnt - 1] != i + 1)
                    q.push(*action);
            }
            delete action;
        }
    }
}

void spin_true(char str[3][3])
{
    char **arr = new char *[3];
    for (int i = 0; i < 3; i++)
        arr[i] = new char[3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            arr[i][j] = str[i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            str[i][j] = arr[2 - j][i];
    delete[] arr;
}

void spin_false(char str[3][3])
{
    char **arr = new char *[3];
    for (int i = 0; i < 3; i++)
        arr[i] = new char[3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            arr[i][j] = str[i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            str[i][j] = arr[j][2 - i];
    delete[] arr;
}

bool check_one(char str[3][3])
{
    char color = str[0][0];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (color != str[i][j])
                return false;
        }
    return true;
}

bool check_all(Cube c)
{
    if (check_one(c.Left) && check_one(c.Front) && check_one(c.Up) && check_one(c.Down) && check_one(c.Right) && check_one(c.Back))
        return true;
    return false;
}

void open_txt()
{
    ifstream fin("5(5).txt");
    while (!fin.eof())
    {
        string s;
        fin >> s;
        if (s == "back:")
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    fin >> a.Back[i][j];
        if (s == "down:")
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    fin >> a.Down[i][j];
        if (s == "front:")
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    fin >> a.Front[i][j];
        if (s == "left:")
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    fin >> a.Left[i][j];
        if (s == "right:")
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    fin >> a.Right[i][j];
        if (s == "up:")
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    fin >> a.Up[i][j];
    }
    fin.close();
}

Cube move_0_true(Cube c)
{
    spin_true(c.Left);
    char arr_back[3][3], arr_down[3][3], arr_front[3][3], arr_up[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_up[i][j] = c.Up[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_down[i][j] = c.Down[i][j];
        }

    for (int i = 0; i < 3; i++)
    {
        c.Back[i][0] = arr_down[i][0];
        c.Up[i][0] = arr_back[i][0];
        c.Front[i][0] = arr_up[i][0];
        c.Down[i][0] = arr_front[i][0];
    }
    return c;
}

Cube move_0_false(Cube c)
{
    spin_false(c.Left);
    char arr_back[3][3], arr_down[3][3], arr_front[3][3], arr_up[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_up[i][j] = c.Up[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_down[i][j] = c.Down[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[i][0] = arr_up[i][0];
        c.Up[i][0] = arr_front[i][0];
        c.Front[i][0] = arr_down[i][0];
        c.Down[i][0] = arr_back[i][0];
    }
    return c;
}

Cube move_1_true(Cube c)
{
    char arr_back[3][3], arr_up[3][3], arr_front[3][3], arr_down[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_up[i][j] = c.Up[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_down[i][j] = c.Down[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[i][1] = arr_down[i][1];
        c.Up[i][1] = arr_back[i][1];
        c.Front[i][1] = arr_up[i][1];
        c.Down[i][1] = arr_front[i][1];
    }
    return c;
}

Cube move_1_false(Cube c)
{
    char arr_back[3][3], arr_down[3][3], arr_front[3][3], arr_up[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_up[i][j] = c.Up[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_down[i][j] = c.Down[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[i][1] = arr_up[i][1];
        c.Up[i][1] = arr_front[i][1];
        c.Front[i][1] = arr_down[i][1];
        c.Down[i][1] = arr_back[i][1];
    }
    return c;
}

Cube move_2_true(Cube c)
{
    spin_false(c.Right);
    char arr_back[3][3], arr_down[3][3], arr_front[3][3], arr_up[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_up[i][j] = c.Up[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_down[i][j] = c.Down[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[i][2] = arr_down[i][2];
        c.Up[i][2] = arr_back[i][2];
        c.Front[i][2] = arr_up[i][2];
        c.Down[i][2] = arr_front[i][2];
    }
    return c;
}

Cube move_2_false(Cube c)
{
    spin_true(c.Right);
    char arr_back[3][3], arr_down[3][3], arr_front[3][3], arr_up[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_up[i][j] = c.Up[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_down[i][j] = c.Down[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[i][2] = arr_up[i][2];
        c.Up[i][2] = arr_front[i][2];
        c.Front[i][2] = arr_down[i][2];
        c.Down[i][2] = arr_back[i][2];
    }
    return c;
}

Cube move_3_true(Cube c)
{
    spin_false(c.Down);
    char arr_back[3][3], arr_left[3][3], arr_front[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[0][i] = arr_left[2 - i][0];
        c.Left[i][0] = arr_front[2][i];
        c.Front[2][i] = arr_right[2 - i][2];
        c.Right[i][2] = arr_back[0][i];
    }
    return c;
}

Cube move_3_false(Cube c)
{
    spin_true(c.Down);
    char arr_back[3][3], arr_left[3][3], arr_front[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[0][i] = arr_right[i][2];
        c.Left[i][0] = arr_back[0][2 - i];
        c.Front[2][i] = arr_left[i][0];
        c.Right[i][2] = arr_front[2][2 - i];
    }
    return c;
}

Cube move_4_true(Cube c)
{
    char arr_back[3][3], arr_left[3][3], arr_front[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[1][i] = arr_left[2 - i][1];
        c.Left[i][1] = arr_front[1][i];
        c.Front[1][i] = arr_right[2 - i][1];
        c.Right[i][1] = arr_back[1][i];
    }
    return c;
}

Cube move_4_false(Cube c)
{
    char arr_back[3][3], arr_left[3][3], arr_front[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[1][i] = arr_right[i][1];
        c.Left[i][1] = arr_back[1][2 - i];
        c.Front[1][i] = arr_left[i][1];
        c.Right[i][1] = arr_front[1][2 - i];
    }
    return c;
}

Cube move_5_true(Cube c)
{
    spin_true(c.Up);
    char arr_back[3][3], arr_left[3][3], arr_front[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[2][i] = arr_left[2 - i][2];
        c.Left[i][2] = arr_front[0][i];
        c.Front[0][i] = arr_right[2 - i][0];
        c.Right[i][0] = arr_back[2][i];
    }
    return c;
}

Cube move_5_false(Cube c)
{
    spin_false(c.Up);
    char arr_back[3][3], arr_left[3][3], arr_front[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_back[i][j] = c.Back[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_front[i][j] = c.Front[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Back[2][i] = arr_right[i][0];
        c.Left[i][2] = arr_back[2][2 - i];
        c.Front[0][i] = arr_left[i][2];
        c.Right[i][0] = arr_front[0][2 - i];
    }
    return c;
}

Cube move_6_true(Cube c)
{
    spin_true(c.Front);
    char arr_up[3][3], arr_left[3][3], arr_down[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_up[i][j] = c.Up[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_down[i][j] = c.Down[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Up[2][i] = arr_left[2][i];
        c.Right[2][i] = arr_up[2][i];
        c.Down[0][i] = arr_right[2][2 - i];
        c.Left[2][i] = arr_down[0][2 - i];
    }
    return c;
}

Cube move_6_false(Cube c)
{
    spin_false(c.Front);
    char arr_up[3][3], arr_left[3][3], arr_down[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_up[i][j] = c.Up[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_down[i][j] = c.Down[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Up[2][i] = arr_right[2][i];
        c.Right[2][i] = arr_down[0][2 - i];
        c.Down[0][i] = arr_left[2][2 - i];
        c.Left[2][i] = arr_up[2][i];
    }
    return c;
}

Cube move_7_true(Cube c)
{
    char arr_up[3][3], arr_left[3][3], arr_down[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_up[i][j] = c.Up[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_down[i][j] = c.Down[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Up[1][i] = arr_left[1][i];
        c.Right[1][i] = arr_up[1][i];
        c.Down[1][i] = arr_right[1][2 - i];
        c.Left[1][i] = arr_down[1][2 - i];
    }
    return c;
}

Cube move_7_false(Cube c)
{
    char arr_up[3][3], arr_left[3][3], arr_down[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_up[i][j] = c.Up[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_down[i][j] = c.Down[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Up[1][i] = arr_right[1][i];
        c.Right[1][i] = arr_down[1][2 - i];
        c.Down[1][i] = arr_left[1][2 - i];
        c.Left[1][i] = arr_up[1][i];
    }
    return c;
}

Cube move_8_true(Cube c)
{
    spin_false(c.Back);
    char arr_up[3][3], arr_left[3][3], arr_down[3][3], arr_right[3][3];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_up[i][j] = c.Up[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_down[i][j] = c.Down[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Up[0][i] = arr_left[0][i];
        c.Right[0][i] = arr_up[0][i];
        c.Down[2][i] = arr_right[0][2 - i];
        c.Left[0][i] = arr_down[2][2 - i];
    }
    return c;
}

Cube move_8_false(Cube c)
{
    spin_true(c.Back);
    char arr_up[3][3], arr_left[3][3], arr_down[3][3], arr_right[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            arr_up[i][j] = c.Up[i][j];
            arr_left[i][j] = c.Left[i][j];
            arr_down[i][j] = c.Down[i][j];
            arr_right[i][j] = c.Right[i][j];
        }
    for (int i = 0; i < 3; i++)
    {
        c.Up[0][i] = arr_right[0][i];
        c.Right[0][i] = arr_down[2][2 - i];
        c.Down[2][i] = arr_left[0][2 - i];
        c.Left[0][i] = arr_up[0][i];
    }
    return c;
}

Cube create_action(int num, Cube c)
{
    if (num == 0)
        c = move_0_true(c);
    if (num == 1)
        c = move_0_false(c);
    if (num == 2)
        c = move_1_true(c);
    if (num == 3)
        c = move_1_false(c);
    if (num == 4)
        c = move_2_true(c);
    if (num == 5)
        c = move_2_false(c);
    if (num == 6)
        c = move_3_true(c);
    if (num == 7)
        c = move_3_false(c);
    if (num == 8)
        c = move_4_true(c);
    if (num == 9)
        c = move_4_false(c);
    if (num == 10)
        c = move_5_true(c);
    if (num == 11)
        c = move_5_false(c);
    if (num == 12)
        c = move_6_true(c);
    if (num == 13)
        c = move_6_false(c);
    if (num == 14)
        c = move_7_true(c);
    if (num == 15)
        c = move_7_false(c);
    if (num == 16)
        c = move_8_true(c);
    if (num == 17)
        c = move_8_false(c);
    return c;
}

int main()
{
    open_txt();
    // ios::sync_with_stdio(false);
    // string x1 = ex();
    // cout << x1.c_str();
    beg = clock();
    // q.push(a);
    a = move_4_false(a);
    a = move_5_true(a);
    a = move_3_false(a);
    a = move_4_false(a);
    string x2 = ex();
    cout << x2.c_str();
    // bfs();
    // string x = ex();
    //  cout << x.c_str();
    return 0;
}
string ex()
{
    string s;
    for (int i = 0; i < 3; i++)
    {
        for (int i1 = 0; i1 < 3; i1++)
        {
            s += a.Back[i][i1];
        }
    }
    // s += '\n';
    for (int i = 0; i < 3; i++)
    {
        for (int i1 = 0; i1 < 3; i1++)
        {
            s += a.Down[i][i1];
        }
    }
    // s += '\n';
    for (int i = 0; i < 3; i++)
    {
        for (int i1 = 0; i1 < 3; i1++)
        {
            s += a.Front[i][i1];
        }
    }
    // s += '\n';
    for (int i = 0; i < 3; i++)
    {
        for (int i1 = 0; i1 < 3; i1++)
        {
            s += a.Left[i][i1];
        }
    }
    // s += '\n';
    for (int i = 0; i < 3; i++)
    {
        for (int i1 = 0; i1 < 3; i1++)
        {
            s += a.Right[i][i1];
        }
    }
    // s += '\n';
    for (int i = 0; i < 3; i++)
    {
        for (int i1 = 0; i1 < 3; i1++)
        {
            s += a.Up[i][i1];
        }
    }
    // s += '\n';
    return s;
}