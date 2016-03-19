#include "GOFrame.h"
#include "GameContext.h"


GOFrame::GOFrame(GameContext * context, Rect frame, int width) : GameObject(context, frame)
{
	this->width = width;
	ceiling = new GOSolid(context, Rect(
		0,
		-frame.size.height / 2 + width / 2,
		frame.size.width, 
		width
		));
	ceiling->renderObject = new RenderObject(context, ceiling, Color(0x00, 0x00, 0x00, 0xFF));
	wallLeft = new GOSolid(context, Rect(
		-frame.size.width / 2 + width / 2,
		0,
		width,
		frame.size.height - width*2 
		));
	wallLeft->renderObject = new RenderObject(context, wallLeft, Color(0x00, 0x00, 0x00, 0xFF));
	wallRight = new GOSolid(context, Rect(
		frame.size.width / 2 - width / 2,
		0,
		width,
		frame.size.height - width*2
		));
	wallRight->renderObject = new RenderObject(context, wallRight, Color(0x00, 0x00, 0x00, 0xFF));
	floor = new GOSolid(context, Rect(
		0,
		frame.size.height / 2 - width / 2, 
		frame.size.width,
		width
		));
	floor->renderObject = new RenderObject(context, floor, Color(0x00, 0x00, 0x00, 0xFF));
	addChild(ceiling);
	addChild(wallLeft);
	addChild(wallRight);
	addChild(floor);

}