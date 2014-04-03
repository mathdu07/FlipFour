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

#ifndef GAME_H
#define GAME_H

//Forward class
class State;

#include "Main.h"
#include "Assets.h"

class Game
{
public:
    Game(sf::RenderWindow &window);
    virtual ~Game();

    sf::RenderWindow& getWindow();

    void run();

    Graphics const& gfx();
    Fonts const& fonts();

    State& getState();

    sf::Vector2u getSize() const;

    void switchToMainMenu();
    void switchToAbout();

    void exit();

private:
    void handleEvent(sf::Event const &event);

    void setState(State *newState);

private:
    sf::RenderWindow &m_window;
    Assets m_assets;
    State *m_oldState, *m_state;
};

#endif
