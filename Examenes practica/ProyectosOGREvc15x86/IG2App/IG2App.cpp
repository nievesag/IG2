#include "IG2App.h"

#include "DataSizes.h"
#include "DataSizesExtra.h"
#include "OgreAnimation.h"
#include "OgreKeyFrame.h"
#include <OgreBillboardSet.h>
#include <OgreParticleSystem.h>

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
    // a -> avion gira sobre el eje X AIRPLANE_ROTATION
    else if (evt.keysym.sym == SDLK_a) 
    {
        rotationMinus = false;
        rotationPlus = true;
    }
    // d -> avion gira sobre el eje X -AIRPLANE_ROTATION
    else if (evt.keysym.sym == SDLK_d) 
    {
        rotationMinus = true;
        rotationPlus = false;
    }
    // s -> avion ya no gira
    else if (evt.keysym.sym == SDLK_s) 
    {
        rotationMinus = false;
        rotationPlus = false;
    }
    // w -> toggle propulsion
    else if (evt.keysym.sym == SDLK_w)
    {
        propulsion = !propulsion;

        fireSys->setEmitting(propulsion);

        if (propulsion) speedMult = 2;
        else speedMult = 1;
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
    cam->setFarClipDistance(250000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, 0, 2000);
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
    mLightNode->setDirection(Ogre::Vector3(0, -1, -1));

    // colision
    Entity* sinbad1Ent = mSM->createEntity("Sinbad.mesh");
    sinbad1 = mSM->getRootSceneNode()->createChildSceneNode("sinbad1");
    sinbad1->attachObject(sinbad1Ent);

    sinbad1->setPosition(-2500, 0, -2500);
    sinbad1->setScale(40, 40, 40);
    sinbad1->yaw(Angle(90));

    Entity* sinbad2Ent = mSM->createEntity("Sinbad.mesh");
    sinbad2 = mSM->getRootSceneNode()->createChildSceneNode("sinbad2");
    sinbad2->attachObject(sinbad2Ent);

    sinbad2->setPosition(2500, 0, -2500);
    sinbad2->setScale(40, 40, 40);
    sinbad2->yaw(Angle(-90));

    explosionSys = mSM->createParticleSystem("explosion", "examen/explosion");
    explosionSys->setEmitting(false);

    explosionNode = mSM->getRootSceneNode()->createChildSceneNode("explosionNode");
    explosionNode->attachObject(explosionSys);

    // circulo
    Real cirStep = (Math::PI * 2) / DataSizesExtra::NUM_SPHERE;
    for (int i = 0; i < DataSizesExtra::NUM_SPHERE; i++)
    {
        Entity* cirEnt = mSM->createEntity("uv_sphere.mesh");
        SceneNode* cirNode = mSM->getRootSceneNode()->createChildSceneNode("cir" + to_string(i));
        cirNode->attachObject(cirEnt);

        cirNode->setScale(0.1,0.1,0.1);
        cirNode->setPosition((DataSizesExtra::OUTER_RING_RADIUS + 10 * i) * cos(cirStep*i),
            10 * i,
            (DataSizesExtra::OUTER_RING_RADIUS + 10 * i) * sin(cirStep*i)
        );

        cirEnt->setMaterialName("examen/shaderColores");
    }

    // shaders
    Entity* dicEnt = mSM->createEntity("uv_sphere.mesh");
    SceneNode* dicNode = mSM->getRootSceneNode()->createChildSceneNode("diciembre");
    dicNode->attachObject(dicEnt);

    dicNode->setPosition(Vector3(0, 600, 0));
    dicEnt->setMaterialName("examen/diciembre");
       
    // ------- SINBAD
    Ogre::Entity* sinbadEnt = mSM->createEntity("Sinbad.mesh");
    mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    mSinbadNode->attachObject(sinbadEnt);

    mSinbadNode->setScale(30, 30, 30);
    mSinbadNode->setPosition(DataSizesExtra::SINBAD_INITIAL_POSITION);

    mSinbadNode->setInitialState();

    // animacion
    Animation* animation = mSM->createAnimation("triangle", DataSizesExtra::SINBAD_TIME_ROTATING * 3 + DataSizesExtra::SINBAD_TIME_WALKING * 3);
    animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
    NodeAnimationTrack* track = animation->createNodeTrack(0);
    track->setAssociatedNode(mSinbadNode);
    TransformKeyFrame* kf;

    // kf 0
    kf = track->createNodeKeyFrame(0);
    kf->setTranslate(DataSizesExtra::SINBAD_INITIAL_POSITION);

    // kf 1
    kf = track->createNodeKeyFrame(DataSizesExtra::SINBAD_TIME_ROTATING);

    Vector3 look = Ogre::Vector3(mSinbadNode->_getDerivedOrientation() * Vector3::UNIT_Z);
    Quaternion quat = Ogre::Quaternion(Angle(120), Vector3::UNIT_Y);

    Ogre::Vector3 rotated = quat * look;
    kf->setTranslate(DataSizesExtra::SINBAD_INITIAL_POSITION);
    kf->setRotation(look.getRotationTo(rotated)); // gira

    // kf 2
    kf = track->createNodeKeyFrame(DataSizesExtra::SINBAD_TIME_ROTATING + DataSizesExtra::SINBAD_TIME_WALKING);

    Ogre::Vector3 nextPos = mSinbadNode->getPosition() + (rotated * DataSizesExtra::SINBAD_WALK_LENGTH);
    kf->setRotation(look.getRotationTo(rotated)); // gira
    kf->setTranslate(nextPos);

    // kf 3
    kf = track->createNodeKeyFrame(DataSizesExtra::SINBAD_TIME_ROTATING * 2 + DataSizesExtra::SINBAD_TIME_WALKING);

    look = rotated;
    quat = Ogre::Quaternion(Angle(240), Vector3::UNIT_Y);
	rotated = quat * look;
    kf->setTranslate(nextPos);
    kf->setRotation(look.getRotationTo(rotated)); // gira

    // kf 4
    kf = track->createNodeKeyFrame(DataSizesExtra::SINBAD_TIME_ROTATING * 2 + DataSizesExtra::SINBAD_TIME_WALKING * 2);

    nextPos = mSinbadNode->getPosition() + (-rotated * DataSizesExtra::SINBAD_WALK_LENGTH);
    kf->setRotation(look.getRotationTo(rotated)); // gira
    kf->setTranslate(nextPos);

    // kf 5
    kf = track->createNodeKeyFrame(DataSizesExtra::SINBAD_TIME_ROTATING * 3 + DataSizesExtra::SINBAD_TIME_WALKING * 2);

    look = rotated;
    quat = Ogre::Quaternion(Angle(360), Vector3::UNIT_Y);
    rotated = quat * look;
    kf->setTranslate(nextPos);
    kf->setRotation(look.getRotationTo(rotated)); // gira

    // kf 6
    kf = track->createNodeKeyFrame(DataSizesExtra::SINBAD_TIME_ROTATING * 3 + DataSizesExtra::SINBAD_TIME_WALKING * 3);

    nextPos = mSinbadNode->getPosition() + (rotated * DataSizesExtra::SINBAD_WALK_LENGTH);
    kf->setRotation(look.getRotationTo(rotated)); // gira
    kf->setTranslate(DataSizesExtra::SINBAD_INITIAL_POSITION);

    triangleAnimation = mSM->createAnimationState("triangle");
    triangleAnimation->setLoop(true);
    triangleAnimation->setEnabled(true);

    /*
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

    /*
    kf = track->createNodeKeyFrame(0);
    kf->setTranslate({ 0,100,0 });
    kf->setScale({ 0.5,0.5,0.5 });

	kf = track->createNodeKeyFrame(9.0f);
    kf->setTranslate({ 0,-400,0 });
    kf->setScale({1,1,1});

    bolaAnim = mSM->createAnimationState("bolaAnim");
    bolaAnim->setLoop(true);
    bolaAnim->setEnabled(true);
	*/

    // billboards
    // 1
    Entity* sphereEnt = mSM->createEntity("sphere.mesh");
    SceneNode* sphereNode = mSM->getRootSceneNode()->createChildSceneNode();
    sphereNode->attachObject(sphereEnt);
    sphereNode->setPosition(Vector3(0, 100, 0));
    sphereEnt->setMaterialName("examen/billboard1");

    // 2
    SceneNode* bbNode = mSM->getRootSceneNode()->createChildSceneNode();
    BillboardSet* bbSet = mSM->createBillboardSet("set",1);
    bbSet->setDefaultDimensions(120, 120);
    bbSet->setMaterialName("examen/billboard2");
    bbNode->attachObject(bbSet);
    bbSet->createBillboard({ 0, 400, -50 });

    // ------- JUNIO 2025
    centerNode = mSM->getRootSceneNode()->createChildSceneNode();

    airplaneNode = centerNode->createChildSceneNode();
    // body
    Ogre::Entity* bodyEnt = mSM->createEntity("uv_sphere.mesh");
    Ogre::SceneNode* bodyNode = airplaneNode->createChildSceneNode("body");
    bodyNode->attachObject(bodyEnt);

    bodyNode->_update(false, false);
    bodyNode->setScale(DataSizesExtra::AIRPLANE_BODY_SIZE / bodyNode->_getWorldAABB().getSize());
    bodyEnt->setMaterialName("examen/body");

    // wing1
    Ogre::Entity* wing1Ent = mSM->createEntity("cube.mesh");
    Ogre::SceneNode* wing1Node = airplaneNode->createChildSceneNode("wing1");
    wing1Node->attachObject(wing1Ent);

    wing1Node->_update(false, false);
    wing1Node->setScale(DataSizesExtra::AIRPLANE_WING_SIZE / wing1Node->_getWorldAABB().getSize());

    Real posX1 = -(((DataSizesExtra::AIRPLANE_BODY_SIZE.x) / 2) + ((DataSizesExtra::AIRPLANE_WING_SIZE.x) / 2));
    wing1Node->setPosition(posX1,0,0);
    wing1Node->pitch(Angle(90));

    wing1Ent->setMaterialName("examen/wings");

    // wing2
    Ogre::Entity* wing2Ent = mSM->createEntity("cube.mesh");
    Ogre::SceneNode* wing2Node = airplaneNode->createChildSceneNode("wing2");
    wing2Node->attachObject(wing2Ent);

    wing2Node->_update(false, false);
    wing2Node->setScale(DataSizesExtra::AIRPLANE_WING_SIZE / wing2Node->_getWorldAABB().getSize());

    Real posX2 = (((DataSizesExtra::AIRPLANE_BODY_SIZE.x) / 2) + ((DataSizesExtra::AIRPLANE_WING_SIZE.x) / 2));
    wing2Node->setPosition(posX2, 0, 0);
    wing2Node->pitch(Angle(90));

    wing2Ent->setMaterialName("examen/wings");

    // timon
    Ogre::Entity* rudderEnt = mSM->createEntity("cube.mesh");
    Ogre::SceneNode* rudderNode = airplaneNode->createChildSceneNode("rudder");
    rudderNode->attachObject(rudderEnt);

    rudderNode->_update(false, false);
    rudderNode->setScale(DataSizesExtra::AIRPLANE_RUDDER_SIZE / rudderNode->_getWorldAABB().getSize());

    Real posR = ((DataSizesExtra::AIRPLANE_BODY_SIZE.x) / 2) + ((DataSizesExtra::AIRPLANE_RUDDER_SIZE.z) / 2);
    Real posRY = -((DataSizesExtra::AIRPLANE_BODY_SIZE.y) / 2);
    rudderNode->setPosition(0, posRY, posR);
    rudderNode->roll(Angle(90));
	rudderNode->yaw(Angle(90));
	rudderNode->yaw(Angle(-20));

    rudderEnt->setMaterialName("examen/wings");

    // motor1
    Ogre::Entity* motorEnt = mSM->createEntity("Barrel.mesh");
    Ogre::SceneNode* motorNode = airplaneNode->createChildSceneNode("motor1");
    motorNode->attachObject(motorEnt);

    motorNode->_update(false, false);
    //motorNode->setInheritScale(false);
    motorNode->setScale(DataSizesExtra::ENGINE_BASE_SIZE / motorNode->_getWorldAABB().getSize());

    motorNode->setPosition((DataSizesExtra::AIRPLANE_WING_SIZE.x / 2) + (DataSizesExtra::AIRPLANE_BODY_SIZE.x /2), 0, -((DataSizesExtra::ENGINE_BASE_SIZE.x / 2) + (DataSizesExtra::AIRPLANE_WING_SIZE.y / 2)));

    motorEnt->setMaterialName("examen/engine");

    // motor2
    Ogre::Entity* motorEnt2 = mSM->createEntity("Barrel.mesh");
    Ogre::SceneNode* motorNode2 = airplaneNode->createChildSceneNode("motor2");
    motorNode2->attachObject(motorEnt2);

    motorNode2->_update(false, false);
    motorNode2->setScale(DataSizesExtra::ENGINE_BASE_SIZE / motorNode2->_getWorldAABB().getSize());

    motorNode2->setPosition(-((DataSizesExtra::AIRPLANE_WING_SIZE.x / 2) + (DataSizesExtra::AIRPLANE_BODY_SIZE.x / 2)), 0, -((DataSizesExtra::ENGINE_BASE_SIZE.x / 2) + (DataSizesExtra::AIRPLANE_WING_SIZE.y/2)));

    motorEnt2->setMaterialName("examen/engine");

    // circulo1
    Real step = (2 * Math::PI) / DataSizesExtra::AIRPLANE_NUM_ROCKETS;
    Real radius = DataSizesExtra::ENGINE_BASE_SIZE.x / 2;
    for (int i = 0; i < DataSizesExtra::AIRPLANE_NUM_ROCKETS; i++)
    {
        Ogre::Entity* rocketEnt = mSM->createEntity("uv_sphere.mesh");
        SceneNode* rocketNode = motorNode->createChildSceneNode("rocket1" + std::to_string(i));
        rocketNode->attachObject(rocketEnt);

        rocketNode->_update(false, false);
        
        rocketNode->setScale((DataSizesExtra::ROCKET_SIZE / rocketNode->_getWorldAABB().getSize()));

        rocketNode->translate(radius * cos(step * i),
								-(DataSizesExtra::ENGINE_BASE_SIZE.y/2 + DataSizesExtra::ROCKET_SIZE.y/2) ,
								radius * sin(step * i), Node::TS_WORLD);

        rocketEnt->setMaterialName("examen/rocket");

        if (i%2 == 0)
        {
	        pSys = mSM->createParticleSystem("smokeWhite" + std::to_string(i), "examen/smokeWhite");
	        pSys->setEmitting(true);
	        rocketNode->attachObject(pSys);
        }
        else
        {
            pSys = mSM->createParticleSystem("smokeGrey" + std::to_string(i), "examen/smokeGrey");
            pSys->setEmitting(true);
            rocketNode->attachObject(pSys);
        }
    }

    // circulo2
    for (int i = 0; i < DataSizesExtra::AIRPLANE_NUM_ROCKETS; i++)
    {
        Ogre::Entity* rocketEnt = mSM->createEntity("uv_sphere.mesh");
        SceneNode* rocketNode = motorNode2->createChildSceneNode("rocket2" + std::to_string(i));
        rocketNode->attachObject(rocketEnt);

        rocketNode->_update(false, false);

        rocketNode->setScale((DataSizesExtra::ROCKET_SIZE / rocketNode->_getWorldAABB().getSize()));

        rocketNode->translate(radius * cos(step * i),
            -(DataSizesExtra::ENGINE_BASE_SIZE.y / 2 + DataSizesExtra::ROCKET_SIZE.y / 2),
            radius * sin(step * i), Node::TS_WORLD);

        rocketEnt->setMaterialName("examen/rocket");

        if (i % 2 == 0)
        {
            pSys = mSM->createParticleSystem("smokeWhite2" + std::to_string(i), "examen/smokeWhite");
            pSys->setEmitting(true);
            rocketNode->attachObject(pSys);
        }
        else
        {
            pSys = mSM->createParticleSystem("smokeGrey2" + std::to_string(i), "examen/smokeGrey");
            pSys->setEmitting(true);
            rocketNode->attachObject(pSys);
        }
    }

    // coloca el nodo padre del avion
    airplaneNode->translate(0, 500, -2500);
    airplaneNode->pitch(Angle(-90));
    airplaneNode->roll(Angle(90));

    fireSys = mSM->createParticleSystem("fire", "examen/fire");
    fireSys->setEmitting(propulsion);
    airplaneNode->attachObject(fireSys);

    // pared
    SceneNode* wallNode = mSM->getRootSceneNode()->createChildSceneNode("wall");
    MeshManager::getSingleton().createPlane("wall",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Z, 0),
        5000, 5000,
        100, 80,
        true, 1, 1.0, 1.0, Vector3::UNIT_Y);

    Ogre::Entity* wallEnt = mSM->createEntity("wall");
	wallNode->attachObject(wallEnt);
    wallEnt->setMaterialName("examen/shaderChecker");
    wallNode->setPosition(0, 0, -3000);

    // suelo
    SceneNode* floorNode = mSM->getRootSceneNode()->createChildSceneNode("floor");
    MeshManager::getSingleton().createPlane("floor",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        5000, 5000, 
        100, 80,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);

    Ogre::Entity* floorEnt = mSM->createEntity("floor");
	floorNode->attachObject(floorEnt);
    floorEnt->setMaterialName("examen/floor");

    // cielo
    Ogre::Plane plane;
    plane.d = 1000;
    plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
    mSM->setSkyPlane(true, plane, "examen/sky", 1500, 2, true, 1.5, 50, 50);

    //------------------------------------------------------------------------
    // The snowman
    /*
    // Create the main scene node (from root)
    //snowman = mSM->getRootSceneNode()->createChildSceneNode("snowMan");

    //// Create the head
    //head = snowman->createChildSceneNode("head");
    //Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
    //head->attachObject(ent);

    //// Nodes for the head (eyes, nose and mouth)
    //leftEye = head->createChildSceneNode("leftEye");
    //ent = mSM->createEntity("sphere.mesh");
    //leftEye->attachObject(ent);
    //leftEye->setScale(0.1, 0.1, 0.1);
    //leftEye->setPosition(30, 30, 100);

    //rightEye = head->createChildSceneNode("rightEye");
    //ent = mSM->createEntity("sphere.mesh");
    //rightEye->attachObject(ent);
    //rightEye->setScale(0.1, 0.1, 0.1);
    //rightEye->setPosition(-30, 30, 100);

    //nose = head->createChildSceneNode("nose");
    //ent = mSM->createEntity("sphere.mesh");
    //nose->attachObject(ent);
    //nose->setScale(0.1, 0.1, 0.1);
    //nose->setPosition(0, 15, 100);

    //mouth = head->createChildSceneNode("mouth");
    //ent = mSM->createEntity("sphere.mesh");
    //mouth->attachObject(ent);
    //mouth->setScale(0.2, 0.1, 0.1);
    //mouth->setPosition(0, -20, 100);

    //// Create the body
    //body = snowman->createChildSceneNode("bodySnow");
    //ent = mSM->createEntity("sphere.mesh");
    //body->attachObject(ent);
    //body->setScale(1.5, 1.5, 1.5);

    //bellyButton = body->createChildSceneNode("bellyButton");
    //ent = mSM->createEntity("sphere.mesh");
    //bellyButton->attachObject(ent);
    //bellyButton->setScale(0.1, 0.1, 0.1);
    //bellyButton->setPosition(0, 0, 100);

    //// Move the body (and also the belly button)
    //body->setPosition(0, -230, 0);
	*/
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{
    if (sinbad1 != nullptr && sinbad2 != nullptr && !explosion)
    {
	    if (checkCollision(sinbad1->_getWorldAABB(), sinbad2->_getWorldAABB()))
	    {
            if (!explosion) explosion = true;
	    }
    }

    if (explosion)
    {
        if (!done)
        {
            done = true;

            explosionNode->setPosition(returnCollision(sinbad1->_getWorldAABB(), sinbad2->_getWorldAABB()));
            explosionSys->setEmitting(true);
        }
    }

    /*
    // Calculate vertical (Y) displacement using sine wave
    float yOffset = Mathf.Sin(Time.time * frequency) * amplitude;

    // Calculate horizontal (X) movement (simple constant speed)
    float xOffset = Time.time * speed;

    // Set the new position
    transform.position = new Vector3(startPos.x + xOffset, startPos.y + yOffset, startPos.z);
    */

    //estrellaChipNode->translate(0,DataSizes::SHIP_SPEED * evt.timeSinceLastFrame,0);
    //estrellaChipNode->setPosition(DataSizes::SHIP_SPEED * evt.timeSinceLastFrame, sin(DataSizes::SHIP_SPEED * evt.timeSinceLastFrame) * 10, 0);

    //bolaFather->rotate({0,1,0}, Angle(evt.timeSinceLastFrame * DataSizes::SHIP_SPEED));

    //Real o = (evt.timeSinceLastFrame * DataSizes::SHIP_SPEED);
    //std::cout << o << std::endl;
    //float angle = cos(o) + sin(o);
    //nodeBola->yaw(Angle(angle));

    /*
    object.pos.x = object.speed * getElapsedTime();
    object.pos.y = sin(object.speed * getElapsedTime()) * amplitude;
    */
    //bolaAnim->addTime(evt.timeSinceLastFrame);

    centerNode->yaw(Angle(evt.timeSinceLastFrame * (DataSizesExtra::AIRPLANE_SPEED * speedMult)));

    if (rotationMinus)
    {
        airplaneNode->yaw(Angle(evt.timeSinceLastFrame * DataSizesExtra::AIRPLANE_ROTATION));
    }
    else if (rotationPlus)
    {
        airplaneNode->yaw(Angle(evt.timeSinceLastFrame * -DataSizesExtra::AIRPLANE_ROTATION));
    }

    triangleAnimation->addTime(evt.timeSinceLastFrame);

    if (!done)
    {
	    sinbad1->translate(DataSizesExtra::SINBAD_SPEED * evt.timeSinceLastFrame, 0, 0);
	    sinbad2->translate(-DataSizesExtra::SINBAD_SPEED * evt.timeSinceLastFrame, 0, 0);
    }

   /* airplaneNode->setPosition(2500 * Ogre::Math::Cos(Ogre::Degree(angle)), 0,
        2500 * Ogre::Math::Sin(Ogre::Degree(angle)));*/
}

bool IG2App::checkCollision(const AxisAlignedBox& a, const AxisAlignedBox& b)
{
    bool coll = a.intersects(b);
    return coll;
}

Vector3 IG2App::returnCollision(const AxisAlignedBox& a, const AxisAlignedBox& b)
{
    return a.intersection(b).getCenter();
}