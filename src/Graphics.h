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

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Main.h"

class Graphics
{
public:
    Graphics();

    void load();

    sf::Texture const& getButton() const;
    sf::Texture const& getButtonFired() const;
    
    sf::Texture const& getGrid() const;
    sf::Texture const& getCase() const;
    
    sf::Texture const& getPlayer1() const;
    sf::Texture const& getPlayer2() const;
    
    sf::Texture const& getArrowLeft() const;
    sf::Texture const& getArrowRight() const;
    
    sf::Texture const& getArrowLeftFired() const;
    sf::Texture const& getArrowRightFired() const;
    
    sf::Texture const& getGameoverBackground() const;
    
    sf::Color getMainColor() const;
    sf::Color getSecondColor() const;

private:
    sf::Texture m_button, m_buttonFired;
    sf::Texture m_grid, m_case;
    sf::Texture m_player1, m_player2;
    sf::Texture m_arrowLeft, m_arrowRight;
    sf::Texture m_arrowLeftFired, m_arrowRightFired;
    sf::Texture m_gameoverBackground;
    sf::Color m_mainColor, m_secondColor;
};

#endif
