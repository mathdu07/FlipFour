/*
 *  This file is part of Four Flip.
 *
 *  Four Flip is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Four Flip is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. *  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Four Flip. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "Main.h"
#include <cstdlib>
#include "Game.h"
 
int main(int argc, char *argv[])
{
    std::cout << "Starting Four Flip v" << FOUR_FLIP_VERSION_MAJOR;
    std::cout << "." << FOUR_FLIP_VERSION_MINOR;
    std::cout << "." << FOUR_FLIP_VERSION_PATCH << std::endl;

    sf::RenderWindow window;
    Game game(window);
    
    game.run();
    
    return EXIT_SUCCESS;
}
