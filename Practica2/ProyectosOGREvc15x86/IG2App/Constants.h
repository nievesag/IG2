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

	// direcciones
	static const std::array<Ogre::Vector3, 4> DirectionsArray = {
		Ogre::Vector3::NEGATIVE_UNIT_Z,	// ARRIBA
		Ogre::Vector3::UNIT_Z,			// ABAJO
		Ogre::Vector3::NEGATIVE_UNIT_X,	// IZQ
		Ogre::Vector3::UNIT_X				// DER
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
	static const int maxBombs = 3;	// bombas maximas que se pueden colocar de manera simultanea
	static const int bombReach = 4;	// alcance de las bombas
	static const float bombTick = 0.3f;	// tiempo que tarda en explotar
	static const float smokeTime = 0.2f;	// tiempo que tarda en expirar
	static const int maxSmokes = ((4 * bombReach) * maxBombs); // humos maximos en partida
	static const Ogre::Vector3 bigBombSize = {100,100,100};
	static const Ogre::Vector3 smallBombSize = {100,100,100};

	//Animation
	static const Ogre::Vector3 animPos(0, -20, -200);
	static const Ogre::Real moveStep = 4;
	static const Ogre::Real turnStep = 2;
	static const Ogre::Real danceStep = 5;
	static const Ogre::Real loopTime = moveStep * 2 + turnStep * 3 + danceStep;
}


