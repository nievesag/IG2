#include "EstrellaChip.h"
#include "DataSizes.h"
#include "Rocket.h"

EstrellaChip::EstrellaChip(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	spaceShip = new SpaceShip({0,0,0}, node, sceneMng);
	Real yPos = (DataSizes::SPACESHIP_BODY_SIZE.y / 2) + (DataSizes::ENGINE_BASE_SIZE.y / 2);
	engine = new Engine( {0,-yPos,0},node,sceneMng);

	Real angleStep = (2 * Math::PI) / DataSizes::NUM_ROCKETS;
	for (int i = 0; i < DataSizes::NUM_ROCKETS; ++i)
	{
		Real angle = i * angleStep;

		Real x = (DataSizes::ENGINE_BASE_SIZE.x / 2) * cos(angle);
		Real z = (DataSizes::ENGINE_BASE_SIZE.x / 2) * sin(angle);
		Vector3 rocketPos = {x, -DataSizes::ENGINE_BASE_SIZE.y / 2, z };

		Rocket* r = new Rocket(rocketPos, node, sceneMng);
	}
}
