#include "GOFrame.h"
#include "GameContext.h"

GOFrame::GOFrame(const GameContext& context, Rect frame, int width) : GameObject(context, frame) {
    this->width = width;
    ceiling = new GOSolid(context, Rect(
            0,
            -frame.size.height / 2 + float(width) / 2,
            frame.size.width,
            float(width)
    ));
    ceiling->renderObject = RenderObject::renderObjectFromColor(context.renderer, Color(0x00, 0x00, 0x00, 0xFF));
    wallLeft = new GOSolid(context, Rect(
            -frame.size.width / 2 + float(width) / 2,
            0,
            float(width),
            frame.size.height - float(width) * 2
    ));
    wallLeft->renderObject = RenderObject::renderObjectFromColor(context.renderer, Color(0x00, 0x00, 0x00, 0xFF));
    wallRight = new GOSolid(context, Rect(
            frame.size.width / 2 - float(width) / 2,
            0,
            float(width),
            frame.size.height - float(width) * 2
    ));
    wallRight->renderObject = RenderObject::renderObjectFromColor(context.renderer, Color(0x00, 0x00, 0x00, 0xFF));
    floor = new GOSolid(context, Rect(
            0,
            frame.size.height / 2 - float(width) / 2,
            frame.size.width,
            float(width)
    ));
    floor->renderObject = RenderObject::renderObjectFromColor(context.renderer, Color(0x00, 0x00, 0x00, 0xFF));
}

void GOFrame::addChildren()
{
    addChild(ceiling);
    addChild(wallLeft);
    addChild(wallRight);
    addChild(floor);
}

GOFrame::~GOFrame()
{
    for (auto frame : children) {
        delete frame;
    }
}
