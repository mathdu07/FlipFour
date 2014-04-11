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

#include "Grid.h"
#include "PlayState.h"

Grid::Grid(PlayState &state)
: m_state(state), m_background(), m_gridShape(),
  m_case1(), m_case2(), m_playing(true), m_winner(NONE),
  m_caseWin(), m_directionWin()
{
    for (sf::Uint32 x = 0; x < GRID_SIZE; x++)
    {
        for (sf::Uint32 y = 0; y < GRID_SIZE; y++)
        {
            m_map[x][y] = NONE;
        }
    }
}
    
void Grid::init()
{
    Graphics const &gfx = m_state.getGame().gfx();
    sf::Vector2u size = gfx.getGrid().getSize();
    
    if (!m_target.create(size.x, size.y))
    {
        std::cerr << "Can't allocate Render Texture with : " << size.x << ";" << size.y << std::endl;
    }
    
    m_background.setTexture(gfx.getGrid(), true);
    sf::Rect<float> bounds = m_background.getLocalBounds();
    
    m_gridShape.setTexture(gfx.getCase());
    m_gridShape.setTextureRect(sf::IntRect(0, 0, bounds.width, bounds.height));
    
    m_case1.setTexture(gfx.getPlayer1(), true);
    m_case2.setTexture(gfx.getPlayer2(), true);
    m_case1.setOrigin(0, 0);
    m_case2.setOrigin(0, 0);
}
    
Case Grid::getCaseAt(sf::Uint32 x, sf::Uint32 y) const
{
    return m_map[x][y];
}
    
void Grid::setCaseAt(sf::Uint32 x, sf::Uint32 y, Case c)
{
    std::cout << "Case set at (" << x << ";" << y << ") : " << c << std::endl; 
    m_map[x][y] = c;
    doGravity();
    checkGame(c);
}
    
void Grid::render()
{
    m_target.draw(m_background);
    m_target.draw(m_gridShape);
    
    for (unsigned int x = 0; x < GRID_SIZE; x++)
    {
        for (unsigned int y = 0; y < GRID_SIZE; y++)
        {
            Case c = m_map[x][y];
            sf::FloatRect bounds = m_background.getLocalBounds();
            
            if (c == PLAYER_1)
            {
                m_case1.setPosition(x * (bounds.width / GRID_SIZE), y * (bounds.height / GRID_SIZE));
                m_target.draw(m_case1);
            }
            else if (c == PLAYER_2)
            {
                m_case2.setPosition(x * (bounds.width / GRID_SIZE), y * (bounds.height / GRID_SIZE));
                m_target.draw(m_case2);
            }
        }
    }
    
    m_target.display();
}

const sf::Texture& Grid::getGridTexture() const
{
    return m_target.getTexture();
}

sf::Vector2i Grid::getMapCoordAt(int x, int y) const
{
    sf::FloatRect bounds = m_background.getLocalBounds();
    
    if (bounds.contains(sf::Vector2f(x, y)))
    {
        return sf::Vector2i(x / (int) (bounds.width / GRID_SIZE), y / (int) (bounds.height / GRID_SIZE));
    }
    else
    {
        return sf::Vector2i(-1, -1);
    }
}

bool Grid::isInGrid(int x, int y) const
{
    return getMapCoordAt(x, y) != sf::Vector2i(-1, -1);
}

bool Grid::isPlaying() const
{
    return m_playing;
}
    
Case Grid::getWinner() const
{
    return m_winner;
}
    
void Grid::doGravity()
{
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int y = GRID_SIZE - 1; y >= 0; y--)
        {
            fall(x, y);
        }    
    }
}
    
void Grid::fall(unsigned int x, unsigned int y)
{
    if (y < GRID_SIZE - 1)
    {
        if (m_map[x][y] != NONE && m_map[x][y + 1] == NONE)
        {
            m_map[x][y + 1] = m_map[x][y];
            m_map[x][y] = NONE;
            fall(x, y + 1);
        }
    }
}

