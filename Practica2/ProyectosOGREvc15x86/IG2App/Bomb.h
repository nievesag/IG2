#pragma once

#include "IG2Object.h"
#include "Object.h"

class Bomb : public Object
{
public:
	Bomb(Vector3 a, SceneNode* b, SceneManager* c, String name);
	~Bomb();

	bool getExploded() { return exploded; }

	void update(Real t);

	void setActive(bool a) { active = a; }
	bool getActive() const { return active; }

	void clearBomb();
	void createBomb();

private:
	Ogre::SceneNode* mCuerpoNode = nullptr; // cuerpo
	Ogre::Entity* bomba = nullptr;
	Ogre::SceneNode* mMechaNode = nullptr;  // mecha
	Ogre::Entity* mecha = nullptr;

	Ogre::ParticleSystem* sysMecha = nullptr;
	Ogre::SceneNode* sysMechaNode = nullptr;

	Ogre::SceneNode* nodeMecha = nullptr;
	Ogre::ParticleSystem* sysHumo = nullptr; // para el humo propio no el que se propaga
	Ogre::SceneNode* nodeHumo = nullptr;

	float current = 0; // para controlar cuando explota

	bool exploded = false;

	bool active = false;

	bool increasing = true;
	bool decreasing = false;
};