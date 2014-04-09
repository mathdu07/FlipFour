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

#include "PlayState.h"
#include <cmath>

PlayState::PlayState(Game &game, bool multi)
: State(game), m_multiplayer(multi),
  m_background(), m_title(), m_subTitle(),
  m_leave(&game, &Game::switchToMainMenu), 
  m_grid(*this), m_turn(NONE), m_gridSprite(),
  m_player1(), m_player2(),
  m_arrowLeft(this, &PlayState::flipLeft),
  m_arrowRight(this, &PlayState::flipRight),
  m_lineWin(), m_lineStep(0), m_gameoverPanel(),
  m_gameoverLabel(), m_gameoverWinner(), 
  m_gameoverButton(&game, &Game::playMultiplayer),
  m_gameover(false), m_gameoverUpdatesLeft(20),
  m_flipDirection(false), m_flipUpdatesLeft(0),
  m_ready(true)
{
    m_title.setText("Flip Four");
    m_subTitle.setText("1 vs 1");
    m_leave.setText("Leave");
    m_player1.setText("Player 1");
    m_player2.setText("Player 2");
    m_background.setFillColor(sf::Color::Red);
    
    m_gameoverLabel.setText("Game Over");
    m_gameoverButton.setText("Replay");
    
    setTurn(PLAYER_1);
}
    
void PlayState::init()
{
    m_background.setSize(sf::Vector2f(m_game.getSize()));

    Fonts const &f = m_game.fonts();
    m_title.setFont(f.getBold());
    m_title.setFontColor(sf::Color::White);
    m_title.setFontSize(45);
    m_title.setPosition(120, 50);
    
    m_subTitle.setFont(f.getContent());
    m_subTitle.setFontColor(sf::Color::White);
    m_subTitle.setFontSize(35);
    m_subTitle.setPosition(180, 110);
    
    m_player1.setFont(f.getContent());
    m_player1.setFontSize(25);
    m_player1.setPosition(60, 200);
    
    m_player2.setFont(f.getContent());
    m_player2.setFontSize(25);
    m_player2.setPosition(340, 200);
    
    Graphics const &g = m_game.gfx();
    m_leave.setFont(f.getContent());
    m_leave.setFontColor(sf::Color::Black);
    m_leave.setTexture(g.getButton());
    m_leave.setTextureFocused(g.getButton());
    m_leave.setTextureFired(g.getButtonFired());
    m_leave.setPosition(m_game.getSize().x/2 - m_leave.getSize().x/2, 700);
    
    m_grid.init();
    sf::Texture const &gridTex = m_grid.getGridTexture();
    m_gridSprite.setTexture(gridTex);
    m_gridSprite.setOrigin(sf::Vector2f(gridTex.getSize()) / 2.f);
    m_gridSprite.setPosition(m_game.getSize().x/2, 400);
    
    m_arrowLeft.setTexture(g.getArrowLeft());
    m_arrowLeft.setTextureFocused(g.getArrowLeft());
    m_arrowLeft.setTextureFired(g.getArrowLeft());
    m_arrowLeft.setPosition(m_gridSprite.getPosition() + m_gridSprite.getOrigin() - sf::Vector2f(gridTex.getSize().x + g.getArrowLeft().getSize().x, 0));
    
    m_arrowRight.setTexture(g.getArrowRight());
    m_arrowRight.setTextureFocused(g.getArrowRight());
    m_arrowRight.setTextureFired(g.getArrowRight());
    m_arrowRight.setPosition(m_gridSprite.getPosition() + m_gridSprite.getOrigin());
    
    m_lineWin.setFillColor(g.getMainColor());
    
    m_gameoverPanel.setTexture(g.getGameoverBackground());
    m_gameoverPanel.setPosition(sf::Vector2f(m_game.getSize()) / 2.f - sf::Vector2f(m_gameoverPanel.getLocalBounds().width, m_gameoverPanel.getLocalBounds().height) / 2.f);
    
    m_gameoverLabel.setFont(f.getBold());
    m_gameoverLabel.setFontColor(sf::Color::White);
    m_gameoverLabel.setFontSize(30);
    m_gameoverLabel.setPosition(140, 180);
    
    m_gameoverWinner.setFont(f.getContent());
    m_gameoverWinner.setFontColor(sf::Color::Black);
    m_gameoverWinner.setFontSize(40);
    m_gameoverWinner.setPosition(100, 370);
    
    m_gameoverButton.setFont(f.getContent());
    m_gameoverButton.setFontColor(sf::Color::Black);
    m_gameoverButton.setTexture(g.getButton());
    m_gameoverButton.setTextureFocused(g.getButton());
    m_gameoverButton.setTextureFired(g.getButtonFired());
    m_gameoverButton.setPosition(m_game.getSize().x/2 - m_leave.getSize().x/2, 540);
}

