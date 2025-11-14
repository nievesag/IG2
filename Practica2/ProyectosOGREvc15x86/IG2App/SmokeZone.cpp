#include "SmokeZone.h"

#include <OgreParticleSystem.h>

#include "Constants.h"

SmokeZone::SmokeZone(Vector3 a, SceneNode* b, SceneManager* c, String name)
	: Object(a, b, c, true)
{
	// sistemas de particulas
	sysHumo = mSM->createParticleSystem(name, "Examples/Smoke");
	b->attachObject(sysHumo);
	sysHumo->setEmitting(false);
}

SmokeZone::~SmokeZone()
{

}

void SmokeZone::update(Real t)
{

}

void SmokeZone::clearSmoke()
{
	active = false;
	sysHumo->clear();
}
