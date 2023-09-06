#include <bits/stdc++.h>
using namespace std;

struct pos
{
    int x;
    int y;
};
struct player
{
    string id;
    int length;
    int score;
    int move;
    int head;
    int pstill;
    int pcool;
    pos body[30];
};
struct state
{
    int time;
    int tool;
    pos toolpos[100];
    int tooltype[100];
    int playernum;
    player people[10];
};
state getstate(state now)
{
    cin >> now.time;
    cin >> now.tool;
    for (int i = 0; i < now.tool; i++)
    {
        cin >> now.toolpos[i].x;
        cin >> now.toolpos[i].y;
        cin >> now.tooltype[i];
    }
    cin >> now.playernum;
    for (int i = 0; i < now.tool; i++)
    {
        cin >> now.people->id;
        cin >> now.people->length;
        cin >> now.people->score;
        cin >> now.people->head;
        cin >> now.people->move;
        cin >> now.people->pstill;
        cin >> now.people->pcool;
    }
    for (int i = 0; i < now.people->length; i++)
    {
        cin >> now.people->body->x;
        cin >> now.people->body->y;
    }
    return now;
}
int main()
{
    state now;
    now = getstate(now);
    return 0;
}