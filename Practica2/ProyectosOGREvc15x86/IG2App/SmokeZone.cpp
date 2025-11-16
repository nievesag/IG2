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
	// si esta activa
	if (active)
	{
		// si aun no ha expirado
		if (!expired)
		{
			current += t;

			if (current > Constants::smokeTime)
			{
				expired = true;
				//sysMecha->setEmitting(false);
				//active = false;
				clearSmoke();
			}
		}
	}
}

void SmokeZone::clearSmoke()
{
	active = false;
	sysHumo->clear();
	sysHumo->setEmitting(false);
}

void SmokeZone::createSmoke()
{
	active = true;
	current = 0;
	expired = false;
	sysHumo->setEmitting(true);
}
