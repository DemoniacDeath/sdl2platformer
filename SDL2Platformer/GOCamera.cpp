#include "GOCamera.h"


GOCamera::GOCamera(GameContext *context, Rect frame) : GameObject(context, frame) {
    originalSize = frame.size;
}

void GOCamera::handleKeyboard(const Uint8 *state) {
    if (state[SDL_SCANCODE_Z]) {
        frame.size.width = originalSize.width * 2;
        frame.size.height = originalSize.height * 2;
    } else {
        frame.size.width = originalSize.width;
        frame.size.height = originalSize.height;
    }
}
