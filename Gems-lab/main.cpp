//
//  main.cpp
//  GEMS
//
//  Created by Alexandra Tronyagina on 01.06.2022.
//

#include "game.hpp"

int main(void) {
    srand((unsigned int)(time(0)));
    Game game;
    int countOfClicks = 0;
    sf::Vector2i prevClickCoordinates;
    while (game.window.isOpen()) {
        game.run(countOfClicks, prevClickCoordinates);
        game.drawInWindow();
    }
    return 0;
}
