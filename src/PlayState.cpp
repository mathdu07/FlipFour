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
  m_background(),
  m_grid(*this), m_turn(NONE), m_gridSprite(),
  m_arrowTop1(this, &PlayState::flipLeft1),
  m_arrowBottom1(this, &PlayState::flipRight1),
  m_arrowTop2(this, &PlayState::flipRight2),
  m_arrowBottom2(this, &PlayState::flipLeft2),
  m_lineWin(), m_lineStep(0), m_gameoverPanel(),
  m_gameoverWinner(), 
  m_gameoverRestart(&game, &Game::playMultiplayer),
  m_gameoverLeave(&game, &Game::switchToMainMenu),
  m_gameover(false), m_gameoverUpdatesLeft(20),
  m_flipDirection(false), m_flipUpdatesLeft(0),
  m_ready(true)
{
    m_background.setFillColor(sf::Color::Red);
    
    setTurn(PLAYER_1);
}
    
void PlayState::init()
{
    m_background.setSize(sf::Vector2f(m_game.getSize()));    
    
    Graphics const &g = m_game.gfx();
    Fonts const &f = m_game.fonts();
        
    m_grid.init();
    sf::Texture const &gridTex = m_grid.getGridTexture();
    m_gridSprite.setTexture(gridTex);
    m_gridSprite.setOrigin(sf::Vector2f(gridTex.getSize()) / 2.f);
    m_gridSprite.setPosition(m_game.getSize().x/2, m_game.getSize().y/2);
    
    m_arrowTop1.setTexture(g.getArrowTopLeft());
    m_arrowTop1.setTextureFocused(g.getArrowTopLeft());
    m_arrowTop1.setTextureFired(g.getArrowTopLeftFired());
    m_arrowTop1.setPosition(m_gridSprite.getPosition() - m_gridSprite.getOrigin() - m_arrowTop1.getSize());
    
    m_arrowBottom1.setTexture(g.getArrowBottomLeft());
    m_arrowBottom1.setTextureFocused(g.getArrowBottomLeft());
    m_arrowBottom1.setTextureFired(g.getArrowBottomLeftFired());
    m_arrowBottom1.setPosition(sf::Vector2f(m_gridSprite.getPosition().x - m_gridSprite.getOrigin().x - m_arrowBottom1.getSize().x, m_gridSprite.getPosition().y + m_gridSprite.getOrigin().y));
    
    m_arrowTop2.setTexture(g.getArrowTopRight());
    m_arrowTop2.setTextureFocused(g.getArrowTopRight());
    m_arrowTop2.setTextureFired(g.getArrowTopRightFired());
    m_arrowTop2.setPosition(sf::Vector2f(m_gridSprite.getPosition().x + m_gridSprite.getOrigin().x, m_gridSprite.getPosition().y - m_gridSprite.getOrigin().y - m_arrowTop2.getSize().y));
    
    m_arrowBottom2.setTexture(g.getArrowBottomRight());
    m_arrowBottom2.setTextureFocused(g.getArrowBottomRight());
    m_arrowBottom2.setTextureFired(g.getArrowBottomRightFired());
    m_arrowBottom2.setPosition(m_gridSprite.getPosition() + m_gridSprite.getOrigin());
    
    m_lineWin.setFillColor(g.getMainColor());
    
    m_gameoverPanel.setTexture(g.getGameoverBackground());
    m_gameoverPanel.setPosition(sf::Vector2f(m_game.getSize()) / 2.f - sf::Vector2f(m_gameoverPanel.getLocalBounds().width, m_gameoverPanel.getLocalBounds().height) / 2.f);
       
    m_gameoverWinner.setFont(f.getContent());
    m_gameoverWinner.setFontColor(g.getContentColor());
    m_gameoverWinner.setFontSize(40);
    m_gameoverWinner.setPosition(m_game.getSize().x/2 - m_gameoverWinner.getSize().x/2, m_gameoverPanel.getPosition().y + 50);
    
    m_gameoverRestart.setTexture(g.getRestart());
    m_gameoverRestart.setTextureFocused(g.getRestart());
    m_gameoverRestart.setTextureFired(g.getRestartFired());
    m_gameoverRestart.setPosition(m_gameoverPanel.getPosition().x + 20, m_gameoverPanel.getPosition().y + m_gameoverPanel.getLocalBounds().height - m_gameoverRestart.getSize().y - 20);
    
    m_gameoverLeave.setTexture(g.getReturn());
    m_gameoverLeave.setTextureFocused(g.getReturn());
    m_gameoverLeave.setTextureFired(g.getReturnFired());
    m_gameoverLeave.setPosition(m_gameoverPanel.getPosition().x + m_gameoverPanel.getLocalBounds().width - m_gameoverLeave.getSize().x - 20, m_gameoverPanel.getPosition().y + m_gameoverPanel.getLocalBounds().height - m_gameoverLeave.getSize().y - 20);
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
                            m_gameoverWinner.setText(m_grid.getWinner() == PLAYER_1 ? "Player 1 won" : (m_grid.getWinner() == PLAYER_2 ? "Player 2 won" : "Tie !"));
                            m_gameoverWinner.setPosition(m_game.getSize().x/2 - m_gameoverWinner.getSize().x/2, m_gameoverPanel.getPosition().y + 50);
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
    
    m_arrowTop1.updateEvent(event);
    m_arrowBottom1.updateEvent(event);
    m_arrowTop2.updateEvent(event);
    m_arrowBottom2.updateEvent(event);
    
    if (m_gameover)
    {
        m_gameoverRestart.updateEvent(event);
        m_gameoverLeave.updateEvent(event);
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
    target.draw(m_arrowTop1);
    target.draw(m_arrowBottom1);
    target.draw(m_arrowTop2);
    target.draw(m_arrowBottom2);
    
    m_grid.render();
    target.draw(m_gridSprite);
    
    if (!m_grid.isPlaying())
    {
        target.draw(m_lineWin);
    }
    
    if (m_gameover)
    {
            target.draw(m_gameoverPanel);
            target.draw(m_gameoverWinner);
            target.draw(m_gameoverRestart);     
            target.draw(m_gameoverLeave);   
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
                m_gameoverWinner.setText(m_grid.getWinner() == PLAYER_1 ? "Player 1 won" : (m_grid.getWinner() == PLAYER_2 ? "Player 2 won" : "Tie !"));
                m_gameoverWinner.setPosition(m_game.getSize().x/2 - m_gameoverWinner.getSize().x/2, m_gameoverPanel.getPosition().y + 50);
            }
        }
    }
}

void PlayState::flipLeft1()
{
    if (m_grid.isPlaying() && m_ready && m_turn == PLAYER_1)
    {
        m_flipDirection = true;
        m_flipUpdatesLeft = FLIPS_COUNT;
        m_ready = false;
    }
}
    
void PlayState::flipRight1()
{
    if (m_grid.isPlaying() && m_ready && m_turn == PLAYER_1)
    {
        m_flipDirection = false;
        m_flipUpdatesLeft = FLIPS_COUNT;
        m_ready = false;
    }
}
    
void PlayState::flipLeft2()
{
    if (m_grid.isPlaying() && m_ready && m_turn == PLAYER_2)
    {
        m_flipDirection = true;
        m_flipUpdatesLeft = FLIPS_COUNT;
        m_ready = false;
    }
}
    
void PlayState::flipRight2()
{
    if (m_grid.isPlaying() && m_ready && m_turn == PLAYER_2)
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
}
