#include "Game.h"

#include <time.h>
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

		context->world = new GOWorld(context, Rect(0, 0, float(context->settings->windowWidth/2.), float(context->settings->windowHeight/2.)));
		context->world->camera->originalSize.width /= 2;
		context->world->camera->originalSize.height /= 2;

		GOPlayer * player = new GOPlayer(context, Rect( 0,20,10,20 ));

		player->idleAnimation = Animation::animationWithSingleRenderObject(RenderObject::renderObjectFromFile(context, "img/idle.png"));
		player->moveAnimation = Animation::animationWithSpeedAndTextureFile(80, context, "img/move.png", 40, 80, 6);
		player->jumpAnimation = Animation::animationWithSingleRenderObject(RenderObject::renderObjectFromFile(context, "img/jump.png"));
		player->crouchAnimation = Animation::animationWithSingleRenderObject(RenderObject::renderObjectFromFile(context, "img/crouch.png"));
		player->crouchMoveAnimation = Animation::animationWithSingleRenderObject(RenderObject::renderObjectFromFile(context, "img/crouch.png"));

		player->speed = 1.3f;
		player->jumpSpeed = 2.5f;
		player->physics->gravityForce = 0.1f;
		player->addChild(context->world->camera);

		context->world->addChild(player);

		context->world->addChild(new GOFrame(context, Rect( 0,0,context->world->frame.size.width,context->world->frame.size.height ), 10));

		GOSolid * brick;
		srand((unsigned int)time(NULL));
		int x = int(context->world->frame.size.width / 10 - 2);
		int y = int(context->world->frame.size.height / 10 - 2);
		int rndx, rndy;
		for (int i = 0; i < 100; i++)
		{
			rndx = rand() % x;
			rndy = rand() % y;
			brick = new GOSolid(context, Rect(float(context->world->frame.size.width / 2) - 15 - rndx * 10, float(context->world->frame.size.height / 2) - 15 - rndy * 10, 10, 10 ));
			brick->renderObject = RenderObject::renderObjectFromColor(context, Color(0x00, 0x00, 0x00, 0xFF));
			context->world->addChild(brick);
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
				context->world->handleEvent(&e);
			}

			context->world->handleKeyboard(SDL_GetKeyboardState(NULL));
			context->world->processPhysics();
			context->world->detectCollisions();
			context->world->animate();

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