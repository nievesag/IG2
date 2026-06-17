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
    else if (evt.keysym.sym == SDLK_s) {
        dir *= -1;
    }
    else if (evt.keysym.sym == SDLK_f) {
        turnSphere = !turnSphere;
    }
    else if (evt.keysym.sym == SDLK_d) {
        turnOuter = !turnOuter;
    }
    else if (evt.keysym.sym == SDLK_a) {
        emit = !emit;

        for (auto s : pSystems)
        {
            s->setEmitting(emit);
        }
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
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(0, 0, -1));
    
    //------------------------------------------------------------------------
	// Animacion

    Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    mSinbadNode->attachObject(ent);
    mSinbadNode->setScale(2, 2, 2);
    mSinbadNode->setPosition(DataSizes::SINBAD_INITIAL_POSITION);

    mSinbadNode->setInitialState();

    Ogre::Animation* animation = mSM->createAnimation("triangle", DataSizes::SINBAD_TIME_WALKING*3 + DataSizes::SINBAD_TIME_ROTATING*3);
    animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
    NodeAnimationTrack* track = animation->createNodeTrack(0);
    track->setAssociatedNode(mSinbadNode);
    TransformKeyFrame* kf;

    // --- 0
    kf = track->createNodeKeyFrame(0);
    kf->setTranslate(DataSizes::SINBAD_INITIAL_POSITION);

    // --- 1
    kf = track->createNodeKeyFrame(DataSizes::SINBAD_TIME_ROTATING);

    kf->setTranslate(DataSizes::SINBAD_INITIAL_POSITION);

    Vector3 look = Vector3(mSinbadNode->_getDerivedOrientation() * Vector3::UNIT_Z);
    Quaternion quat = Quaternion(Angle(120), Vector3::UNIT_Y);

    Vector3 lookNew = quat * look;
    kf->setRotation(look.getRotationTo(lookNew));

    // --- 2 
    kf = track->createNodeKeyFrame(DataSizes::SINBAD_TIME_ROTATING + DataSizes::SINBAD_TIME_WALKING);
    kf->setRotation(look.getRotationTo(lookNew));

    Vector3 nextPos = mSinbadNode->getPosition() + (lookNew * DataSizes::SINBAD_WALK_LENGTH);
    kf->setTranslate(nextPos);

    // --- 3
    kf = track->createNodeKeyFrame(DataSizes::SINBAD_TIME_ROTATING * 2 + DataSizes::SINBAD_TIME_WALKING);
    kf->setTranslate(nextPos);

    look = lookNew;
	quat = Quaternion(Angle(240), Vector3::UNIT_Y);
    lookNew = quat * look;
    kf->setRotation(look.getRotationTo(lookNew));

    // --- 4
    kf = track->createNodeKeyFrame(DataSizes::SINBAD_TIME_ROTATING * 2 + DataSizes::SINBAD_TIME_WALKING * 2);
    kf->setRotation(look.getRotationTo(lookNew));

	nextPos = mSinbadNode->getPosition() + (-lookNew * DataSizes::SINBAD_WALK_LENGTH);
    kf->setTranslate(nextPos);

    // --- 5
    kf = track->createNodeKeyFrame(DataSizes::SINBAD_TIME_ROTATING * 3 + DataSizes::SINBAD_TIME_WALKING * 2);
    kf->setTranslate(nextPos);

    look = lookNew;
    quat = Quaternion(Angle(360), Vector3::UNIT_Y);
    lookNew = quat * look;
    kf->setRotation(look.getRotationTo(lookNew));

    // --- 6
    kf = track->createNodeKeyFrame(DataSizes::SINBAD_TIME_ROTATING * 3 + DataSizes::SINBAD_TIME_WALKING * 3);
    kf->setRotation(look.getRotationTo(lookNew));

    kf->setTranslate(DataSizes::SINBAD_INITIAL_POSITION);

    animationState = mSM->createAnimationState("triangle");
    animationState->setLoop(true);
    animationState->setEnabled(true);

    animationStateWalk = ent->getAnimationState("RunBase");
    animationStateWalk->setLoop(true);
    animationStateWalk->setEnabled(true);

    animationStateWalkTop = ent->getAnimationState("RunTop");
    animationStateWalkTop->setLoop(true);
    animationStateWalkTop->setEnabled(true);

    // Rings
    outer = mSM->getRootSceneNode()->createChildSceneNode("outer");

    Real step = (Math::PI * 2) / DataSizes::NUM_SPHERES_PER_RING;
    for (int i = 0; i < DataSizes::NUM_SPHERES_PER_RING; i++)
    {
        Entity* outerE = mSM->createEntity("uv_sphere.mesh");
        SceneNode* outerN = outer->createChildSceneNode("outer" + std::to_string(i));
        outerN->attachObject(outerE);

        outerN->_update(false, false);
        outerN->setScale(DataSizes::SPHERE_SIZE / outerN->_getWorldAABB().getSize());

        outerN->translate(DataSizes::OUTER_RING_RADIUS * cos(i * step),
							0,
							DataSizes::OUTER_RING_RADIUS * sin(i * step)
        );

        outerN->roll(Angle(90));
        outerN->pitch(Radian(-(i * step)));

        outerE->setMaterialName("examen/shader");
    }

    inner = mSM->getRootSceneNode()->createChildSceneNode("inner");
    for (int i = 0; i < DataSizes::NUM_SPHERES_PER_RING; i++)
    {
        Entity* innerE = mSM->createEntity("uv_sphere.mesh");
        SceneNode* innerN = inner->createChildSceneNode("inner" + std::to_string(i));
        innerN->attachObject(innerE);

        innerN->_update(false, false);
        innerN->setScale(DataSizes::SPHERE_SIZE / innerN->_getWorldAABB().getSize());

        innerN->translate(DataSizes::INNER_RING_RADIUS * cos(i * step),
            DataSizes::INNER_RING_RADIUS * sin(i * step),
            0
        );

        SceneNode* particle = innerN->createChildSceneNode("particle" + std::to_string(i));

        if (i % 2 == 0)
        {
			innerE->setMaterialName("examen/par");

            // Particulas
            ParticleSystem* pSys = mSM->createParticleSystem("white" + std::to_string(i), "examen/whiteSmokeParticle");
            pSys->setEmitting(emit);
            particle->attachObject(pSys);

            pSystems.push_back(pSys);

            particle->roll(Angle(-90));
            particle->roll(Radian((i * step)));
        }
        else
        {
            innerE->setMaterialName("examen/impar");

            // Particulas
            ParticleSystem* pSys = mSM->createParticleSystem("black" + std::to_string(i), "examen/blackSmokeParticle");
            pSys->setEmitting(emit);
            particle->attachObject(pSys);

            pSystems.push_back(pSys);

            particle->roll(Angle(-90));
            particle->roll(Radian((i * step)));
        }

        innerSpheres.push_back(innerN);
    }

    // Suelo y cielo
    SceneNode* floor = mSM->getRootSceneNode()->createChildSceneNode("floor");

    MeshManager::getSingleton().createPlane("floor",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        1500, 1500, 100, 80,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);

    Ogre::Entity* plane = mSM->createEntity("floor");
    floor->attachObject(plane);
    plane->setMaterialName("examen/floor");
    floor->translate(0, -DataSizes::OUTER_RING_RADIUS - 100, 0);

    Ogre::Plane sky;
    sky.d = 1000;
    sky.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
    mSM->setSkyPlane(true, sky, "examen/sky", 1500, 50, true, 10, 100, 100);
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{
    inner->yaw(Angle(evt.timeSinceLastFrame * (dir * DataSizes::RING_SPEED)));

    if (turnSphere)
    {
	    for (auto s : innerSpheres)
	    {
	        s->yaw(Angle(evt.timeSinceLastFrame * DataSizes::SPHERE_SPEED));
	    }
    }

    if (turnOuter)
    {
        outer->pitch(Angle(evt.timeSinceLastFrame * DataSizes::RING_SPEED));
    }

    animationState->addTime(evt.timeSinceLastFrame);
    animationStateWalk->addTime(evt.timeSinceLastFrame);
    animationStateWalkTop->addTime(evt.timeSinceLastFrame);
}