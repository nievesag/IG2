#include "Bomb.h"
#include "Constants.h"

Bomb::Bomb(Vector3 a, SceneNode* b, SceneManager* c)
	: Object(a, b, c, true)
{

}

Bomb::~Bomb()
{

}

void Bomb::frameRendered(const Ogre::FrameEvent& evt)
{
	// si aun no ha explotado
	if (!exploded) 
	{
		current += evt.timeSinceLastEvent;

		if (current > Constants::bombTick)
		{
			exploded = true;
		}
	}
}
