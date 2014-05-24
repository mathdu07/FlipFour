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

 #include "MainMenuState.h"

MainMenuState::MainMenuState(Game &game)
: State(game), m_background(), m_title(),
  m_versusButton(&game, &Game::playMultiplayer),
  m_aboutButton(&game, &Game::switchToAbout), m_exitButton(&game, &Game::exit),
  m_versionType()
{
    m_versusButton.setText("Versus");
    m_aboutButton.setText("About");
    m_exitButton.setText("Exit");
    m_title.setText("Flip Four");
    m_background.setSize(sf::Vector2f(game.getSize().x, game.getSize().y));
    m_background.setFillColor(sf::Color::Red);
    m_versionType.setText("Beta Prototype");
}

void MainMenuState::init()
{
    Graphics const &g = m_game.gfx();
    m_versusButton.setTexture(g.getBigButton());
    m_aboutButton.setTexture(g.getSettings());
    m_exitButton.setTexture(g.getReturn());
    
    m_versusButton.setTextureFocused(g.getBigButton());
    m_aboutButton.setTextureFocused(g.getSettings());
    m_exitButton.setTextureFocused(g.getReturn());

    m_versusButton.setTextureFired(g.getBigButtonFired());
    m_aboutButton.setTextureFired(g.getSettingsFired());
    m_exitButton.setTextureFired(g.getReturnFired());

    Fonts const &f = m_game.fonts();
    m_versusButton.setFont(f.getBold());
    m_versusButton.setFontColor(sf::Color::Black);

    m_title.setFont(f.getBold());
    m_title.setFontColor(sf::Color::White);
    m_title.setFontSize(50);
    m_title.setPosition(m_game.getSize().x/2 - m_title.getSize().x/2, 25);

    m_versusButton.setPosition(m_game.getSize().x/2 - m_versusButton.getSize().x/2, m_game.getSize().y/2 - m_versusButton.getSize().y/2);
    m_aboutButton.setPosition(20, m_game.getSize().y - m_aboutButton.getSize().y - 10);
    m_exitButton.setPosition(m_game.getSize().x - m_exitButton.getSize().x - 20, m_game.getSize().y - m_exitButton.getSize().y - 10);
    
    m_versionType.setFont(f.getContent());
    m_versionType.setFontColor(sf::Color::White);
    m_versionType.setFontSize(22);
    m_versionType.setPosition(m_game.getSize().x/2 - m_versionType.getSize().x/2, m_game.getSize().y - m_versionType.getSize().y - 20);
}

void MainMenuState::handleEvent(sf::Event const &event)
{
    m_versusButton.updateEvent(event);
    m_aboutButton.updateEvent(event);
    m_exitButton.updateEvent(event);
    m_title.updateEvent(event);
}

void MainMenuState::deInit()
{

}

void MainMenuState::render(sf::RenderTarget &target)
{
    target.draw(m_background); // TODO Background
    target.draw(m_title);
    target.draw(m_versusButton);
    target.draw(m_aboutButton);
    target.draw(m_exitButton);
    target.draw(m_versionType);
}

void MainMenuState::update()
{
    //TODO Update dynamic background
}
