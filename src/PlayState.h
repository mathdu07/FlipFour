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
    
private:
    void setTurn(Case c);
    
    void updateLine(Direction d);
    
private:
    bool m_multiplayer; // True -> Multiplayer, False -> Singleplayer VS AI
    sf::RectangleShape m_background;
    sf::ui::Label m_title, m_subTitle;
    sf::ui::Button m_leave;
    Grid m_grid;
    Case m_turn;
    sf::Sprite m_gridSprite;
    sf::ui::Label m_player1, m_player2;
    sf::ui::Button m_arrowLeft, m_arrowRight;
    sf::RectangleShape m_lineWin;
    float m_lineStep;
};

#endif
