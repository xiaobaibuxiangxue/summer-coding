Cube move01(char cube.matrix[6][3][3])
{
    Cube shun90(char cube.matrix[3][3]);
    shun90(cube.matrix[LEFT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][0] = cube.matrix[UP][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][0] = cube.matrix[FRONT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][0] = cube.matrix[UP][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][0] = temp[i];
    }
}
Cube move10(char cube.matrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][1] = cube.matrix[DOWN][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][1] = cube.matrix[FRONT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][1] = cube.matrix[UP][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][1] = temp[i];
    }
}
Cube move11(char cube.matrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][1] = cube.matrix[UP][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][1] = cube.matrix[FRONT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][1] = cube.matrix[DOWN][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][1] = temp[i];
    }
}
Cube move20(char cube.matrix[6][3][3])
{
    shun90(cube.matrix[RIGHT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][2] = cube.matrix[DOWN][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][2] = cube.matrix[FRONT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][2] = cube.matrix[UP][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][2] = temp[i];
    }
}
Cube move21(char cube.matrix[6][3][3])
{
    ni90(cube.matrix[RIGHT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][i][2] = cube.matrix[UP][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][i][2] = cube.matrix[FRONT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][i][2] = cube.matrix[DOWN][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][i][2] = temp[i];
    }
}
Cube move31(char cube.matrix[6][3][3])
{
    ni90(cube.matrix[DOWN]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][0][i] = cube.matrix[LEFT][2 - i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][0] = cube.matrix[FRONT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][2][i] = cube.matrix[RIGHT][2 - i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][2] = temp[i];
    }
}
Cube move30(char cube.matrix[6][3][3])
{
    shun90(cube.matrix[DOWN]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][0][i] = cube.matrix[RIGHT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][2] = cube.matrix[FRONT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][2][i] = cube.matrix[LEFT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][0] = temp[2 - i];
    }
}
Cube move41(char cube.matrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][1][i] = cube.matrix[LEFT][2 - i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][1] = cube.matrix[FRONT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][1][i] = cube.matrix[RIGHT][2 - i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][1] = temp[i];
    }
}
Cube move40(char cube.matrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][1][i] = cube.matrix[RIGHT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][1] = cube.matrix[FRONT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][1][i] = cube.matrix[LEFT][i][1];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][1] = temp[2 - i];
    }
}
Cube move51(char cube.matrix[6][3][3])
{
    shun90(cube.matrix[UP]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][2][i] = cube.matrix[LEFT][2 - i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][2] = cube.matrix[FRONT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][0][i] = cube.matrix[RIGHT][2 - i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][2] = temp[i];
    }
}
Cube move50(char cube.matrix[6][3][3])
{
    ni90(cube.matrix[UP]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[BACK][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[BACK][2][i] = cube.matrix[RIGHT][i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][i][0] = cube.matrix[FRONT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[FRONT][0][i] = cube.matrix[LEFT][i][2];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][i][2] = temp[2 - i];
    }
}
Cube move61(char cube.matrix[6][3][3])
{
    shun90(cube.matrix[FRONT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][2][i] = cube.matrix[LEFT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][2][i] = cube.matrix[DOWN][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][0][i] = cube.matrix[RIGHT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][2][i] = temp[i];
    }
}
Cube move60(char cube.matrix[6][3][3])
{
    ni90(cube.matrix[FRONT]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][2][i] = cube.matrix[RIGHT][2][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][2][i] = cube.matrix[DOWN][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][0][i] = cube.matrix[LEFT][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][2][i] = temp[i];
    }
}
Cube move71(char cube.matrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][1][i] = cube.matrix[LEFT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][1][i] = cube.matrix[DOWN][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][1][i] = cube.matrix[RIGHT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][1][i] = temp[i];
    }
}
Cube move70(char cube.matrix[6][3][3])
{
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][1][i] = cube.matrix[RIGHT][1][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][1][i] = cube.matrix[DOWN][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][1][i] = cube.matrix[LEFT][1][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][1][i] = temp[i];
    }
}
Cube move80(char cube.matrix[6][3][3])
{
    shun90(cube.matrix[BACK]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][0][i] = cube.matrix[RIGHT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][0][i] = cube.matrix[DOWN][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][2][i] = cube.matrix[LEFT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][0][i] = temp[i];
    }
}
Cube move81(char cube.matrix[6][3][3])
{
    ni90(cube.matrix[BACK]);
    char temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = cube.matrix[UP][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[UP][0][i] = cube.matrix[LEFT][0][i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[LEFT][0][i] = cube.matrix[DOWN][2][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[DOWN][2][i] = cube.matrix[RIGHT][0][2 - i];
    }
    for (int i = 0; i < 3; i++)
    {
        cube.matrix[RIGHT][0][i] = temp[i];
    }
}
Cube action_list(int n, Cube c)
{
    switch (n)
    {
    case 1:
        move01(c.matrix);
        break;
    case 2:
        move00(c.matrix);
        break;
    case 3:
        move11(c.matrix);
    case 4:
        move10(c.matrix);
        break;
    case 5:
        move21(c.matrix);
        break;
    case 6:
        move20(c.matrix);
        break;
    case 7:
        move31(c.matrix);
        break;
    case 8:
        move30(c.matrix);
        break;
    case 9:
        move41(c.matrix);
        break;
    case 10:
        move40(c.matrix);
        break;
    case 11:
        move51(c.matrix);
        break;
    case 12:
        move50(c.matrix);
        break;
    case 13:
        move61(c.matrix);
        break;
    case 14:
        move60(c.matrix);
        break;
    case 15:
        move71(c.matrix);
        break;
    case 16:
        move70(c.matrix);
        break;
    case 17:
        move81(c.matrix);
        break;
    case 18:
        move81(c.matrix);
        break;
    }
    return c;
}
Cube solve()