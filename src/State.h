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

#ifndef STATE_H
#define STATE_H

#include "Main.h"
#include "Game.h"

class State
{
public:
    State(Game &game);

    virtual void init() = 0;

    virtual void handleEvent(sf::Event const &event) = 0;

    virtual void deInit() = 0;

    virtual void render(sf::RenderTarget &target) = 0;

    virtual void update() = 0;

protected:
    Game &m_game;
};

#endif
