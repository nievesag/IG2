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
    
    // Objetos escena
    Ogre::SceneNode* mSinbadNode = nullptr;
    Ogre::SceneNode* mDragonNode = nullptr;
    Ogre::SceneNode* mSwordNode = nullptr;
    Ogre::SceneNode* mHelmetNode = nullptr;
    Ogre::SceneNode* mHeadNode = nullptr;
    Ogre::SceneNode* mFacialNode = nullptr;
    Ogre::SceneNode* mBathUNode = nullptr;
    Ogre::SceneNode* mBathLNode = nullptr;
    Ogre::SceneNode* mColumnsNode = nullptr;
    //
    Ogre::SceneNode* mSnowManNode = nullptr;    // ---------- nodo snowman root
    Ogre::SceneNode* mCabezaNode = nullptr;     // ------- cabeza
    Ogre::SceneNode* mOjoDerNode = nullptr;     // --- ojo izq
    Ogre::SceneNode* mOjoIzqNode = nullptr;     // --- ojo der
    Ogre::SceneNode* mNarizNode = nullptr;      // --- nariz
    Ogre::SceneNode* mCuerpoNode = nullptr;     // ------- cuerpo
    Ogre::SceneNode* mOmbligoNode = nullptr;    // --- ombligo

      
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;
    
    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;
    
    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;
};

#endif
