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
  m_singleplayerButton(), m_multiplayerButton(),
  m_aboutButton(&game, &Game::switchToAbout), m_exitButton(&game, &Game::exit)
{
    m_singleplayerButton.setText("Single Player");
    m_multiplayerButton.setText("Multi Player");
    m_aboutButton.setText("About");
    m_exitButton.setText("Exit");
    m_title.setText("Flip Four");
    m_background.setSize(sf::Vector2f(game.getSize().x, game.getSize().y));
    m_background.setFillColor(sf::Color::Red);
}

void MainMenuState::init()
{
    Graphics const &g = m_game.gfx();
    m_singleplayerButton.setTexture(g.getButton());
    m_multiplayerButton.setTexture(g.getButton());
    m_aboutButton.setTexture(g.getButton());
    m_exitButton.setTexture(g.getButton());

    m_singleplayerButton.setTextureFocused(g.getButton());
    m_multiplayerButton.setTextureFocused(g.getButton());
    m_aboutButton.setTextureFocused(g.getButton());
    m_exitButton.setTextureFocused(g.getButton());

    m_singleplayerButton.setTextureFired(g.getButtonFired());
    m_multiplayerButton.setTextureFired(g.getButtonFired());
    m_aboutButton.setTextureFired(g.getButtonFired());
    m_exitButton.setTextureFired(g.getButtonFired());

    Fonts const &f = m_game.fonts();
    m_singleplayerButton.setFont(f.getContent());
    m_multiplayerButton.setFont(f.getContent());
    m_aboutButton.setFont(f.getContent());
    m_exitButton.setFont(f.getContent());

    m_singleplayerButton.setFontColor(sf::Color::Black);
    m_multiplayerButton.setFontColor(sf::Color::Black);
    m_aboutButton.setFontColor(sf::Color::Black);
    m_exitButton.setFontColor(sf::Color::Black);

    m_title.setFont(f.getBold());
    m_title.setFontColor(sf::Color::White);
    m_title.setFontSize(45);
    m_title.setPosition(m_game.getSize().x/2 - 120, 50);

    m_singleplayerButton.setPosition(m_game.getSize().x/2 - m_singleplayerButton.getSize().x/2, 200);
    m_multiplayerButton.setPosition(m_game.getSize().x/2 - m_multiplayerButton.getSize().x/2, 350);
    m_aboutButton.setPosition(m_game.getSize().x/2 - m_aboutButton.getSize().x/2, 500);
    m_exitButton.setPosition(m_game.getSize().x/2 - m_exitButton.getSize().x/2, 650);
}

void MainMenuState::handleEvent(sf::Event const &event)
{
    m_singleplayerButton.updateEvent(event);
    m_multiplayerButton.updateEvent(event);
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
    target.draw(m_singleplayerButton);
    target.draw(m_multiplayerButton);
    target.draw(m_aboutButton);
    target.draw(m_exitButton);
}

void MainMenuState::update()
{
    //TODO Update dynamic background
}