void PlayState::handleEvent(sf::Event const &event)
{
    if (m_grid.isPlaying() && m_ready)
    {
        switch (event.type)
        {
        case sf::Event::MouseButtonReleased:
        {
            sf::Event::MouseButtonEvent me = event.mouseButton;
            
            if (me.button == sf::Mouse::Left)
            {
                int x = me.x - m_gridSprite.getPosition().x + m_gridSprite.getOrigin().x;
                int y = me.y - m_gridSprite.getPosition().y + m_gridSprite.getOrigin().y;
                
                if (m_grid.isInGrid(x, y))
                {
                    sf::Vector2i coord = m_grid.getMapCoordAt(x, y);
                    
                    if (m_grid.getCaseAt(coord.x, coord.y) == NONE)
                    {
                        m_grid.setCaseAt(coord.x, coord.y, m_turn);
                        
                        if (m_grid.isPlaying())
                        {
                            setTurn(m_turn == PLAYER_1 ? PLAYER_2 : PLAYER_1);
                        }
                        else
                        {
                            m_gameoverWinner.setText(m_grid.getWinner() == PLAYER_1 ? "Player 1 won" : (m_grid.getWinner() == PLAYER_2 ? "Player 2 won" : "   Tie !"));
                        }
                    }
                }

            }
            
            break;
        }
        default:
            break;
        }
    }
        
    m_leave.updateEvent(event);
    m_arrowLeft.updateEvent(event);
    m_arrowRight.updateEvent(event);
    
    if (m_gameover)
    {
        m_gameoverButton.updateEvent(event);
    }
}

void PlayState::updateLine(Direction d)
{
    switch (d)
    {
    case HORIZONTAL:
        m_lineWin.setSize(sf::Vector2f(3 * m_gridSprite.getLocalBounds().width / GRID_SIZE * m_lineStep, 3));
        m_lineWin.setRotation(0);
        break;
    case VERTICAL:
        m_lineWin.setSize(sf::Vector2f(3, 3 * m_gridSprite.getLocalBounds().height / GRID_SIZE * m_lineStep));
        m_lineWin.setRotation(0);
        break;
    case LEFT_DIAGONAL:
    case RIGHT_DIAGONAL:
        m_lineWin.setSize(sf::Vector2f(sqrt(pow(3 * m_gridSprite.getLocalBounds().width / GRID_SIZE, 2) 
            + pow(3 * m_gridSprite.getLocalBounds().height / GRID_SIZE, 2)) * m_lineStep, 3));
        m_lineWin.setRotation(d == LEFT_DIAGONAL ? 45 : -45);
        break;
    }
}

void PlayState::deInit()
{

}

