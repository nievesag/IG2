#include "Character.h"

void Character::moveCharacter() 
{
	currentDirection = lastPosibleDirection;
}

void Character::stopCharacter()
{
	currentDirection = Vector3(0, 0, 0);
}

Quaternion Character::quaternionRotateCharacter()
{
	return this->getOrientation().getRotationTo(lastPosibleDirection);
}

Radian Character::yawDirection()
{
	return quaternionRotateCharacter().getYaw();
}

bool Character::checkCharacterCollision(const AxisAlignedBox& b)
{
	bool choque = this->getAABB().intersects(b);
	return choque;
}
