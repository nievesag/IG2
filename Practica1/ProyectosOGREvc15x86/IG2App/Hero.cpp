#include "Hero.h"
#include "Constants.h"
#include "IG2ApplicationContext.h"

Hero::Hero(Vector3 a, SceneNode* b, SceneManager* c, String mesh)
	: Character(a,b,c,mesh)
{
    
}

bool Hero::keyPressed(const OgreBites::KeyboardEvent& evt) 
{
    if (evt.keysym.sym == SDLK_UP) 
    {
        lastPressed = 'u';
    }
    else if (evt.keysym.sym == SDLK_DOWN) 
    {
        lastPressed = 'd';
    }
    else if (evt.keysym.sym == SDLK_LEFT) 
    {
        lastPressed = 'l';
    }
    else if (evt.keysym.sym == SDLK_RIGHT) 
    {
        lastPressed = 'r';
    }

    if (lastPressed == 'u' || lastPressed == 'd' || lastPressed == 'l' || lastPressed == 'r') 
    { lastPosibleDirection = keyToDirection(lastPressed); }

    //std::cout << lastPosibleDirection.x << "\n";

    return true;
}

void Hero::frameRendered(const Ogre::FrameEvent& evt) 
{
    Vector3 toMove(currentDirection * evt.timeSinceLastFrame * Constants::heroSpeed);
    move(toMove);
}

Vector3 Hero::keyToDirection(char x)
{
    Vector3 dir;
    switch (x) 
    {
    case 'u':
        dir = Vector3::NEGATIVE_UNIT_Z;
        break;
    case 'd':
        dir = Vector3::UNIT_Z;
        break;
    case 'l':
        dir = Vector3::NEGATIVE_UNIT_X;
        break;
    case 'r':
        dir = Vector3::UNIT_X;
        break;
    }

    return dir;
}
