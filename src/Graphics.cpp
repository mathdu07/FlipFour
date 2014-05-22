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
  m_bigButton(), m_bigButtonFired(),
  m_return(), m_returnFired(),
  m_grid(), m_case(),
  m_player1(), m_player2(),
  m_arrowBottomLeft(), m_arrowBottomRight(),
  m_arrowBottomLeftFired(), m_arrowBottomRightFired(),
  m_arrowTopLeft(), m_arrowTopRight(),
  m_arrowTopLeftFired(), m_arrowTopRightFired(),
  m_gameoverBackground(),
  m_mainColor(), m_secondColor()
{

}

void Graphics::load()
{
    m_button.loadFromFile("res/gfx/button.png");
    m_buttonFired.loadFromFile("res/gfx/button_fired.png");
    
    m_bigButton.loadFromFile("res/gfx/big_button.png");
    m_bigButtonFired.loadFromFile("res/gfx/big_button_fired.png");
    
    m_return.loadFromFile("res/gfx/return.png");
    m_returnFired.loadFromFile("res/gfx/return_fired.png");
    
    m_grid.loadFromFile("res/gfx/grid.png");
    m_case.loadFromFile("res/gfx/case.png");
    m_case.setRepeated(true);
    
    m_player1.loadFromFile("res/gfx/player_1.png");
    m_player2.loadFromFile("res/gfx/player_2.png");
    
    m_arrowBottomLeft.loadFromFile("res/gfx/arrow_bl.png");
    m_arrowBottomLeftFired.loadFromFile("res/gfx/arrow_bl_fired.png");
    m_arrowBottomRight.loadFromFile("res/gfx/arrow_br.png");
    m_arrowBottomRightFired.loadFromFile("res/gfx/arrow_br_fired.png");
    m_arrowTopLeft.loadFromFile("res/gfx/arrow_tl.png");
    m_arrowTopLeftFired.loadFromFile("res/gfx/arrow_tl_fired.png");
    m_arrowTopRight.loadFromFile("res/gfx/arrow_tr.png");
    m_arrowTopRightFired.loadFromFile("res/gfx/arrow_tr_fired.png");
    
    m_gameoverBackground.loadFromFile("res/gfx/gameover_background.png");
    
    m_mainColor = sf::Color(52, 39, 20);
    m_secondColor = sf::Color(120, 109, 95);
}

sf::Texture const& Graphics::getButton() const
{
    return m_button;
}

sf::Texture const& Graphics::getButtonFired() const
{
    return m_buttonFired;
}

sf::Texture const& Graphics::getBigButton() const
{
    return m_bigButton;
}

sf::Texture const& Graphics::getBigButtonFired() const
{
    return m_bigButtonFired;
}

sf::Texture const& Graphics::getReturn() const
{
    return m_return;
}

sf::Texture const& Graphics::getReturnFired() const
{
    return m_returnFired;
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

sf::Texture const& Graphics::getArrowBottomLeft() const
{
	return m_arrowBottomLeft;
}

sf::Texture const& Graphics::getArrowBottomRight() const
{
	return m_arrowBottomRight;
}
    
sf::Texture const& Graphics::getArrowBottomLeftFired() const
{
	return m_arrowBottomLeftFired;
}

sf::Texture const& Graphics::getArrowBottomRightFired() const
{
	return m_arrowBottomRightFired;
}

sf::Texture const& Graphics::getArrowTopLeft() const
{
	return m_arrowTopLeft;
}

sf::Texture const& Graphics::getArrowTopRight() const
{
	return m_arrowTopRight;
}
    
sf::Texture const& Graphics::getArrowTopLeftFired() const
{
	return m_arrowTopLeftFired;
}

sf::Texture const& Graphics::getArrowTopRightFired() const
{
	return m_arrowTopRightFired;
}

sf::Texture const& Graphics::getGameoverBackground() const
{
    return m_gameoverBackground;
}

sf::Color Graphics::getMainColor() const
{
    return m_mainColor;
}

sf::Color Graphics::getSecondColor() const
{
    return m_secondColor;
}
