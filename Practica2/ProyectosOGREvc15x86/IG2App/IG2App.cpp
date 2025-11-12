#include "IG2App.h"

#include "Fisher.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown(); 
}

void IG2App::setup(void) 
{    
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

void IG2App::setupScene(void)
{
    // ---------------- CAMARA
    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);
           
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, 100, -100);
    mCamNode->lookAt(Ogre::Vector3(0, 0, -400), Ogre::Node::TS_WORLD);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(ColourValue(0, 0, 0, 1));
    
    // >> descomentar para usar eventos de teclado para mover la camara
    /*mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);*/
    // <<
    
    // ---------------- OBJETOS ESCENA
    // -- Hero
    SceneNode* nodeHero = mSM->getRootSceneNode()->createChildSceneNode("Hero");
    nodeHero->setScale(11, 11, 11);
    mHero = new Hero(Vector3(0, 0, 0), nodeHero, mSM, "Sinbad.mesh");
    addInputListener(mHero);

    // -- Enemigos
    for (int i = 0; i < enemyCount; i++)
    {
        SceneNode* nodeEnemy = mSM->getRootSceneNode()->createChildSceneNode("Enemy" + i);
        mEnemiesNode.push_back(nodeEnemy);
        mEnemies.push_back(new Fisher(Vector3(0, 0, 0), nodeEnemy, mSM));
        addInputListener(mEnemies.back());
    }

    // -- UI
    OgreBites::Label* stageLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "StageLabel", "Stage: ", 200);
    OgreBites::TextBox* infoTextBox = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "InfoTextBox", "Game info here!", 200, 100);

    // -- Laberinto
    mLab = new Labyrinth();
    mLab->setupLabyrinth(mSM, mHero, nodeHero, mEnemies, mEnemiesNode, mCamNode);
    mLab->readFile("stage1.txt");
    mLab->registerUI(stageLabel, infoTextBox);
    addInputListener(mLab);
}