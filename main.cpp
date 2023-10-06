#include <iostream>
#include "Game.h"

int main()
{
    Game* game_of_life = new Game(1350, 680, 4, 300, 100);
    game_of_life->init();

    while (game_of_life->shouldRun())
    {
        game_of_life->run();
    }

    game_of_life->close();
    delete game_of_life;
	return 0;
}