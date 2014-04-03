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

#include "AboutState.h"
#include <sstream>

AboutState::AboutState(Game &game)
: State(game), m_background(),
  m_title(), m_developer(), m_license(), m_version(),
  m_back(&game, &Game::switchToMainMenu)
{
    m_title.setText("About");
    m_developer.setText("Developed by Mathieu Margier");
    m_license.setText("Distributed under GPLv3 license");
    
    std::ostringstream version;
    version << "Version : ";
    version << FLIP_FOUR_VERSION_MAJOR << ".";
    version << FLIP_FOUR_VERSION_MINOR << ".";
    version << FLIP_FOUR_VERSION_PATCH;
    
    m_version.setText(version.str());
    
    m_back.setText("<- Back");
    
    m_background.setFillColor(sf::Color::Red);
}

void AboutState::init()
{
    m_background.setSize(sf::Vector2f(m_game.getSize().x, m_game.getSize().y));
    
    Fonts const &f = m_game.fonts();
    m_title.setFont(f.getBold());
    m_title.setFontSize(45);
    m_title.setFontColor(sf::Color::White);
    m_title.setPosition(m_game.getSize().x / 2 - 80, 50);
    
    m_developer.setFont(f.getContent());
    m_developer.setFontSize(25);
    m_developer.setFontColor(sf::Color::White);
    m_developer.setPosition(20, 300);
    
    m_license.setFont(f.getContent());
    m_license.setFontSize(25);
    m_license.setFontColor(sf::Color::White);
    m_license.setPosition(20, 350);
    
    m_version.setFont(f.getContent());
    m_version.setFontSize(25);
    m_version.setFontColor(sf::Color::White);
    m_version.setPosition(20, 400);
    
    Graphics const &g = m_game.gfx(); 
    m_back.setTexture(g.getButton());
    m_back.setTextureFocused(g.getButton());
    m_back.setTextureFired(g.getButtonFired());
    m_back.setFont(f.getContent());
    m_back.setFontSize(25);
    m_back.setFontColor(sf::Color::Black);
    m_back.setPosition(m_game.getSize().x / 2 - m_back.getSize().x / 2, 700);
}

void AboutState::handleEvent(sf::Event const &event)
{
    m_title.updateEvent(event);
    m_developer.updateEvent(event);
    m_license.updateEvent(event);
    m_version.updateEvent(event);
    m_back.updateEvent(event);
}

void AboutState::deInit()
{

}

void AboutState::render(sf::RenderTarget &target)
{
    target.draw(m_background);
    target.draw(m_title);
    target.draw(m_developer);
    target.draw(m_license);
    target.draw(m_version);
    target.draw(m_back);
}

void AboutState::update()
{

}