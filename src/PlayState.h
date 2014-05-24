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

#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "State.h"
#include "Grid.h"

#define FLIPS_COUNT 20

class PlayState : public State
{
public:
    PlayState(Game &game, bool multi);
    
    virtual void init();

    virtual void handleEvent(sf::Event const &event);

    virtual void deInit();

    virtual void render(sf::RenderTarget &target);

    virtual void update();
    
    Case getTurn() const;
    
    void flipLeft1();
    
    void flipRight1();
    
    void flipLeft2();
    
    void flipRight2();
    
private:
    void setTurn(Case c);
    
    void updateLine(Direction d);
    
private:
    bool m_multiplayer; // True -> Multiplayer, False -> Singleplayer VS AI
    sf::RectangleShape m_background;
    Grid m_grid;
    Case m_turn;
    sf::Sprite m_gridSprite;
    sf::ui::Button m_arrowTop1, m_arrowBottom1, m_arrowTop2, m_arrowBottom2;
    sf::Sprite m_backgroundTurn1, m_backgroundTurn2;
    sf::Sprite m_caseTurn1, m_caseTurn2;
    sf::RectangleShape m_lineWin;
    float m_lineStep;
    sf::Sprite m_gameoverPanel;
    sf::ui::Label m_gameoverWinner;
    sf::ui::Button m_gameoverRestart, m_gameoverLeave;
    bool m_gameover;
    sf::Uint32 m_gameoverUpdatesLeft;
    bool m_flipDirection; // True -> Flip Left, false -> Flip Right
    sf::Uint32 m_flipUpdatesLeft;
    bool m_ready;
};

#endif
