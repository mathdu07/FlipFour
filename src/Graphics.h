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
    
    sf::Texture const& getBigButton() const;
    sf::Texture const& getBigButtonFired() const;
    
    sf::Texture const& getReturn() const;
    sf::Texture const& getReturnFired() const;
    
    sf::Texture const& getRestart() const;
    sf::Texture const& getRestartFired() const;
    
    sf::Texture const& getSettings() const;
    sf::Texture const& getSettingsFired() const;
    
    sf::Texture const& getGrid() const;
    sf::Texture const& getCase() const;
    
    sf::Texture const& getPlayer1() const;
    sf::Texture const& getPlayer2() const;
    
    sf::Texture const& getArrowBottomLeft() const;
    sf::Texture const& getArrowBottomRight() const;
    
    sf::Texture const& getArrowBottomLeftFired() const;
    sf::Texture const& getArrowBottomRightFired() const;
    
    sf::Texture const& getArrowTopLeft() const;
    sf::Texture const& getArrowTopRight() const;
    
    sf::Texture const& getArrowTopLeftFired() const;
    sf::Texture const& getArrowTopRightFired() const;
    
    sf::Texture const& getGameoverBackground() const;
    
    sf::Color getMainColor() const;
    sf::Color getSecondColor() const;
    sf::Color getContentColor() const;

private:
    sf::Texture m_button, m_buttonFired;
    sf::Texture m_bigButton, m_bigButtonFired;
    sf::Texture m_return, m_returnFired;
    sf::Texture m_restart, m_restartFired;
    sf::Texture m_settings, m_settingsFired;
    sf::Texture m_grid, m_case;
    sf::Texture m_player1, m_player2;
    sf::Texture m_arrowBottomLeft, m_arrowBottomRight;
    sf::Texture m_arrowBottomLeftFired, m_arrowBottomRightFired;
    sf::Texture m_arrowTopLeft, m_arrowTopRight;
    sf::Texture m_arrowTopLeftFired, m_arrowTopRightFired;
    sf::Texture m_gameoverBackground;
    sf::Color m_mainColor, m_secondColor, m_contentColor;
};

#endif
