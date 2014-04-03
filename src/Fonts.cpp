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

#include "Fonts.h"

Fonts::Fonts()
: m_content(), m_bold(), m_oblique()
{

}

void Fonts::load()
{
    m_content.loadFromFile("res/fonts/purisa.ttf");
    m_bold.loadFromFile("res/fonts/purisa-bold.ttf");
    m_oblique.loadFromFile("res/fonts/purisa-oblique.ttf");
}

sf::Font const& Fonts::getContent() const
{
    return m_content;
}

sf::Font const& Fonts::getBold() const
{
    return m_bold;
}

sf::Font const& Fonts::getOblique() const
{
    return m_oblique;
}
