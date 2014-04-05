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

#include "Graphics.h"

Graphics::Graphics()
: m_button(), m_buttonFired(),
  m_grid(), m_case(),
  m_player1(), m_player2(),
  m_arrowLeft(), m_arrowRight()
{

}

void Graphics::load()
{
    m_button.loadFromFile("res/gfx/button.png");
    m_buttonFired.loadFromFile("res/gfx/button_fired.png");
    
    m_grid.loadFromFile("res/gfx/grid.png");
    m_case.loadFromFile("res/gfx/case.png");
    m_case.setRepeated(true);
    
    m_player1.loadFromFile("res/gfx/player_1.png");
    m_player2.loadFromFile("res/gfx/player_2.png");
    
    m_arrowLeft.loadFromFile("res/gfx/arrow_left.png");
    m_arrowRight.loadFromFile("res/gfx/arrow_right.png");
}

sf::Texture const& Graphics::getButton() const
{
    return m_button;
}

sf::Texture const& Graphics::getButtonFired() const
{
    return m_buttonFired;
}

sf::Texture const& Graphics::getGrid() const
{
    return m_grid;
}

sf::Texture const& Graphics::getCase() const
{
    return m_case;
}
    
sf::Texture const& Graphics::getPlayer1() const
{
    return m_player1;
}

sf::Texture const& Graphics::getPlayer2() const
{
    return m_player2;
}

sf::Texture const& Graphics::getArrowLeft() const
{
    return m_arrowLeft;
}

sf::Texture const& Graphics::getArrowRight() const
{
    return m_arrowRight;
}

sf::Color Graphics::getMainColor() const
{
    return sf::Color(52, 39, 20, 255);
}
