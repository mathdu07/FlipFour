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

#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"

class MainMenuState : public State
{
public:
    MainMenuState(Game &game);

    virtual void init();

    virtual void handleEvent(sf::Event const &event);

    virtual void deInit();

    virtual void render(sf::RenderTarget &target);

    virtual void update();

private:
    sf::RectangleShape m_background;
    sf::ui::Label m_title;
    sf::ui::Button m_versusButton, m_aboutButton, m_exitButton;
    sf::ui::Label m_versionType;
};

 #endif