void Grid::flip(Case player, bool direction)
{
    Case clone[GRID_SIZE][GRID_SIZE];
    cloneMap(clone);
    
    for (unsigned int x = 0; x < GRID_SIZE; x++)
    {
        for (unsigned int y = 0; y < GRID_SIZE; y++)
        {
            m_map[x][y] = clone[direction ? y : (GRID_SIZE - 1) - y][direction ? (GRID_SIZE - 1) - x : x];
        }
    }
    
    doGravity();
    
    // After flip the grid, the game will first check if the other player win, and only after if the player who's flipped win 
    checkGame(player == PLAYER_1 ? PLAYER_2 : PLAYER_1);
}

void Grid::cloneMap(Case clone[GRID_SIZE][GRID_SIZE])
{
    for (unsigned int x = 0; x < GRID_SIZE; x++)
    {
        for (unsigned int y = 0; y < GRID_SIZE; y++)
        {
            clone[x][y] = m_map[x][y];
        }
    }
}

sf::Vector2i Grid::getFirstCaseWin() const
{
    return m_caseWin;
}
    
sf::Vector2i Grid::getLastCaseWin() const
{
    sf::Vector2i last(m_caseWin);
    
    switch (m_directionWin)
    {
    case HORIZONTAL:
        last += sf::Vector2i(3, 0);
        break;
    case VERTICAL:  
        last += sf::Vector2i(0, 3);
        break;
    case LEFT_DIAGONAL:
        last += sf::Vector2i(3, -3);
        break;
    case RIGHT_DIAGONAL:
        last += sf::Vector2i(3, 3);
        break;
    }    
    
    return last;
}

Direction Grid::getDirectionWin() const
{
    return m_directionWin;
}
    
void Grid::checkGame(Case first)
{
    bool exit(false);
    for (int i = 1; i <= 2; i++)
    {
        Case player = (i == 1 ? first : (first == PLAYER_1 ? PLAYER_2 : PLAYER_1));
        
        for (int x = 0; x < GRID_SIZE; x++)
        {
            for (int y = 0; y < GRID_SIZE; y++)
            {
                if (m_map[x][y] != player)
                {
                    continue;
                }
                else
                {
                    if (x < GRID_SIZE - 3)
                    {
                        if (checkDirection(x, y, HORIZONTAL, player))
                        {
                            exit = true;
                            break;
                        }
                    }
                    
                    if (y < GRID_SIZE - 3)
                    {
                        if (checkDirection(x, y, VERTICAL, player))
                        {
                            exit = true;
                            break;
                        }                    
                    }
                    
                    if (x < GRID_SIZE - 3 && y < GRID_SIZE - 3)
                    {
                        if (checkDirection(x, y, LEFT_DIAGONAL, player))
                        {
                            exit = true;
                            break;
                        }
                    }
                    
                    if (x < GRID_SIZE - 3 && y >= 3)
                    {
                        if (checkDirection(x, y, RIGHT_DIAGONAL, player))
                        {
                            exit = true;
                            break;
                        }               
                    }
                }
            }
            
            if (exit)
                break;
        }
        
        if (exit)
            break;
    }
    
    bool full(true);
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int y = 0; y < GRID_SIZE; y++)
        {
            if (m_map[x][y] == NONE)
            {
                full = false;
            }
        }
    }
    
    if (m_playing && full)
        setWinner(NONE, sf::Vector2i(), HORIZONTAL);
}
    
bool Grid::checkDirection(int x, int y, Direction d, Case player)
{
    for (int j = 0; j <= 3; j++)
    {
        if (m_map[x + (d == VERTICAL ? 0 : j)][y + (d == HORIZONTAL ? 0 : (d == RIGHT_DIAGONAL ? -j : j))] != player)
        {
           return false;
        }
    }

    setWinner(player, sf::Vector2i(x, y), d);
    return true;
}
    
void Grid::setWinner(Case winner, sf::Vector2i coord, Direction dir)
{
    m_playing = false;
    m_winner = winner;
    m_caseWin = coord;
    m_directionWin = dir;
    std::cout << "Win of " << winner << " from case ";
    std::cout << "(" << getFirstCaseWin().x << ";" << getFirstCaseWin().y << ") to ";
    std::cout << "(" << getLastCaseWin().x << ";" << getLastCaseWin().y << ")" << std::endl;
}
