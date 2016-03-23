#include "Game.h"

#include <time.h>
#include <stdlib.h>
#include "RenderObject.h"
#include "GOPlayer.h"
#include "GOFrame.h"
#include "GOConsumable.h"

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

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not be initialized! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() == -1)
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
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

		context->world->addChild(new GOFrame(context, Rect( 0,0,context->world->frame.size.width,context->world->frame.size.height ), 10));

		GameObject * object;
		srand((unsigned int)time(NULL));
		int count = 200;
		int powerCount = 100;
		int x = int(context->world->frame.size.width / 10 - 2);
		int y = int(context->world->frame.size.height / 10 - 2);
		int rndx, rndy;
		int * takenx = new int[count];
		int * takeny = new int[count];
		for (int i = 0; i < count; i++)
		{
			bool taken;
			do {
				taken = false;
				rndx = rand() % x;
				rndy = rand() % y;
				for (int j = 0; j <= i; j++)
				{
					if (rndx == takenx[j] && rndy == takeny[j])
					{
						taken = true;
						break;
					}
				}
			} while (taken);

			takenx[i] = rndx;
			takeny[i] = rndy;

			if (powerCount)
			{
				object = new GOConsumable(context, Rect(float(context->world->frame.size.width / 2) - 15 - rndx * 10, float(context->world->frame.size.height / 2) - 15 - rndy * 10, 10, 10));
				object->renderObject = RenderObject::renderObjectFromColor(context, Color(0x00, 0xFF, 0x00, 0x80));
				context->world->addChild(object);
			    powerCount--;
			}
			else
			{
				object = new GOSolid(context, Rect(float(context->world->frame.size.width / 2) - 15 - rndx * 10, float(context->world->frame.size.height / 2) - 15 - rndy * 10, 10, 10));
				object->renderObject = RenderObject::renderObjectFromFile(context, "img/brick.png");
				context->world->addChild(object);
			}
		}

		context->world->addChild(player);

		context->ui = new GOUI(context, {{0.0f, 0.0f}, context->world->camera->originalSize});

        context->ui->deathText = new GOUIText(context, {0, 0, 100, 10});
        context->ui->deathText->setText("You died! Game Over!");
        context->ui->deathText->setFont("fonts/Scratch_.ttf", 28);
        context->ui->deathText->setColor({0xFF, 0x00, 0x00});
        context->ui->deathText->visible = false;
        context->ui->addChild(context->ui->deathText);

        context->ui->winText = new GOUIText(context, {0, 0, 100, 10});
        context->ui->winText->setText("Congratulations! You won!");
        context->ui->winText->setFont("fonts/Scratch_.ttf", 28);
        context->ui->winText->setColor({0x00, 0xFF, 0x00});
        context->ui->winText->visible = false;
        context->ui->addChild(context->ui->winText);

        context->ui->healthBarHolder = new GOUIElement(context, {-context->world->camera->originalSize.width/2+16, -context->world->camera->originalSize.height/2+2.5f, 30, 3});
        context->ui->healthBarHolder->renderObject = RenderObject::renderObjectFromColor(context, {0x00, 0x00, 0x00, 0xFF});
        context->ui->addChild(context->ui->healthBarHolder);

        context->ui->healthBar = new GOUIBar(context, {-context->world->camera->originalSize.width/2+16, -context->world->camera->originalSize.height/2+2.5f, 29, 2});
        context->ui->healthBar->renderObject = RenderObject::renderObjectFromColor(context, {0xFF, 0x00, 0x00, 0xFF});
        context->ui->addChild(context->ui->healthBar);

        context->ui->powerBarHolder = new GOUIElement(context, {context->world->camera->originalSize.width/2-16, -context->world->camera->originalSize.height/2+2.5f, 30, 3});
        context->ui->powerBarHolder->renderObject = RenderObject::renderObjectFromColor(context, {0x00, 0x00, 0x00, 0xFF});
        context->ui->addChild(context->ui->powerBarHolder);

        context->ui->powerBar = new GOUIBar(context, {context->world->camera->originalSize.width/2-16, -context->world->camera->originalSize.height/2+2.5f, 29, 2});
        context->ui->powerBar->renderObject = RenderObject::renderObjectFromColor(context, {0x00, 0xFF, 0x00, 0xFF});
        context->ui->powerBar->setValue(0);
        context->ui->addChild(context->ui->powerBar);

		object = NULL;
		player = NULL;

		while (!context->quit)
		{
			context->world->clean();

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
			context->ui->render();

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
	IMG_Quit();
	TTF_Quit();
}
