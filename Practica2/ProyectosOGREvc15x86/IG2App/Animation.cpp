#include "Animation.h"
#include "Constants.h"
#include <iostream>
#include "OgreAnimation.h"
#include "OgreKeyFrame.h"

Animative::Animative(Vector3 a, SceneNode* b, SceneManager* c, String mesh) : IG2Object(a, b, c, mesh)
{
	SceneNode* heroNode = mNode->createChildSceneNode("heroAnimNode");
	SceneNode* villainNode = mNode->createChildSceneNode("villainAnimNode");
	floor = new IG2Object(Vector3(0, 50, 0), mNode->createChildSceneNode("floorNode"), c, "cube.mesh");
	hero = new IG2Object(Vector3(0, 100, 0), heroNode, c, "Sinbad.mesh");
	sword1 = new IG2Object(Vector3(-50, 100, 0), mNode->createChildSceneNode("sword1Node"), c, "Sword.mesh");
	sword2 = new IG2Object(Vector3(50, 100, 0), mNode->createChildSceneNode("sword2Node"), c, "Sword.mesh");
	villain = new IG2Object(Vector3(0, 100, -300), villainNode, c, "ogrehead.mesh");
	
	floor->setScale(Vector3(5, 0.5, 5));
	floor->setMaterialName("Muro");
	hero->setScale(Vector3(10, 10, 10));
	sword1->setScale(Vector3(5, 5, 5));
	sword2->setScale(Vector3(5, 5, 5));

	//Preparando animacion

#pragma region HeroAnim
	Animation* animation = mSM->createAnimation("heroWalk", Constants::loopTime);
	animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(heroNode);
	TransformKeyFrame* kf;

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
	keyFrame += 3 * Constants::moveStep / 4;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(75, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	kf->setRotation(heroNode->getOrientation());

	//180Iz
	keyFrame += Constants::turnStep;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(75, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	hero->yaw(Angle(180));
	kf->setRotation(heroNode->getOrientation());

	//AndarIz
	keyFrame += Constants::moveStep;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(-25, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	kf->setRotation(heroNode->getOrientation());

	//180Der
	keyFrame += Constants::turnStep;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(-25, 100, -50));
	kf->setScale(Vector3(5, 5, 5));
	hero->yaw(Angle(180));
	kf->setRotation(heroNode->getOrientation());

	//VolverCentro
	keyFrame += Constants::moveStep / 4;
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


	heroMoveAnim = mSM->createAnimationState("heroWalk");
	heroMoveAnim->setLoop(true);
	heroMoveAnim->setEnabled(true);
#pragma endregion

#pragma region VillainAnim
	keyFrame = 0;

	animation = mSM->createAnimation("villainWalk", Constants::loopTime);
	animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	track = animation->createNodeTrack(0);
	track->setAssociatedNode(villainNode);

	//Inicio
	kf = track->createNodeKeyFrame(0);
	kf->setTranslate(Vector3(-170, 100, -50));
	villain->yaw(Angle(90));
	kf->setRotation(villainNode->getOrientation());
	kf->setScale(Vector3(0.7, 0.7, 0.7));

	//FinDanza
	keyFrame += Constants::danceStep;

	//GiroDer
	keyFrame += Constants::turnStep / 2;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(-50, 100, -50));
	kf->setRotation(villainNode->getOrientation());
	kf->setScale(Vector3(0.7, 0.7, 0.7));
	
	//kf->setRotation(heroNode->getOrientation());

	//AndarDer
	keyFrame += 3 * Constants::moveStep / 4;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(25, 100, -50));
	kf->setRotation(villainNode->getOrientation());
	kf->setScale(Vector3(0.7, 0.7, 0.7));

	//180Iz
	keyFrame += Constants::turnStep;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(25, 100, -50));
	villain->yaw(Angle(180));
	kf->setRotation(villainNode->getOrientation());
	kf->setScale(Vector3(0.7, 0.7, 0.7));

	//AndarIz
	keyFrame += Constants::moveStep;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(-75, 100, -50));
	kf->setRotation(villainNode->getOrientation());
	kf->setScale(Vector3(0.7, 0.7, 0.7));

	//180Der
	keyFrame += Constants::turnStep;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(-75, 100, -50));
	villain->yaw(Angle(180));
	kf->setRotation(villainNode->getOrientation());
	kf->setScale(Vector3(0, 0, 0));

	//VolverCentro
	keyFrame += Constants::moveStep / 4;

	//GiroCentro
	keyFrame += Constants::turnStep / 2;
	kf = track->createNodeKeyFrame(keyFrame);
	kf->setTranslate(Vector3(-200, 100, -50));
	kf->setScale(Vector3(0, 0, 0));
	villain->yaw(Angle(-90));


	villainMoveAnim = mSM->createAnimationState("villainWalk");
	villainMoveAnim->setLoop(true);
	villainMoveAnim->setEnabled(true);
#pragma endregion

	runBot = hero->getEntity()->getAnimationState("RunBase");
	runBot->setLoop(true);

	runTop = hero->getEntity()->getAnimationState("RunTop");
	runTop->setLoop(true);

	dance = hero->getEntity()->getAnimationState("Dance");
	dance->setLoop(true);
	dance->setEnabled(true);
}

Animative::~Animative()
{ 
}

void Animative::updateAnime(Real t)
{
	time += t;
	//cout << time << " : " << hero->getPosition().x << " " << hero->getPosition().y << endl;

	heroMoveAnim->addTime(t);
	villainMoveAnim->addTime(t);

	dance->addTime(t);
	runTop->addTime(t);
	runBot->addTime(t);

	if (time > Constants::danceStep && !run)
	{
		run = true;

		dance->setEnabled(false);
		runBot->setEnabled(true);
		runBot->setTimePosition(0.0); 
		runTop->setEnabled(true);
		runTop->setTimePosition(0.0);
	}
	if (time > Constants::loopTime)
	{
		time -= Constants::loopTime;
		run = false;

		dance->setEnabled(true);
		dance->setTimePosition(0.0);
		runBot->setEnabled(false);
		runTop->setEnabled(false);
	}
}

