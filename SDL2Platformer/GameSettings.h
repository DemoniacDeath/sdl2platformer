#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <SDL2/SDL.h>

class GameSettings
{
    public:
        GameSettings();
        const char * name = NULL;
        int windowWidth = 0;
        int windowHeight = 0;
};

#endif // GAMESETTINGS_H
