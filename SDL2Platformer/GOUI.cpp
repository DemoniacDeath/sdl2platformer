#include "GOUI.h"
#include "GameContext.h"

GOUI::GOUI(GameContext * context, Rect frame) : GOUIElement(context, frame) {}

void GOUI::render()
{
	GameObject::render(frame.center, {0.0f,0.0f}, context->world->camera->originalSize);
}
