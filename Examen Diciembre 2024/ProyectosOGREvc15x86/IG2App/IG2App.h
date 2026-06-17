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

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener{

public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()
    virtual ~IG2App() { };                                    // delete -> shutdown()
 
protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();
    virtual void frameRendered(const Ogre::FrameEvent& evt) override;

    Ogre::SceneNode* mSinbadNode = nullptr;
      
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;
    
    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;
    
    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    Ogre::SceneNode* spaceShip = nullptr;
    Ogre::SceneNode* engineN = nullptr;
    Ogre::SceneNode* rocketsRack = nullptr;

    Ogre::ParticleSystem* fireSys = nullptr;
    bool start = false;
    float countdown = 0.0f;
    bool takeoff = false;

    // extra
    Ogre::SceneNode* ghostExplorer = nullptr;

    Ogre::SceneNode* sinbadN = nullptr;
    float time = 0.0f;
};

#endif