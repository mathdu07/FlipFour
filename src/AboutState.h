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

#ifndef ABOUT_STATE_H
#define ABOUT_STATE_H

#include "State.h"

class AboutState : public State
{
public:
    AboutState(Game &game);

    virtual void init();

    virtual void handleEvent(sf::Event const &event);

    virtual void deInit();

    virtual void render(sf::RenderTarget &target);

    virtual void update();

private:
    sf::RectangleShape m_background;
    sf::ui::Label m_title;
    sf::ui::Label m_developer;
    sf::ui::Label m_idea;
    sf::ui::Label m_license;
    sf::ui::Label m_libs;
    sf::ui::Label m_version;
    sf::ui::Button m_back;
};

#endif
