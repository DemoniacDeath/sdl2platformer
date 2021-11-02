#include <ctime>
#include <cstdlib>
#include <memory>

#include "Game.h"
#include "RenderObject.h"
#include "GOPlayer.h"
#include "GOFrame.h"
#include "GOConsumable.h"

Game::Game() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL could not initialize! SDL Error: " + std::string(SDL_GetError()));
    }
    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        throw std::runtime_error("Warning: Linear texture filtering not enabled!");
    }

    int imgFlags = IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        throw std::runtime_error("SDL_image could not be initialized! SDL_image Error: " + std::string(IMG_GetError()));
    }

    if (TTF_Init() == -1) {
        throw std::runtime_error("SDL_ttf could not initialize! SDL_ttf Error: " + std::string(TTF_GetError()));
    }

    context = new GameContext(new GameSettings());
}

void Game::run() {
    context->world = new GOWorld(*context, Rect(0, 0, float(context->settings->windowWidth / 2.),
                                                float(context->settings->windowHeight / 2.)));
    context->world->camera->originalSize.width /= 2;
    context->world->camera->originalSize.height /= 2;

    auto player = GOPlayer(*context, Rect(0, 20, 10, 20));

    player.idleAnimation = Animation::animationWithSingleRenderObject(
            RenderObject::renderObjectFromFile(context->renderer, "img/idle.png"));
    player.moveAnimation = Animation::animationWithSpeedAndTextureFile(80, context->renderer, "img/move.png", 40,
                                                                       80, 6);
    player.jumpAnimation = Animation::animationWithSingleRenderObject(
            RenderObject::renderObjectFromFile(context->renderer, "img/jump.png"));
    player.crouchAnimation = Animation::animationWithSingleRenderObject(
            RenderObject::renderObjectFromFile(context->renderer, "img/crouch.png"));
    player.crouchMoveAnimation = Animation::animationWithSingleRenderObject(
            RenderObject::renderObjectFromFile(context->renderer, "img/crouch.png"));

    player.speed = 1.3f;
    player.jumpSpeed = 2.5f;
    player.physics->gravityForce = 0.1f;

    player.addChild(context->world->camera.get());

    auto frame = std::make_unique<GOFrame>(*context, Rect(0, 0, context->world->frame.size.width,
                                                          context->world->frame.size.height), 10);
    frame->addChildren();
    context->world->addChild(frame.get());

    context->world->addChild(&player);

    GameObject *object;
    srand((unsigned int) time(nullptr));

    {
        const int count = 200;
        int powerCount = 100;
        int x = int(context->world->frame.size.width / 10 - 2);
        int y = int(context->world->frame.size.height / 10 - 2);
        int randomX, randomY;
        int takenXs[count];
        int takenYs[count];
        context->world->blocks.reserve(count);
        auto blockColor = RenderObject::renderObjectFromColor(context->renderer, Color(0x00, 0xFF, 0x00, 0x80));
        auto blockBrick = RenderObject::renderObjectFromFile(context->renderer, "img/brick.png");
        for (int i = 0; i < count; ++i) {
            bool taken;
            do {
                taken = false;
                randomX = rand() % x;
                randomY = rand() % y;
                for (int j = 0; j <= i; ++j) {
                    if (randomX == takenXs[j] && randomY == takenYs[j]) {
                        taken = true;
                        break;
                    }
                }
            } while (taken);

            takenXs[i] = randomX;
            takenYs[i] = randomY;

            if (powerCount) {
                object = new GOConsumable(*context,
                                          Rect(float(context->world->frame.size.width / 2) - 15 - randomX * 10,
                                               float(context->world->frame.size.height / 2) - 15 -
                                               randomY * 10, 10, 10));
                object->renderObject = blockColor;
                --powerCount;
            } else {
                object = new GOSolid(*context, Rect(float(context->world->frame.size.width / 2) - 15 - randomX * 10,
                                                    float(context->world->frame.size.height / 2) - 15 - randomY * 10,
                                                    10,
                                                    10));
                object->renderObject = blockBrick;
            }
            context->world->addChild(object);
            context->world->blocks.push_back(object);
        }
    }

    context->ui = new GameObject(*context, {{0.0f, 0.0f}, context->world->camera->originalSize});

    {
        auto deathText = new GOUIText(*context, {0, 0, 100, 10});
        deathText->setText("You died! Game Over!");
        deathText->setFont("fonts/Scratch_.ttf", 28);
        deathText->setColor({0xFF, 0x00, 0x00});
        deathText->visible = false;
        deathText->generate();

        player.deathText = deathText;
    }
    context->ui->addChild(player.deathText);

    {
        auto winText = new GOUIText(*context, {0, 0, 100, 10});
        winText->setText("Congratulations! You won!");
        winText->setFont("fonts/Scratch_.ttf", 28);
        winText->setColor({0x00, 0xFF, 0x00});
        winText->visible = false;
        winText->generate();

        player.winText = winText;
    }
    context->ui->addChild(player.winText);

    {
        auto healthBarHolder = new GameObject(*context, {-context->world->camera->originalSize.width / 2 + 16,
                                                         -context->world->camera->originalSize.height / 2 +
                                                         2.5f, 30, 3});
        healthBarHolder->renderObject = RenderObject::renderObjectFromColor(context->renderer,
                                                                            {0x00, 0x00, 0x00, 0xFF});

        player.healthBar = new GOUIBar(*context, {0.0f, 0.0f, 29, 2});
        player.healthBar->renderObject = RenderObject::renderObjectFromColor(context->renderer,
                                                                             {0xFF, 0x00, 0x00, 0xFF});

        healthBarHolder->addChild(player.healthBar);
        context->ui->addChild(healthBarHolder);
        context->world->healthBar = std::unique_ptr<GameObject>(healthBarHolder);
    }

    {
        auto powerBarHolder = new GameObject(*context, {context->world->camera->originalSize.width / 2 - 16,
                                                        -context->world->camera->originalSize.height / 2 + 2.5f,
                                                        30, 3});
        powerBarHolder->renderObject = RenderObject::renderObjectFromColor(context->renderer,
                                                                           {0x00, 0x00, 0x00, 0xFF});

        player.powerBar = new GOUIBar(*context, {0.0f, 0.0f, 29, 2});
        player.powerBar->renderObject = RenderObject::renderObjectFromColor(context->renderer,
                                                                            {0x00, 0xFF, 0x00, 0xFF});
        player.powerBar->setValue(0);

        powerBarHolder->addChild(player.powerBar);
        context->ui->addChild(powerBarHolder);
        context->world->powerBar = std::unique_ptr<GameObject>(powerBarHolder);
    }

    SDL_Event e;
    while (!context->quit) {
        SDL_Delay(10);
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    context->quit = true;
                    break;
            }
            context->world->handleEvent(&e);
        }

        context->world->handleKeyboard(SDL_GetKeyboardState(nullptr));
        context->world->clean();
        context->world->processPhysics();
        context->world->detectCollisions();
        context->world->animate();

        //Clear screen
        SDL_SetRenderDrawColor(context->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(context->renderer);

        context->world->renderWorld();
        context->ui->render({0.0f, 0.0f}, {0.0f, 0.0f}, context->world->camera->originalSize);

        //Update screen
        SDL_RenderPresent(context->renderer);
    }
}

Game::~Game() {
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    delete context;
}
