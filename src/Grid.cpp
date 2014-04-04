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
  m_case1(), m_case2()
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
}
    
Case Grid::getCaseAt(sf::Uint32 x, sf::Uint32 y) const
{
    return m_map[x][y];
}
    
void Grid::setCaseAt(sf::Uint32 x, sf::Uint32 y, Case c)
{
    m_map[x][y] = c;
}
    
void Grid::render()
{
    m_target.draw(m_background);
    m_target.draw(m_gridShape);
}

const sf::Texture& Grid::getGridTexture() const
{
    return m_target.getTexture();
}
