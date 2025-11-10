#pragma once

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>

namespace Constants
{
	// teclas
	enum KEYS : OgreBites::Keycode
	{
		SDLK_UP,
		SDLK_DOWN,
		SDLK_LEFT,
		SDLK_RIGHT
	};

	// velocidad objetos
	static const double heroSpeed = 200;
	static const double enemySpeed = 150;

	// objects size
	static const int mapSize = 100;
	static const int characterSize = 100;
	 
	// spot light
	static const float sptInner = 5.0f;
	static const float sptOuter = 17.0f;
	static const float sptFalloff = 0.0f;

	// bombas
	static const int maxBombs = 5;	// bombas maximas que se pueden colocar
	static const int bombReach = 3;	// alcance de las bombas
	static const int bombTick = 20;	// tiempo que tarda en explotar

	//Animation
	static const Ogre::Vector3 animPos(0, -20, -200);
	static const Ogre::Real moveStep = 4;
	static const Ogre::Real turnStep = 2;
	static const Ogre::Real danceStep = 5;
	static const Ogre::Real loopTime = moveStep * 2 + turnStep * 3 + danceStep;
}


