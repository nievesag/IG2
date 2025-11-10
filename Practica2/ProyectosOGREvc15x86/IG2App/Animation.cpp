#include "Animation.h"
#include "Constants.h"
#include <iostream>
#include "OgreAnimation.h"
#include "OgreKeyFrame.h"

Animative::Animative(Vector3 a, SceneNode* b, SceneManager* c, String mesh) : IG2Object(a, b, c, mesh)
{
	SceneNode* heroNode = mNode->createChildSceneNode("heroAnimNode");
	floor = new IG2Object(Vector3(0, 50, 0), mNode->createChildSceneNode("floorNode"), c, "cube.mesh");
	hero = new IG2Object(Vector3(0, 100, 0), heroNode, c, "Sinbad.mesh");
	sword1 = new IG2Object(Vector3(-50, 100, 0), mNode->createChildSceneNode("sword1Node"), c, "Sword.mesh");
	sword2 = new IG2Object(Vector3(50, 100, 0), mNode->createChildSceneNode("sword2Node"), c, "Sword.mesh");
	villain = new IG2Object(Vector3(0, 100, -300), mNode->createChildSceneNode("villainAnimNode"), c, "ogrehead.mesh");
	
	floor->setScale(Vector3(5, 0.5, 5));
	floor->setMaterialName("Muro");
	hero->setScale(Vector3(10, 10, 10));
	heroNode->showBoundingBox(true);
	sword1->setScale(Vector3(5, 5, 5));
	sword2->setScale(Vector3(5, 5, 5));

	//Preparando animacion
	animation = mSM->createAnimation("heroWalk", Constants::loopTime);
	animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	track = animation->createNodeTrack(0);
	track->setAssociatedNode(heroNode);
	TransformKeyFrame* kf;

#pragma region HeroKeynodes
	int keyFrame = 0;

	//Inicio
	kf = track->createNodeKeyFrame(0); 
	kf->setTranslate(Vector3(0, 100, -50));
	kf->setScale(Vector3(5, 5, 5));

	//FinDanza
	keyFrame += Constants::danceStep;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(0, 100, -50));
	kf->setScale(Vector3(5, 5, 5));

	//GiroDer
	keyFrame += Constants::turnStep / 2;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(0, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	hero->yaw(Angle(90));
	kf->setRotation(heroNode->getOrientation());

	//AndarDer
	keyFrame += Constants::moveStep / 2;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(50, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	kf->setRotation(heroNode->getOrientation());

	//180Iz
	keyFrame += Constants::turnStep;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(50, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	hero->yaw(Angle(180));
	kf->setRotation(heroNode->getOrientation());

	//AndarIz
	keyFrame += Constants::moveStep;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(-50, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	kf->setRotation(heroNode->getOrientation());

	//180Der
	keyFrame += Constants::turnStep;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(-50, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	hero->yaw(Angle(180));
	kf->setRotation(heroNode->getOrientation());

	//VolverCentro
	keyFrame += Constants::moveStep / 2;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(0, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	kf->setRotation(heroNode->getOrientation());

	//GiroCentro
	keyFrame += Constants::turnStep / 2;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(0, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	hero->yaw(Angle(-90));
#pragma endregion

	heroMoveAnim = mSM->createAnimationState("heroWalk");
	heroMoveAnim->setLoop(true);
	heroMoveAnim->setEnabled(true);
}

Animative::~Animative()
{ 
}

void Animative::updateAnime(Real t)
{
	time += t;
	//cout << time << " : " << hero->getPosition().x << " " << hero->getPosition().y << endl;

	heroMoveAnim->addTime(t);

	if (time > Constants::loopTime)
	{
		time - Constants::loopTime;
	}
}

