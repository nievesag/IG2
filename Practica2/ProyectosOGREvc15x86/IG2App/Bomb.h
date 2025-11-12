#pragma once

#include "IG2Object.h"
#include "Object.h"

class Bomb : public Object
{
public:
	Bomb(Vector3 a, SceneNode* b, SceneManager* c);
	~Bomb();

	bool getExploded() { return exploded; }

	void update(Real t);

private:
	Ogre::SceneNode* mCuerpoNode = nullptr; // cuerpo
	Ogre::SceneNode* mMechaNode = nullptr;  // mecha

	Ogre::ParticleSystem* sysMecha = nullptr;
	Ogre::SceneNode* nodeMecha = nullptr;
	Ogre::ParticleSystem* sysHumo = nullptr; // para el humo propio no el que se propaga
	Ogre::SceneNode* nodeHumo = nullptr;

	float current = 0; // para controlar cuando explota

	bool exploded = false;

	void clearBomb();
};