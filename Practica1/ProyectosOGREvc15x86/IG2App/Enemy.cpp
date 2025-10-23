#include "Enemy.h"

Enemy::Enemy(Vector3 a, SceneNode* b, SceneManager* c, String mesh)
	: Character(a, b, c, mesh)
{
	currentDirection = this->getOrientation();
	cout << "CURRENT COJONES:  !!!!!!!!!!!!!!! " << currentDirection << endl;
	lastPosibleDirection = this->getOrientation();
}

void Enemy::frameRendered(const Ogre::FrameEvent& evt)
{
	Vector3 toMove(currentDirection * evt.timeSinceLastFrame * Constants::enemySpeed);
	move(toMove);
}

Vector3 Enemy::getRandomDirection()
{
	// a) Encuentre un cruce con varias opciones de movimiento.
	//		a. En este caso, se calcula aleatoriamente la nueva dirección, salvo el giro de 180º.
	// b) Se bloquee contra un muro enfrente.
	//		a. Si es posible tomar una dirección que no sea un giro de 180º, se calcula de forma aleatoria.
	//		b. Si no queda otra alternativa, el villano gira 180º y continúa avanzando.

	// si se choca con un muro

	return Vector3();
}
