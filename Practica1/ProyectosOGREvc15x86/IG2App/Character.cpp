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
	std::cout << "act: " << this->getOrientation() << endl;
	std::cout << "sig: " << lastPosibleDirection << endl;

	return this->getOrientation().getRotationTo(lastPosibleDirection);
}