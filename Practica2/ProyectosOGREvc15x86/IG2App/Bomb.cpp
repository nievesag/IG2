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
	cout << "hola" << endl;

	// si aun no ha explotado
	if (!exploded) 
	{
		current += evt.timeSinceLastEvent;

		if (current > Constants::bombTick)
		{
			cout << "explota" << endl;
			exploded = true;
		}
	}
}
