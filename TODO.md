4 Flip
=======

Objectif
--------
    Il s'agit de faire un jeu similaire au puissance 4, mais avec une nouvelle fonctionnalité : pouvoir tourner la grille de jeu.
    
Gameplay
---------
Le jeu se déroule sur grille de 5*5 cases (voir +), avec la possibilité de :

* poser une croix (joueur 1)
* poser un rond (joueur 2)
* faire tourner la grille vers la droite ou vers la gauche

Fonctions
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

void flip(bool left) // Or right, to check ^^
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