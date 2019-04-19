#include "GOUIBar.h"

GOUIBar::GOUIBar(GameContext * context, Rect frame) : GOUIElement(context, frame)
{
    originalFrame = frame;
}

void GOUIBar::setValue(float newValue)
{
    if (newValue > 100) newValue = 100;
    if (newValue < 0) newValue = 0;

    this->value = newValue;

    frame = Rect({originalFrame.center.x+originalFrame.size.width*((newValue - 100) / 200), originalFrame.center.y}, {originalFrame.size.width/100*newValue, originalFrame.size.height});
}
