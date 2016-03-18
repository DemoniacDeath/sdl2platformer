/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "game.h"

int main(int argc, char* args[])
{
	Game * game = new Game();
	game->run();
	return 0;
}