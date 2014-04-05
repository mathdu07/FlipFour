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
  m_player1(), m_player2(), m_arrowLeft(), m_arrowRight(),
  m_lineWin()
{
    m_title.setText("Flip Four");
    m_subTitle.setText("1 vs 1");
    m_leave.setText("Leave");
    m_player1.setText("Player 1");
    m_player2.setText("Player 2");
    m_background.setFillColor(sf::Color::Red);
    
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
}

void PlayState::handleEvent(sf::Event const &event)
{
    if (m_grid.isPlaying())
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
                        else if (m_grid.getWinner() != NONE)
                        {
                            std::cout << "Updating line" << std::endl;
                            updateLine(m_grid.getDirectionWin());
                            
                            sf::Vector2f gridPos = m_gridSprite.getPosition() - m_gridSprite.getOrigin();
                            sf::Vector2f gridSize = sf::Vector2f(m_gridSprite.getLocalBounds().width, m_gridSprite.getLocalBounds().height);
                            std::cout << "Grid Bounds : (" << gridPos.x << ";" << gridPos.y << ")";
                            std::cout << " with size (" << gridSize.x << ";" << gridSize.y << ")" << std::endl;
                            sf::Vector2i coord = m_grid.getFirstCaseWin();
                            m_lineWin.setPosition(gridPos.x + (coord.x + 0.5) * gridSize.x / GRID_SIZE,
                            gridPos.y + (coord.y + 0.5) * gridSize.y / GRID_SIZE);
                            //TODO Center line
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
}

void PlayState::updateLine(Direction d)
{
    switch (d)
    {
    case HORIZONTAL:
        m_lineWin.setSize(sf::Vector2f(3 * m_gridSprite.getLocalBounds().width / GRID_SIZE, 5));
        m_lineWin.setRotation(0);
        break;
    case VERTICAL:
        m_lineWin.setSize(sf::Vector2f(5, 3 * m_gridSprite.getLocalBounds().height / GRID_SIZE));
        m_lineWin.setRotation(0);
        break;
    case LEFT_DIAGONAL:
    case RIGHT_DIAGONAL:
        m_lineWin.setSize(sf::Vector2f(sqrt(pow(3 * m_gridSprite.getLocalBounds().width / GRID_SIZE, 2) 
            + pow(3 * m_gridSprite.getLocalBounds().height / GRID_SIZE, 2)), 5));
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
        /*std::cout << "Drawing line" << std::endl;
        sf::FloatRect f = m_lineWin.getLocalBounds();
        std::cout << "Line begin from (" << f.left << ";" << f.top << ")";
        std::cout << " to (" << f.width << ";" << f.height << ")";
        sf::Color c = m_lineWin.getFillColor();
        std::cout << " with color (" << (sf::Uint32) c.r << ";" << (sf::Uint32) c.g << ";";
        std::cout << (sf::Uint32) c.b << ";" << (sf::Uint32) c.a << ")" << std::endl;*/
        target.draw(m_lineWin);
    }
}

void PlayState::update()
{

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
