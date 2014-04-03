Flip Four
=========

Goal
----
Make a game similar to Connect Four, but with a new important feature : the ability to flip the game grid.
    
Gameplay
--------
The game takes place in a 5*5 grid (or plus), with the abilities :

* put a cross (player 1)
* put a circle (player 2)
* flip left or right the grid

Functions
---------

Map :
<code>
enum Case
{
    NONE = 0,
    CROSS = 1,
    CIRCLE = 2
};

Case map[5][5];
</code>

Flip :
<code>
// Pseudo code

void flip(bool left)
{
    Case oldMap[5][5] = clone(map);
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            map[i][j] = left ? oldMap[j][4 - i] : oldMap[4 - j][i];
        }
    }
    
    doGravity();
}
</code>

Gravity :
<code>
void doGravity()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 4; j >= 0; j--)
        {
            fall(i, j);
        }
    }
}

void fall(int x, int y)
{
    if (y < 4)
    {
        if (map[y + 1] == NONE && map[y] != NONE)
        {
            map[y+1] = map[y];
            map[y] = NONE;
            fall(x, y + 1);
        }
    }
}
</code>
