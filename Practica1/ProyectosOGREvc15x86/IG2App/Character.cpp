#include "Character.h"

void Character::moveCharacter() 
{
	currentDirection = lastPosibleDirection;
}

void Character::stopCharacter()
{
	//std::cout << "stop\n";
	currentDirection = Vector3(0, 0, 0);
}

Quaternion Character::quaternionRotateCharacter()
{
	std::cout << "act: " << this->getOrientation() << endl;
	std::cout << "sig: " << lastPosibleDirection << endl;

	return this->getOrientation().getRotationTo(currentDirection);
}