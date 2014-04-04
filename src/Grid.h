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

private:
    PlayState &m_state;
    Case m_map[GRID_SIZE][GRID_SIZE];
    sf::RenderTexture m_target;
    sf::Sprite m_background;
    sf::Sprite m_gridShape;
    sf::Sprite m_case1, m_case2;
};

#endif
