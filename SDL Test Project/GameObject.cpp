#include "GameObject.h"
#include "GameContext.h"

GameObject::GameObject(GameContext * context)
{
	this->context = context;
}

GameObject::GameObject(GameContext * context, SDL_Rect rect)
{
	this->context = context;
	this->rect = rect;
}

void GameObject::handleEvent(SDL_Event * e)
{
	if (children.size())
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->handleEvent(e);
		}
	}
}

void GameObject::handleKeyboard(const Uint8 * state)
{
	if (children.size())
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->handleKeyboard(state);
		}
	}
}

void GameObject::processPhysics()
{
	if (physics)
		physics->change();

	if (children.size())
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->processPhysics();
		}
	}
}

void GameObject::detectCollisions()
{
	std::vector<GameObject *> * allColliders = new std::vector<GameObject *>;
	detectCollisions(allColliders);
	for (int i = 0; i < allColliders->size() - 1; i++)
	{
		for (int j = i + 1; j < allColliders->size(); j++)
		{
			(*allColliders)[i]->physics->detectCollision((*allColliders)[j]->physics);

		}
	}
}

void GameObject::detectCollisions(std::vector<GameObject *> * allColliders)
{
	if (physics)
		allColliders->push_back(this);
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->detectCollisions(allColliders);
	}
}

void GameObject::handleCollision(GameObject * collider, Vector2D collisionArea)
{
	
}

void GameObject::render()
{
	if (renderObject)
	{
		SDL_RenderCopy(context->renderer, renderObject->texture, NULL, &rect);
	}
	if (children.size())
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->render();
		}
	}

}

void GameObject::free()
{
	if (renderObject)
		renderObject->free();

	if (children.size())
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->free();
		}
		children.clear();
	}

	context = NULL;
}