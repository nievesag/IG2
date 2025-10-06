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
#include "Character.h"
#include "Hero.h"

#include "IG2Object.h"
#include "Object.h"

using namespace Ogre;
using namespace std;

class Labyrinth : public OgreBites::InputListener
{
private:
	//static Labyrinth* _labyrinth;

	SceneNode* _labyrinthNode = nullptr;
	SceneManager* _mSM = nullptr;

	int width = 0, height = 0;

	// vector de bloques
	std::vector<std::vector<Object*>> map;

	// --- hero
	Hero* _hero = nullptr;
	std::pair<int, int> _heroPos = { 1,1 }; // posicion del hero en coordenadas de bloques

	void updateHero();

	// Otros
	void DebugMap();

	pair<int, int> vectorToMap(Vector3 pos); // para pasar a coordenadas de bloques

	bool checkMove(pair<int, int> pos, pair<int, int> dir);
	bool checkForward(pair<int, int> pos, pair<int, int> dir, Vector3 realPos);
	bool checkCentered(pair<int, int> pos);

public:
	Labyrinth() = default;

	// para gestion del singleton
	//static Labyrinth* getInstance();

	void setupLabyrinth(SceneManager* mSM, Hero* hero);
	void readFile(string fileName);

	virtual void frameRendered(const Ogre::FrameEvent& evt);

};