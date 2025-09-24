#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreMeshManager.h>
#include <SDL_keycode.h>
#include <iostream>
#include <vector>

#include "IG2Object.h"

using namespace Ogre;
using namespace std;

class Labyrinth
{
private:
	//static Labyrinth* _labyrinth;

	SceneNode* _labyrinthNode = nullptr;
	SceneManager* _mSM = nullptr;

	int width = 0, height = 0;

	// vector de bloques
	std::vector<std::vector<IG2Object*>> map;

	// posicion del hero


	//Otros
	void DebugMap();

public:
	Labyrinth() = default;

	// para gestion del singleton
	//static Labyrinth* getInstance();

	void setupLabyrinth(SceneManager* mSM);
	void readFile(string fileName);
};