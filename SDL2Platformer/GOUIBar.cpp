#include "GOUIBar.h"

GOUIBar::GOUIBar(GameContext * context, Rect frame) : GOUIElement(context, frame)
{
    originalFrame = frame;
}

void GOUIBar::setValue(float value)
{
    if (value > 100) value = 100;
    if (value < 0) value = 0;

    this->value = value;

    frame = Rect({originalFrame.center.x+originalFrame.size.width*((value - 100) / 200), originalFrame.center.y}, {originalFrame.size.width/100*value, originalFrame.size.height});
}
