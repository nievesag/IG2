#include "EstrellaChip.h"
#include "DataSizes.h"
#include "Rocket.h"

EstrellaChip::EstrellaChip(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	spaceShip = new SpaceShip({0,0,0}, node, mSM);
	engine = new Engine( {0,20,0},node,sceneMng);

	rocketsRack = node->createChildSceneNode();

	Real angleStep = (2 * Math::PI) / DataSizes::NUM_ROCKETS;
	for (int i = 0; i < DataSizes::NUM_ROCKETS; ++i)
	{
		Real angle = i * angleStep;

		Real x = (DataSizes::ENGINE_BASE_SIZE.x / 2) * cos(angle);
		Real z = (DataSizes::ENGINE_BASE_SIZE.z / 2) * sin(angle);
		Vector3 rocketPos = {x, -DataSizes::ENGINE_BASE_SIZE.y / 2, z };

		Rocket* r = new Rocket(rocketPos, rocketsRack, sceneMng, i);

		std::cout << r->getAABB().getSize() << std::endl;
	}
}

void EstrellaChip::frameRendered(const Ogre::FrameEvent& evt)
{
	if (active)
	{
		count += evt.timeSinceLastFrame;

		if (count >= DataSizes::TIME_ENGINE_START)
		{
			rocketsRack->yaw(Ogre::Angle(DataSizes::SHIP_ROTATION * evt.timeSinceLastFrame));
		}
	}
}

void EstrellaChip::Takeoff()
{
	engine->setEngine(true);
	active = true;
}