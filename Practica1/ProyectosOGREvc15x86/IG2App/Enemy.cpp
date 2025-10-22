#include "Enemy.h"

Enemy::Enemy(Vector3 a, SceneNode* b, SceneManager* c, String mesh)
	: Character(a, b, c, mesh)
{
	lastPosibleDirection = this->getOrientation();

	/*
	REQUISITOS DEL ENEMY
	- Rormado por, al menos, tres mallas distintas.
	- Formado por, al menos, diez entidades.
	- Contener, al menos, dos partes m�viles que tengan, al menos, tres entidades cada una que realicen rotaciones.
	- Contener un timer que controle el tiempo que las partes m�viles realizar�n movimientos de rotaci�n en cada sentido.
	*/
}

void Enemy::frameRendered(const Ogre::FrameEvent& evt)
{
	std::cout << "AAAAA ENEMY" << std::endl;
	Vector3 toMove(currentDirection * evt.timeSinceLastFrame * Constants::heroSpeed);
	move(toMove);

	// --- El villano avanzar� en su direcci�n hasta que:
	// a) Encuentre un cruce con varias opciones de movimiento.
	//		a. En este caso, se calcula aleatoriamente la nueva direcci�n, salvo el giro de 180�.
	// b) Se bloquee contra un muro enfrente.
	//		a. Si es posible tomar una direcci�n que no sea un giro de 180�, se calcula de forma aleatoria.
	//		b. Si no queda otra alternativa, el villano gira 180� y contin�a avanzando.

	// Vector3 toMove(currentDirection * evt.timeSinceLastFrame * Constants::heroSpeed);
	// move(toMove);
}

Vector3 Enemy::getRandomDirection()
{
	// a) Encuentre un cruce con varias opciones de movimiento.
	//		a. En este caso, se calcula aleatoriamente la nueva direcci�n, salvo el giro de 180�.
	// b) Se bloquee contra un muro enfrente.
	//		a. Si es posible tomar una direcci�n que no sea un giro de 180�, se calcula de forma aleatoria.
	//		b. Si no queda otra alternativa, el villano gira 180� y contin�a avanzando.

	// si se choca con un muro

	return Vector3();
}
