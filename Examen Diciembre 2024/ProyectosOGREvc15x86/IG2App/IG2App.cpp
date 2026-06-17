#include "IG2App.h"
#include "DataSizes.h"
#include "OgreAnimation.h"
#include "OgreKeyFrame.h"
#include "OgreParticleSystem.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    else if (evt.keysym.sym == SDLK_e)
    {
        fireSys->setEmitting(true);

        if (!takeoff) start = true;
    }
    else if (evt.keysym.sym == SDLK_w)
    {
        ghostExplorer->pitch(Angle(-(5)));
    }
    else if (evt.keysym.sym == SDLK_s)
    {
        ghostExplorer->yaw(Angle(-(5)));
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

    mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(0, 0, -1));

    //------------------------------------------------------------------------
    // Nave
    spaceShip = mSM->getRootSceneNode()->createChildSceneNode("spaceship");

    // body
    Entity* ent = mSM->createEntity("uv_sphere.mesh");
    SceneNode* node = spaceShip->createChildSceneNode("body");
    node->attachObject(ent);

    node->_update(false, false);
    node->setScale(DataSizes::SPACESHIP_BODY_SIZE / node->_getWorldAABB().getSize());

    ent->setMaterialName("examen/body");

    // engine
    engineN = spaceShip->createChildSceneNode("engine");

    node = engineN->createChildSceneNode("barrel");
    ent = mSM->createEntity("Barrel.mesh");
    node->attachObject(ent);
    ent->setMaterialName("examen/engine");

    node->_update(false, false);
    node->setScale(DataSizes::ENGINE_BASE_SIZE / node->_getWorldAABB().getSize());

    engineN->translate(0, -(DataSizes::SPACESHIP_BODY_SIZE.y/2), 0, Node::TS_WORLD);

    rocketsRack = engineN->createChildSceneNode("rockets");

    Real step = (Math::PI * 2) / DataSizes::NUM_ROCKETS;
    for (int i = 0; i < DataSizes::NUM_ROCKETS; i++)
    {
        SceneNode* rocketNode = rocketsRack->createChildSceneNode("rocket" + std::to_string(i));

        Entity* cubeEnt = mSM->createEntity("cube.mesh");
        SceneNode* cubeNode = rocketNode->createChildSceneNode("cube" + std::to_string(i));
        cubeNode->attachObject(cubeEnt);
        cubeEnt->setMaterialName("examen/cube");

        cubeNode->_update(false, false);
        cubeNode->setScale(DataSizes::ROCKET_CUBE_SIZE/ cubeNode->_getWorldAABB().getSize());

        Entity* sphereEnt = mSM->createEntity("uv_sphere.mesh");
        SceneNode* sphereNode = rocketNode->createChildSceneNode("sphere" + std::to_string(i));
        sphereNode->attachObject(sphereEnt);
        sphereEnt->setMaterialName("examen/sphere");

        sphereNode->_update(false, false);
        sphereNode->setScale(DataSizes::ROCKET_SPHERE_SIZE / sphereNode->_getWorldAABB().getSize());
        sphereNode->translate(0, -DataSizes::ROCKET_CUBE_SIZE.y/2, 0);

        rocketNode->setPosition(
            (DataSizes::ENGINE_BASE_SIZE.x / 2) * cos(i * step),
            -(DataSizes::ROCKET_CUBE_SIZE.y / 2),
            (DataSizes::ENGINE_BASE_SIZE.x / 2) * sin(i * step)
        );

        rocketNode->setInheritOrientation(false);
        rocketNode->setInheritScale(false);

        // particulas
        if (i % 2 == 0) // par
        {
            rocketNode->yaw(Angle(DataSizes::ROCKET_DEGREE), Node::TS_WORLD);

            ParticleSystem* pSys = mSM->createParticleSystem("smoke" + std::to_string(i), "examen/white");
            pSys->setEmitting(true);
            rocketNode->attachObject(pSys);
        }
        else // impar
        {
            rocketNode->yaw( Angle(-DataSizes::ROCKET_DEGREE), Node::TS_WORLD);
            ParticleSystem* pSys = mSM->createParticleSystem("smoke" + std::to_string(i), "examen/grey");
            pSys->setEmitting(true);
            rocketNode->attachObject(pSys);
        }

        rocketNode->_update(false, false);
        //rocketNode->setScale(DataSizes::ROCKET_SIZE / rocketNode->_getWorldAABB().getSize());
        rocketNode->translate(0, -(DataSizes::ENGINE_BASE_SIZE.y/2),0);
    }

    SceneNode* fire = spaceShip->createChildSceneNode("fireNode");
    fireSys = mSM->createParticleSystem("fire", "examen/fire");
    fireSys->setEmitting(false);
    fire->attachObject(fireSys);

    fire->translate(0, -(DataSizes::ENGINE_BASE_SIZE.y/2 + (DataSizes::SPACESHIP_BODY_SIZE.y/2)), 0);

    // Suelo y cielo
    // suelo
    SceneNode* planeN = mSM->getRootSceneNode()->createChildSceneNode("plane");
    MeshManager::getSingleton().createPlane("floor",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        1500, 1500, 200, 200,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);

    Ogre::Entity* plane = mSM->createEntity("floor");
    planeN->attachObject(plane);

    planeN->translate(0, -500, 0);
    //plane->setMaterialName("examen/floor");
    plane->setMaterialName("exam/waveShader");

    // cielo
    Ogre::Plane sky;
    sky.d = 1000;
    sky.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
    mSM->setSkyPlane(true, sky, "examen/sky", 1500, 20, true, 10, 50, 50);

    // Planeta y orbita
    Entity* planet = mSM->createEntity("uv_sphere.mesh");
    SceneNode* planetN = mSM->getRootSceneNode()->createChildSceneNode("planet");
    planetN->attachObject(planet);
    planetN->setPosition(-500, 0,0);
    planet->setMaterialName("exam/planetShader");

	ghostExplorer = mSM->getRootSceneNode()->createChildSceneNode("ghost");
    ghostExplorer->setPosition(-500, 0, 0);

    Entity* explorer = mSM->createEntity("uv_sphere.mesh");
    SceneNode* explorerN = ghostExplorer->createChildSceneNode("explorer");
    explorerN->attachObject(explorer);
    explorerN->setPosition(0, 100, 0);
    explorerN->scale(0.1, 0.1, 0.2);

    Entity* explorerNose = mSM->createEntity("uv_sphere.mesh");
    SceneNode* explorerNoseN = explorerN->createChildSceneNode("explorer_nose");
    explorerNoseN->attachObject(explorerNose);
    explorerNoseN->setPosition(0, 0, -100);
    explorerNoseN->scale(0.3, 0.3, 0.3);

    float r = 200;
    float n = 50;
    Real step1 = (Math::PI * 2) / n;
    SceneNode* ring = mSM->getRootSceneNode()->createChildSceneNode("ring");
    for (int i = 0; i < n; i++)
    {
        Entity* orbit = mSM->createEntity("uv_sphere.mesh");
        SceneNode* orbitNode = ring->createChildSceneNode("orbit" + std::to_string(i));
        orbitNode->attachObject(orbit);

        orbitNode->setScale(0.1, 0.1, 0.1);

        Real yPos = 15 * sin((20 * i));
        orbitNode->setPosition(r * sin(i * step1), yPos, r * cos(i * step1));
    }

    ring->setPosition(-500, 0, 0);

    // Sinbad
    Entity* sinbad = mSM->createEntity("Sinbad.mesh");
	sinbadN = mSM->getRootSceneNode()->createChildSceneNode("nsinbad");
    sinbadN->attachObject(sinbad);
    sinbadN->setPosition(0, 0, 200);
    sinbadN->scale(10, 10, 10);
    sinbadN->yaw(Angle(90));
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{
    if (start)
    {
        if (!takeoff)
        {
	        countdown += evt.timeSinceLastFrame;

	        if (countdown >= DataSizes::TIME_ENGINE_START)
	        {
	            takeoff = true;
	        }
        }
    }

    if (takeoff)
    {
        spaceShip->translate(0, evt.timeSinceLastFrame * DataSizes::SHIP_SPEED,0);
        rocketsRack->yaw(Angle(evt.timeSinceLastFrame * DataSizes::SHIP_ROTATION));
    }

    time += evt.timeSinceLastFrame;
    sinbadN->setPosition(sinbadN->getPosition().x + (evt.timeSinceLastFrame * DataSizes::SHIP_SPEED), 20 * sin(time * DataSizes::TIME_ENGINE_START), 200);
}