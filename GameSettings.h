#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <SDL2/SDL.h>
#include <string>

class GameSettings {
public:
    GameSettings();

    const std::string name;
    int windowWidth = 0;
    int windowHeight = 0;
};

#endif // GAMESETTINGS_H
