#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    else if (evt.keysym.sym == SDLK_k) {
        cout << "Position of Sword: " << mSwordNode->getPosition() << endl;
        cout << "Position of the camera: " << mCamNode->getPosition() << endl;
    }
    
  return true;
}

void IG2App::shutdown(){
    
  mShaderGenerator->removeSceneManager(mSM);
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown(); 
}

void IG2App::setup(void){
    
    // do not forget to call the base first
    IG2ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);

    mSM->addRenderQueueListener(mOverlaySystem);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);
    
    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::setupScene(void){
    
    //------------------------------------------------------------------------
    // Creating the camera
    
    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, 0, 1000);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9)); // color de fondo
    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    
    //------------------------------------------------------------------------
    // Creating the light
    
    //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(0,0, -1));
    
    //------------------------------------------------------------------------
    // Creating Sinbad
    Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    //mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    //mSinbadNode->attachObject(ent);

    // Creating Dragon
    Ogre::Entity* ent1 = mSM->createEntity("dragon.mesh");
    mDragonNode = mSM->getRootSceneNode()->createChildSceneNode("nDragon");
    mDragonNode->attachObject(ent1);
    mDragonNode->setPosition(0, 200, 0);

    // Creating Sword
    Ogre::Entity* ent2 = mSM->createEntity("Sword.mesh");
    //mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nSword");
    //mSwordNode->attachObject(ent2);
    //mSwordNode->setScale(20, 20, 20);

    // Creating Helmet
    Ogre::Entity* ent3 = mSM->createEntity("DamagedHelmet.mesh");
    /*mHelmetNode = mSM->getRootSceneNode()->createChildSceneNode("nHelmet");
    mHelmetNode->attachObject(ent3);
    mHelmetNode->setScale(30, 30, 30);*/

    // Creating Head
    Ogre::Entity* ent4 = mSM->createEntity("ogrehead.mesh");
   /* mHeadNode = mSM->getRootSceneNode()->createChildSceneNode("nHead");
    mHeadNode->attachObject(ent4);
    mHeadNode->setScale(30, 30, 30);*/

    // Creating Facial
    Ogre::Entity* ent5 = mSM->createEntity("facial.mesh");
    /*mFacialNode = mSM->getRootSceneNode()->createChildSceneNode("nFacial");
    mFacialNode->attachObject(ent5);
    mFacialNode->setScale(30, 10, 10);*/

    // Creating Bath Upper
    Ogre::Entity* ent6 = mSM->createEntity("RomanBathUpper.mesh");
    mBathUNode = mSM->getRootSceneNode()->createChildSceneNode("nBathU");
    mBathUNode->attachObject(ent6);

    // Creating Bath Lower
    Ogre::Entity* ent7 = mSM->createEntity("RomanBathLower.mesh");
    mBathLNode = mSM->getRootSceneNode()->createChildSceneNode("nBathL");
    mBathLNode->attachObject(ent7);

    // Creating Columns
    Ogre::Entity* ent8 = mSM->createEntity("Columns.mesh");
    mColumnsNode = mSM->getRootSceneNode()->createChildSceneNode("nColumns");
    mColumnsNode->attachObject(ent8);

    // Creating SnowMan
    mSnowManNode = mSM->getRootSceneNode()->createChildSceneNode("snowman");
    // Cabeza
    Ogre::Entity* ent9 = mSM->createEntity("sphere.mesh");
    mCabezaNode = mSnowManNode->createChildSceneNode("nsphere");
    mCabezaNode->attachObject(ent9);
    // Ojo Der
    Ogre::Entity* ent10 = mSM->createEntity("sphere.mesh");
    mOjoDerNode = mCabezaNode->createChildSceneNode("nsphere1");
    mOjoDerNode->attachObject(ent10);
    // Ojo Idz
    Ogre::Entity* ent11 = mSM->createEntity("sphere.mesh");
    mOjoIzqNode = mCabezaNode->createChildSceneNode("nsphere2");
    mOjoIzqNode->attachObject(ent11);
    // Nariz
    Ogre::Entity* ent12 = mSM->createEntity("sphere.mesh");
    mNarizNode = mCabezaNode->createChildSceneNode("nsphere3");
    mNarizNode->attachObject(ent12);
    // Cuerpo
    Ogre::Entity* ent13 = mSM->createEntity("sphere.mesh");
    mCuerpoNode = mSnowManNode->createChildSceneNode("nsphere4");
    mCuerpoNode->attachObject(ent13);
    // Ombligo
    Ogre::Entity* ent14 = mSM->createEntity("sphere.mesh");
    mOmbligoNode = mCuerpoNode->createChildSceneNode("nsphere5");
    mOmbligoNode->attachObject(ent14);

    mCabezaNode->setPosition(0, 100, 0);
    mCabezaNode->setScale(0.7, 0.7, 0.7);
    mOjoDerNode->setPosition(70, 50, 70);
    mOjoDerNode->setScale(0.2, 0.2, 0.2);
    mOjoIzqNode->setPosition(-70, 50, 70);
    mOjoIzqNode->setScale(0.2, 0.2, 0.2);
    mNarizNode->setPosition(0, 0, 80);
    mNarizNode->setScale(0.2, 0.2, 0.5);
    mOmbligoNode->setPosition(0, 0, 100);
    mOmbligoNode->setScale(0.1, 0.1, 0.1);
    
    

    // Show bounding box
    //mSinbadNode->showBoundingBox(true);
    
    // Set position of Sinbad
    //mSinbadNode->setPosition(x, y, z);
    
    // Set scale of Sinbad
    //mSinbadNode->setScale(20, 20, 20);

    //mSinbadNode->yaw(Ogre::Degree(-45));
    //mSinbadNode->setVisible(false);    
}


