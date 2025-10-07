#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreMeshManager.h>
#include "IG2Object.h"

class Character : public IG2Object
{
public:
	Character(Vector3 a, SceneNode* b, SceneManager* c, String mesh) : IG2Object(a, b, c, mesh) 
	{
		currentDirection = Vector3(0, 0, 0);
	};
	Vector3 getLastPosibleDirection() { return lastPosibleDirection; }
	Vector3 getCurrentDirection() { return currentDirection; }

	void moveCharacter();
	void stopCharacter();
	Quaternion quaternionRotateCharacter();
	
protected:
	Vector3 lastPosibleDirection; // ultima "posible" direccion
	Vector3 currentDirection; // hacia donde mira
};