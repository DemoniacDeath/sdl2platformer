#include "Game.h"

#include "RenderObject.h"
#include "GOPlayer.h"
#include "GOFrame.h"

bool Game::init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	GameSettings * settings = new GameSettings();
	context = new GameContext(settings);
	return context != NULL;
}

void Game::run()
{
	if (init())
	{
		SDL_Event e;

		GOPlayer * player = new GOPlayer(context, { context->world->rect.w/2-30,0,60,120 });
		player->renderObject = new RenderObject(context, player->rect, Color(0x00, 0xFF, 0x00, 0xFF));
		player->speed = 4;
		player->jumpSpeed = 10;

		context->world->children.push_back(player);

		context->world->children.push_back(new GOFrame(context, { 0,0,context->world->rect.w,context->world->rect.h }, 60));

		//context->world->children.push_back(new GOFrame(context, { context->world->rect.w/2, context->world->rect.h-120, 60, 60}, 20));

		GOSolid * brick;
		for (int i = 0; i < 3; i++)
		{
			brick = new GOSolid(context, { 60+i*60, context->world->rect.h - 120, 60, 60 });
			brick->renderObject = new RenderObject(context, brick->rect, Color(0x00, 0x00, 0x00, 0xFF));
			context->world->children.push_back(brick);
		}

		brick = NULL;
		player = NULL;

		while (!context->quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type)
				{
				case SDL_QUIT:
					context->quit = true;
					break;
				}
				//player->handleEvent(&e);
				context->world->handleEvent(&e);
			}

			context->world->handleKeyboard(SDL_GetKeyboardState(NULL));
			context->world->processPhysics();
			context->world->detectCollisions();

			//Clear screen
			SDL_SetRenderDrawColor(context->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(context->renderer);

			context->world->render();

			//Update screen
			SDL_RenderPresent(context->renderer);
		}
	}
	exit();
}

void Game::exit()
{
	context->free();

	SDL_Quit();
}