#include <bits/stdc++.h>
using namespace std;
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
int main()
{
    // ios::sync_with_stdio(false);
    a.cnt = 10;
    q.push(a);
    Cube x = q.front();
    cout << x.cnt;
    return 0;
}