void PlayState::render(sf::RenderTarget &target)
{
    target.draw(m_background);
    target.draw(m_title);
    target.draw(m_subTitle);
    target.draw(m_leave);
    target.draw(m_player1);
    target.draw(m_player2);
    target.draw(m_arrowLeft);
    target.draw(m_arrowRight);
    
    m_grid.render();
    target.draw(m_gridSprite);
    
    if (!m_grid.isPlaying())
    {
        target.draw(m_lineWin);
    }
    
    if (m_gameover)
    {
            target.draw(m_gameoverPanel);
            target.draw(m_gameoverLabel);
            target.draw(m_gameoverWinner);
            target.draw(m_gameoverButton);        
    }
}

void PlayState::update()
{
    if (!m_grid.isPlaying() && m_grid.getWinner() != NONE && m_lineStep < 1)
    {
        m_lineStep += 0.1; 
        std::cout << "Updating line" << std::endl;
        updateLine(m_grid.getDirectionWin());
        
        sf::Vector2f gridPos = m_gridSprite.getPosition() - m_gridSprite.getOrigin();
        sf::Vector2f gridSize = sf::Vector2f(m_gridSprite.getLocalBounds().width, m_gridSprite.getLocalBounds().height);
        std::cout << "Grid Bounds : (" << gridPos.x << ";" << gridPos.y << ")";
        std::cout << " with size (" << gridSize.x << ";" << gridSize.y << ")" << std::endl;
        sf::Vector2i coord = m_grid.getFirstCaseWin();
        m_lineWin.setPosition(gridPos.x + (coord.x + 0.5) * gridSize.x / GRID_SIZE,
        gridPos.y + (coord.y + 0.5) * gridSize.y / GRID_SIZE);
        
        switch (m_grid.getDirectionWin())
        {
        case HORIZONTAL:
            m_lineWin.move(0, - m_lineWin.getSize().y / 2.f);
            break;
        case VERTICAL:
            m_lineWin.move(- m_lineWin.getSize().x / 2.f, 0);
            break;
        case LEFT_DIAGONAL:
        case RIGHT_DIAGONAL:
            m_lineWin.move(- m_lineWin.getSize().y / 2.f, - m_lineWin.getSize().y / 2.f);
            break;
        }
    }
    
    if (!m_grid.isPlaying() && m_gameoverUpdatesLeft > 0)
    {
        m_gameoverUpdatesLeft--;
        
        if (m_gameoverUpdatesLeft == 0)
        {
            m_gameover = true;
        }
    }
    
    if (m_flipUpdatesLeft > 0)
    {
        m_gridSprite.rotate((m_flipDirection ? 1 : -1) * 90 / (float) FLIPS_COUNT);
        m_flipUpdatesLeft--;
        
        if (m_flipUpdatesLeft == 0)
        {
            m_gridSprite.setRotation(0);
            m_grid.flip(m_turn, m_flipDirection);
            setTurn(m_turn == PLAYER_1 ? PLAYER_2 : PLAYER_1);
            m_ready = true;
            
            if (!m_grid.isPlaying())
            {
                m_gameoverWinner.setText(m_grid.getWinner() == PLAYER_1 ? "Player 1 won" : (m_grid.getWinner() == PLAYER_2 ? "Player 2 won" : "   Tie !"));
            }
        }
    }
}

void PlayState::flipLeft()
{
    if (m_grid.isPlaying() && m_ready)
    {
        m_flipDirection = true;
        m_flipUpdatesLeft = FLIPS_COUNT;
        m_ready = false;
    }
}
    
void PlayState::flipRight()
{
    if (m_grid.isPlaying() && m_ready)
    {
        m_flipDirection = false;
        m_flipUpdatesLeft = FLIPS_COUNT;
        m_ready = false;
    }
}
    
Case PlayState::getTurn() const
{
    return m_turn;
}

void PlayState::setTurn(Case c)
{
    m_turn = c;
    m_player1.setFontColor(c == PLAYER_1 ? sf::Color::Green : sf::Color::Black);
    m_player2.setFontColor(c == PLAYER_2 ? sf::Color::Green : sf::Color::Black);
}
