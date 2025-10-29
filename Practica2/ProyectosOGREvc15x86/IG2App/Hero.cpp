#include "Hero.h"
#include "Constants.h"
#include "IG2ApplicationContext.h"

Hero::Hero(Vector3 a, SceneNode* b, SceneManager* c, String mesh)
	: Character(a,b,c,mesh)
{
    animationStateRunBase = entity->getAnimationState("RunBase");
    animationStateRunBase->setLoop(true);

    animationStateRunTop = entity->getAnimationState("RunTop");
    animationStateRunTop->setLoop(true);
}

bool Hero::keyPressed(const OgreBites::KeyboardEvent& evt) 
{
    if (active)
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
        {
            animationStateRunBase->setEnabled(true);
            animationStateRunTop->setEnabled(true);

            lastPosibleDirection = keyToDirection(lastPressed);
        }
    }

    return true;
}

void Hero::frameRendered(const Ogre::FrameEvent& evt) 
{
    // solo actualizar si esta activo en la escena
    if (active) 
    {
        Vector3 toMove(currentDirection * evt.timeSinceLastFrame * Constants::heroSpeed);
        lastPos = mNode->getPosition();
        move(toMove);

        if (lastPosibleDirection != Vector3::ZERO) 
        {
            animationStateRunBase->addTime(evt.timeSinceLastFrame);
            animationStateRunTop->addTime(evt.timeSinceLastFrame);
        }
    }
}

void Hero::stopCharacter()
{
    Character::stopCharacter();
    animationStateRunBase->setEnabled(false);
    animationStateRunTop->setEnabled(false);
}

Vector3 Hero::keyToDirection(char x)
{
    Vector3 dir;
    switch (x) 
    {
    case 'u': //up
        dir = Vector3::NEGATIVE_UNIT_Z;
        break;
    case 'd': //
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
