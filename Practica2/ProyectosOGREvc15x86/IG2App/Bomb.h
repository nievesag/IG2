#pragma once

#include "IG2Object.h"
#include "Object.h"

class Bomb : public Object
{
public:
	Bomb(Vector3 a, SceneNode* b, SceneManager* c);
	~Bomb();

	virtual void frameRendered(const Ogre::FrameEvent& evt);

	bool getExploded() { return exploded; }

private:
	Ogre::SceneNode* mCuerpoNode = nullptr; // cuerpo
	Ogre::SceneNode* mMechaNode = nullptr;  // mecha

	float current = 0; // para controlar cuando explota

	bool exploded = false;
};

