#pragma once
#include "GameObject.h"
class GOCamera :
	public GameObject
{
public:
	GOCamera(GameContext *, Rect);
	void handleKeyboard(const Uint8 *);

	Size originalSize;
};

