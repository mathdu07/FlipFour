/*
 *  This file is part of Flip Four.
 *
 *  Flip Four is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Flip Four is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Flip Four. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GRID_H
#define GRID_H

#define GRID_SIZE 5

enum Case
{
    NONE,
    PLAYER_1,
    PLAYER_2
};

enum Direction
{
    HORIZONTAL,
    VERTICAL,
    LEFT_DIAGONAL,
    RIGHT_DIAGONAL
};

//Forward Class
class PlayState;

#include "Main.h"

class Grid
{
public:
    Grid(PlayState &state);
    
    void init();
    
    Case getCaseAt(sf::Uint32 x, sf::Uint32 y) const;
    
    void setCaseAt(sf::Uint32 x, sf::Uint32 y, Case c);
    
    void render();
    
    const sf::Texture& getGridTexture() const;
    
    sf::Vector2i getMapCoordAt(int x, int y) const;
    
    bool isInGrid(int x, int y) const;
    
    bool isPlaying() const;
    
    Case getWinner() const;
    
    sf::Vector2i getFirstCaseWin() const;
    
    sf::Vector2i getLastCaseWin() const;
    
    Direction getDirectionWin() const;
    
    void flip(Case player, bool direction); // True -> Flip left, False -> Flip right
    
private:
    void doGravity();
    
    void fall(unsigned int x, unsigned int y);
    
    void checkGame(Case first);
    
    bool checkDirection(int x, int y, Direction d, Case player);
    
    void setWinner(Case winner, sf::Vector2i coord, Direction dir);
    
    void cloneMap(Case clone[GRID_SIZE][GRID_SIZE]);

private:
    PlayState &m_state;
    Case m_map[GRID_SIZE][GRID_SIZE];
    sf::RenderTexture m_target;
    sf::Sprite m_background;
    sf::Sprite m_gridShape;
    sf::Sprite m_case1, m_case2;
    bool m_playing;
    Case m_winner; // NONE if no winner, else the player who's won
    sf::Vector2i m_caseWin;
    Direction m_directionWin;
};

#endif
