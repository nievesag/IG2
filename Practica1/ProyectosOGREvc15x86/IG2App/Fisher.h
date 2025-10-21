#pragma once

#include "Enemy.h"

class Fisher : public Enemy
{
public:
	Fisher(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);
	~Fisher();

	virtual void frameRendered(const Ogre::FrameEvent& evt);

private:
    // pinguino
    Ogre::SceneNode* mFisherNode = nullptr;     // ---------- nodo fisher root
    Ogre::SceneNode* mPenguinNode = nullptr;    // ---------- pinguino
    Ogre::SceneNode* mPelucaNode = nullptr;     // ------- peluca

    // caña
    Ogre::SceneNode* mPaloNode = nullptr;       // --- palo caña
    Ogre::SceneNode* mHiloNode = nullptr;       // --- hilo caña
    Ogre::SceneNode* mPez1Node = nullptr;       // --- pez 1
    Ogre::SceneNode* mPez2Node = nullptr;       // --- pez 2
    Ogre::SceneNode* mPez3Node = nullptr;       // --- pez 3

    // serpiente
    Ogre::SceneNode* mCuerpoSerpienteNode = nullptr;    // ------- cuerpo serpiente
    Ogre::SceneNode* mCabezaSerpienteNode = nullptr;    // ------- cuerpo serpiente
    Ogre::SceneNode* mColaSerpienteNode = nullptr;      // ------- cuerpo serpiente
};

