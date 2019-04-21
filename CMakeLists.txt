cmake_minimum_required(VERSION 3.14)
project(sdl2platformer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories(SDL2Platformer)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(sdl2platformer
        SDL2Platformer/Animation.cpp
        SDL2Platformer/Animation.h
        SDL2Platformer/Collision.cpp
        SDL2Platformer/Collision.h
        SDL2Platformer/Color.cpp
        SDL2Platformer/Color.h
        SDL2Platformer/Game.cpp
        SDL2Platformer/Game.h
        SDL2Platformer/GameContext.cpp
        SDL2Platformer/GameContext.h
        SDL2Platformer/GameObject.cpp
        SDL2Platformer/GameObject.h
        SDL2Platformer/GameSettings.cpp
        SDL2Platformer/GameSettings.h
        SDL2Platformer/GOCamera.cpp
        SDL2Platformer/GOCamera.h
        SDL2Platformer/GOConsumable.cpp
        SDL2Platformer/GOConsumable.h
        SDL2Platformer/GOFrame.cpp
        SDL2Platformer/GOFrame.h
        SDL2Platformer/GOPlayer.cpp
        SDL2Platformer/GOPlayer.h
        SDL2Platformer/GOSolid.cpp
        SDL2Platformer/GOSolid.h
        SDL2Platformer/GOUIBar.cpp
        SDL2Platformer/GOUIBar.h
        SDL2Platformer/GOUIText.cpp
        SDL2Platformer/GOUIText.h
        SDL2Platformer/GOWorld.cpp
        SDL2Platformer/GOWorld.h
        SDL2Platformer/main.cpp
        SDL2Platformer/PhysicsState.cpp
        SDL2Platformer/PhysicsState.h
        SDL2Platformer/Rect.cpp
        SDL2Platformer/Rect.h
        SDL2Platformer/RenderObject.cpp
        SDL2Platformer/RenderObject.h
        SDL2Platformer/Size.cpp
        SDL2Platformer/Size.h
        SDL2Platformer/Vector2D.cpp
        SDL2Platformer/Vector2D.h)

target_link_libraries(sdl2platformer ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2TTF_LIBRARY})

FILE(COPY
        SDL2Platformer/img/brick.png
        SDL2Platformer/img/crouch.png
        SDL2Platformer/img/idle.png
        SDL2Platformer/img/jump.png
        SDL2Platformer/img/move.png
        DESTINATION "${CMAKE_BINARY_DIR}/img")
FILE(COPY SDL2Platformer/fonts/Scratch_.ttf DESTINATION "${CMAKE_BINARY_DIR}/fonts")