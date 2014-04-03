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
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. *  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Flip Four. If not, see <http://www.gnu.org/licenses/>.
 */
 #include "Game.h"
 #include "State.h"
 #include "MainMenuState.h"

Game::Game(sf::RenderWindow &window)
: m_window(window), m_assets(), m_oldState(0), m_state(0)
{

}

Game::~Game()
{
    if (m_oldState)
        delete m_oldState;

    if (m_state)
        delete m_state;
}

sf::RenderWindow& Game::getWindow()
{
    return m_window;
}

void Game::run()
{
    m_window.create(sf::VideoMode(480, 800), "Flip Four");
    m_assets.loadAssets();
    setState(new MainMenuState(*this));
    sf::Event event;
    sf::Time updateDelta(sf::seconds(1 / 20.0));
    sf::Clock updateClock;
    sf::Time nextUpdate(updateClock.getElapsedTime());

    while (m_window.isOpen())
    {
        while (m_window.pollEvent(event))
            handleEvent(event);

        if (nextUpdate <= updateClock.getElapsedTime())
        {
            sf::Time currentTime(updateClock.getElapsedTime());
            while (nextUpdate <= currentTime)
            {
                m_state->update();
                nextUpdate += updateDelta;
            }
        }
        else
        {
            sf::Time sleepTime(nextUpdate - updateClock.getElapsedTime());
            sf::sleep(sleepTime);
        }

        m_window.clear();

        m_state->render(m_window);

        m_window.display();
    }
}

void Game::handleEvent(sf::Event const &event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        exit();
        break;
    default:
        break;
    }

    if (m_window.isOpen() && m_state != 0)
    {
        m_state->handleEvent(event);
    }
}

void Game::exit()
{
    m_window.close();
}

Graphics const& Game::gfx()
{
    return m_assets.getGraphics();
}

Fonts const& Game::fonts()
{
    return m_assets.getFonts();
}

void Game::setState(State *newState)
{
    if (newState != m_state && m_state != 0 && newState != 0)
    {
        m_state->deInit();

        if (m_oldState)
            delete m_oldState;

        m_oldState = m_state;
        m_state = 0;
    }

    if (newState)
    {
        m_state = newState;
        m_state->init();
    }
}

State& Game::getState()
{
    return *m_state;
}

sf::Vector2u Game::getSize() const
{
    return m_window.getSize();
}
