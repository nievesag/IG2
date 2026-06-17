#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>

#include "EstrellaChip.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener{

public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()
    virtual ~IG2App() { };                                    // delete -> shutdown()
 
protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    
    bool checkCollision(const AxisAlignedBox& a, const AxisAlignedBox& b);
    Vector3 returnCollision(const AxisAlignedBox& a, const AxisAlignedBox& b);
      
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;
    
    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;
    
    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    SceneNode* estrellaChipNode = nullptr;
    EstrellaChip* estrella = nullptr;

    Ogre::SceneNode* bolaFather = nullptr;

    Ogre::SceneNode* nodeBola = nullptr;

    AnimationState* bolaAnim = nullptr;

    SceneNode* airplaneNode = nullptr;
    SceneNode* centerNode = nullptr;

    bool rotationPlus = false;
    bool rotationMinus = false;

    ParticleSystem* pSys = nullptr;
    ParticleSystem* fireSys = nullptr;

    bool propulsion = false;
    int speedMult = 1;

    Ogre::SceneNode* mSinbadNode = nullptr;
    AnimationState* triangleAnimation = nullptr;

    SceneNode* explosionNode = nullptr;
    ParticleSystem* explosionSys = nullptr;
    SceneNode* sinbad1 = nullptr;
    SceneNode* sinbad2 = nullptr;

    bool explosion = false;
    bool done = false;

    // The snowman
    Ogre::SceneNode* snowman;
    Ogre::SceneNode* head;
    Ogre::SceneNode* body;
    Ogre::SceneNode* leftEye;
    Ogre::SceneNode* rightEye;
    Ogre::SceneNode* nose;
    Ogre::SceneNode* mouth;
    Ogre::SceneNode* bellyButton;
};

#endif
