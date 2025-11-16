#pragma once

#include "IG2Object.h"
#include "Object.h"

class SmokeZone : public Object
{
public:
	SmokeZone(Vector3 a, SceneNode* b, SceneManager* c, String name);
	~SmokeZone();

	void update(Real t);

	bool getExpired() const { return expired; }

	void setActive(bool a) { active = a; }
	bool getActive() const { return active; }

	void clearSmoke();
	void createSmoke();

private:
	Ogre::ParticleSystem* sysHumo = nullptr;
	Ogre::SceneNode* nodeHumo = nullptr;

	float current = 0; // para controlar cuando expira
	bool active = false;
	bool expired = false;
};