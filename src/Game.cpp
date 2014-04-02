/*
 *  This file is part of Four Flip.
 *
 *  Four Flip is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Four Flip is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. *  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Four Flip. If not, see <http://www.gnu.org/licenses/>.
 */
 #include "Game.h"
 
Game::Game(sf::RenderWindow &window)
: m_window(window)
{

}
    
sf::RenderWindow& Game::getWindow()
{
    return m_window;
}
    
void Game::run()
{
    m_window.create(sf::VideoMode(480, 800), "Four Flip");
    sf::Event event;
    
    while (m_window.isOpen())
    {
        m_window.waitEvent(event);
        
        handleEvent(event);
        
        m_window.clear();
        
        
        
        m_window.display();
    }
}
    
void Game::handleEvent(sf::Event const &event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        m_window.close();
        break;
    default:
        break;
    }
}
