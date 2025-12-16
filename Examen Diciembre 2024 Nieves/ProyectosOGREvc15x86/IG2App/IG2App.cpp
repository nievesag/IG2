#include "IG2App.h"

#include "DataSizes.h"
#include "OgreAnimation.h"
#include "OgreKeyFrame.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    if (evt.keysym.sym == SDLK_e)
    {
        estrella->Takeoff();
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
    mLightNode->setDirection(Ogre::Vector3(0, -1, -1));

    /*
    //------------------------------------------------------------------------
    // Creating Sinbad

    Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    mSinbadNode->attachObject(ent);

    // Show bounding box
    mSinbadNode->showBoundingBox(true);
    
    // Set position of Sinbad
    //mSinbadNode->setPosition(x, y, z);
    
    // Set scale of Sinbad
    mSinbadNode->setScale(20, 20, 20);
    
    //mSinbadNode->yaw(Ogre::Degree(-45));
    //mSinbadNode->setVisible(false);    
	*/

    estrellaChipNode = mSM->getRootSceneNode()->createChildSceneNode("estrella");
    estrella = new EstrellaChip({ 0,0,0 }, estrellaChipNode, mSM);

    addInputListener(estrella);
    
    MeshManager::getSingleton().createPlane("floor",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        1500, 1500, 200, 200,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);

    Ogre::Entity* plane = mSM->createEntity("floor");
    SceneNode* nodePlane = mSM->getRootSceneNode()->createChildSceneNode("floor");
    nodePlane->attachObject(plane);
    nodePlane->setPosition({0,-400,0});
    //plane->setMaterialName("Suelo");
    plane->setMaterialName("exam/waveShader");

    Ogre::Plane sky;
    sky.d = 20;
    sky.normal = Ogre::Vector3::UNIT_Z + Ogre::Vector3::UNIT_Y;
    mSM->setSkyPlane(true, sky, "Sky", 1, 1, true, 1.5, 50, 50);

    bolaFather = mSM->getRootSceneNode()->createChildSceneNode("bolaPadre");
    bolaFather->setPosition(0, 0, 0);
    

    Ogre::Entity* bola = mSM->createEntity("uv_sphere.mesh");
    nodeBola = bolaFather->createChildSceneNode("bola");
    nodeBola->attachObject(bola);
    nodeBola->setPosition({-300, 0,0});
    bola->setMaterialName("exam/coloredRocket");

    Ogre::Entity* bola1 = mSM->createEntity("uv_sphere.mesh");
    SceneNode* bola1node = nodeBola->createChildSceneNode("bolahola");
    bola1node->scale(0.3, 0.3, 0.3);
    bola1node->attachObject(bola1);
    bola1->setMaterialName("exam/coloredRocket");
    bola1node->setPosition({ 100,0,0 });

    Animation* animation = mSM->createAnimation("bolaAnim", 10.0f);
    animation->setInterpolationMode(Animation::IM_LINEAR);
    NodeAnimationTrack* track = animation->createNodeTrack(0);
    track->setAssociatedNode(nodeBola);
    TransformKeyFrame* kf;

    kf = track->createNodeKeyFrame(0);
    kf->setTranslate({ 0,100,0 });
    kf->setScale({ 0.5,0.5,0.5 });

	kf = track->createNodeKeyFrame(9.0f);
    kf->setTranslate({ 0,-400,0 });
    kf->setScale({1,1,1});

    bolaAnim = mSM->createAnimationState("bolaAnim");
    bolaAnim->setLoop(true);
    bolaAnim->setEnabled(true);
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{
    //estrellaChipNode->translate(0,DataSizes::SHIP_SPEED * evt.timeSinceLastFrame,0);
    estrellaChipNode->setPosition(DataSizes::SHIP_SPEED * evt.timeSinceLastFrame, sin(DataSizes::SHIP_SPEED * evt.timeSinceLastFrame) * 10, 0);

    //bolaFather->rotate({0,1,0}, Angle(evt.timeSinceLastFrame * DataSizes::SHIP_SPEED));

    //Real o = (evt.timeSinceLastFrame * DataSizes::SHIP_SPEED);
    //std::cout << o << std::endl;
    //float angle = cos(o) + sin(o);
    //nodeBola->yaw(Angle(angle));

    /*
    object.pos.x = object.speed * getElapsedTime();
    object.pos.y = sin(object.speed * getElapsedTime()) * amplitude;
    */
    bolaAnim->addTime(evt.timeSinceLastFrame);

}