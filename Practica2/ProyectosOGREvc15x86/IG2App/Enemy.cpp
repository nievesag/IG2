#include "Enemy.h"

Enemy::Enemy(Vector3 a, SceneNode* b, SceneManager* c, String mesh)
	: Character(a, b, c, mesh)
{
	currentDirection = this->getOrientation();
	lastPosibleDirection = this->getOrientation();
}

void Enemy::frameRendered(const Ogre::FrameEvent& evt)
{
	if (active)
	{
		Vector3 toMove(currentDirection * evt.timeSinceLastFrame * Constants::enemySpeed);
		lastPos = mNode->getPosition();
		move(toMove);
	}
}
