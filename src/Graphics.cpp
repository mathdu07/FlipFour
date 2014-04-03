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

#include "Graphics.h"

Graphics::Graphics()
: m_button(), m_buttonFired()
{

}

void Graphics::load()
{
    m_button.loadFromFile("res/gfx/button.png");
    m_buttonFired.loadFromFile("res/gfx/button_fired.png");
}

sf::Texture const& Graphics::getButton() const
{
    return m_button;
}

sf::Texture const& Graphics::getButtonFired() const
{
    return m_buttonFired;
}
