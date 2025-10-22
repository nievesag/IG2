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
	enum KEYS : OgreBites::Keycode
	{
		SDLK_UP,
		SDLK_DOWN,
		SDLK_LEFT,
		SDLK_RIGHT
	};

	 static const double heroSpeed = 200;

	 static const int mapSize = 100;
	 static const int characterSize = 100;
	 
	 static const float sptInner = 5.0f;
	 static const float sptOuter = 17.0f;
	 static const float sptFalloff = 0.0f;
};


