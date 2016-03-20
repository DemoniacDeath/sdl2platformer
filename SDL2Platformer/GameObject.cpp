#include "GameObject.h"
#include "GameContext.h"

GameObject::GameObject(GameContext * context)
{
	this->context = context;
}

GameObject::GameObject(GameContext * context, Rect frame)
{
	this->context = context;
	this->frame = frame;
}

void GameObject::handleEvent(SDL_Event * e)
{
	if (children.size())
	{
		for (Uint32 i = 0, size = children.size(); i < size; i++)
		{
			children[i]->handleEvent(e);
		}
	}
}

void GameObject::handleKeyboard(const Uint8 * state)
{
	if (children.size())
	{
		for (Uint32 i = 0, size = children.size(); i < size; i++)
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
		for (Uint32 i = 0, size = children.size(); i < size; i++)
		{
			children[i]->processPhysics();
		}
	}
}

void GameObject::detectCollisions()
{
	std::vector<GameObject *> * allColliders = new std::vector<GameObject *>;
	detectCollisions(allColliders);
	for (Uint32 i = 0, size = allColliders->size(); i < size; i++)
	{
		for (Uint32 j = i + 1, size = allColliders->size(); j < size; j++)
		{
			(*allColliders)[i]->physics->detectCollision((*allColliders)[j]->physics);

		}
	}
}

void GameObject::detectCollisions(std::vector<GameObject *> * allColliders)
{
	if (physics)
		allColliders->push_back(this);
	for (Uint32 i = 0, size = children.size(); i < size; i++)
	{
		children[i]->detectCollisions(allColliders);
	}
}

void GameObject::handleCollision(GameObject * collider, Vector2D collisionArea)
{
	
}

void GameObject::handleExitCollision(GameObject * collider)
{

}

void GameObject::animate()
{
	if (animation)
	{
		this->renderObject = animation->animate();
	}
	for (Uint32 i = 0, size = children.size(); i < size; i++)
	{
		children[i]->animate();
	}
}

void GameObject::render(Vector2D localBasis, Vector2D cameraPosition, Size cameraSize)
{
	if (renderObject)
	{
		Vector2D globalPosition = frame.center;
		globalPosition += localBasis;
		SDL_Rect rect;

		Vector2D cameraTransform = Vector2D(-cameraSize.width / 2, -cameraSize.height / 2);
		Vector2D cameraTransformedPosition = cameraPosition + cameraTransform;
		Vector2D frameTransform = Vector2D(-frame.size.width / 2, -frame.size.height / 2);
		Vector2D frameTransformedPosition = globalPosition + frameTransform;
		Vector2D renderPosition = frameTransformedPosition - cameraTransformedPosition;
		rect.x = (int)roundf(context->settings->windowWidth * (renderPosition.x / cameraSize.width));
		rect.y = (int)roundf(context->settings->windowHeight * (renderPosition.y / cameraSize.height));
		rect.w = (int)roundf(context->settings->windowWidth * (frame.size.width / cameraSize.width));
		rect.h = (int)roundf(context->settings->windowHeight * (frame.size.height / cameraSize.height));
		SDL_RenderCopy(context->renderer, renderObject->texture, NULL, &rect);
	}
	if (children.size())
	{
		for (Uint32 i = 0, size = children.size(); i < size; i++)
		{
			children[i]->render(localBasis + frame.center, cameraPosition, cameraSize);
		}
	}
}

void GameObject::addChild(GameObject * child)
{
	children.push_back(child);
	child->parent = this;
}

void GameObject::free()
{
	if (!animation && renderObject)
	{
		renderObject->free();
		delete renderObject;
		renderObject = NULL;
	}

	if (animation)
	{
		animation->free();
		delete animation;
		animation = NULL;
	}

	if (children.size())
	{
		for (Uint32 i = 0, size = children.size(); i < size; i++)
		{
			children[i]->free();
		}
		children.clear();
	}
	
	context = NULL;
}

Vector2D GameObject::globalPosition()
{
	if (parent)
	{
		return frame.center + parent->globalPosition();
	}
	else
	{
		return frame.center;
	}
}