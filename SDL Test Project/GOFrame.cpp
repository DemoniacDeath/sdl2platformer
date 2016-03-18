#include "GOFrame.h"
#include "GameContext.h"


GOFrame::GOFrame(GameContext * context, SDL_Rect rect, int width) :GameObject(context, rect)
{
	this->width = width;
	floor = new GOSolid(context, { 0, rect.h - width,rect.w, width });
	floor->renderObject = new RenderObject(context, floor->rect, Color(0x00, 0x00, 0x00, 0xFF));
	wallLeft = new GOSolid(context, { 0, width, width, rect.h - width*2 });
	wallLeft->renderObject = new RenderObject(context, wallLeft->rect, Color(0x00, 0x00, 0x00, 0xFF));
	wallRight = new GOSolid(context, { rect.w - width, width, width, rect.h - width*2 });
	wallRight->renderObject = new RenderObject(context, wallRight->rect, Color(0x00, 0x00, 0x00, 0xFF));
	ceiling = new GOSolid(context, { 0, 0, rect.w, width });
	ceiling->renderObject = new RenderObject(context, ceiling->rect, Color(0x00, 0x00, 0x00, 0xFF));
	children.push_back(floor);
	children.push_back(wallLeft);
	children.push_back(wallRight);
	children.push_back(ceiling);

}