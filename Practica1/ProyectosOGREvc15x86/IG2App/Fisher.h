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
    //Ogre::SceneNode* mFisherNode = nullptr;     // ---------- nodo fisher root
    //Ogre::SceneNode* mPenguinNode = nullptr;    // ---------- pinguino
    Ogre::SceneNode* mPelucaNode = nullptr;     // ------- peluca

    // caña
    SceneNode* mPaloEmpt = nullptr;
    Ogre::SceneNode* mPaloNode = nullptr;       // --- palo caña
    SceneNode* mNudoEmpt = nullptr;
    SceneNode* mHiloEmpt = nullptr;
    Ogre::SceneNode* mHiloNode = nullptr;       // --- hilo caña
    Ogre::SceneNode* mPez1Node = nullptr;       // --- pez 1
    Ogre::SceneNode* mPez2Node = nullptr;       // --- pez 2
    Ogre::SceneNode* mPez3Node = nullptr;       // --- pez 3

    // caña 2
    SceneNode* mPaloEmpt2 = nullptr;
    Ogre::SceneNode* mPaloNode2 = nullptr;       // --- palo caña2
    SceneNode* mNudoEmpt2 = nullptr;
    SceneNode* mHiloEmpt2 = nullptr;
    Ogre::SceneNode* mHiloNode2 = nullptr;       // --- hilo caña2
    Ogre::SceneNode* mPez1Node2 = nullptr;       // --- pez 12
    Ogre::SceneNode* mPez2Node2 = nullptr;       // --- pez 22
    Ogre::SceneNode* mPez3Node2 = nullptr;       // --- pez 32

    // serpiente
    SceneNode* mSerpEmpt = nullptr;
    Ogre::SceneNode* mCuerpoSerpNode = nullptr;    // ------- cuerpo serpiente
    Ogre::SceneNode* mCabezaSerpNode = nullptr;    // ------- cabeza serpiente
    Ogre::SceneNode* mColaSerpNode = nullptr;      // ------- cola serpiente

    float current = 0;
};

