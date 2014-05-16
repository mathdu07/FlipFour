Flip Four
=========

Rules
-----
The goal of Flip Four is to align, horizontaly, verticaly, or diagonally, four similar symbols, in a grid of 5 * 5 squares.
The first player who is matching these conditions win the game.
If nobody has aligned 4 symbols when the grid is full, the game is declared tie.
The players can't have the same symbols.
The symbols are subjects to gravity.

The players can also flip the grid, what will rotate the grid to the left or to the right, and after a rotation, the advantage is giving to the other player : if both player have aligned 4 symbols with the rotation, the winner will be the one who hasn't played.

In this version, the player 1 is symbolised by a circle, and the player 2 by a cross. 

Dependencies
-------------

General :

* [SFML 2.1+](http://www.sfml-dev.org/download.php)
* [SFML-UI 0.4.1+](https://github.com/PatateDev/sfml-ui/releases)

GNU/Linux packages (on Debian) :

* SFML's one :
    * freeglut3-dev
    * libx11-dev
    * libxrandr-dev
    * libfreetype6-dev
    * libglew-dev
    * libjpeg-dev
    * libsndfile1-dev
    * libopenal-dev