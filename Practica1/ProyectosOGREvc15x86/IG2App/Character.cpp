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
