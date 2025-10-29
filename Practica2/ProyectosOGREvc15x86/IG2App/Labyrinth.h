#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreMeshManager.h>
#include <SDL_keycode.h>
#include <iostream>
#include <vector>
#include "Character.h"
#include "Hero.h"
#include "Enemy.h"

#include "IG2Object.h"
#include "Object.h"

using namespace Ogre;
using namespace std;

class Labyrinth : public OgreBites::InputListener
{
private:
	// ATRIBUTOS
	// --- SceneManager
	SceneManager* _mSM = nullptr;

	// --- Mapa
	SceneNode* _labyrinthNode = nullptr;
	int width = 0, height = 0;
	std::vector<std::vector<Object*>> map;

	// --- Hero
	Hero* _hero = nullptr; // objeto hero
	SceneNode* _heroNode = nullptr; // nodo en escena
	std::pair<int, int> _heroInitPos = { 1,1 }; // posicion inicial para moverle al perder
	std::pair<int, int> _heroPos = { 1,1 }; // posicion del hero en coordenadas de bloques

	// --- Enemies
	std::vector<Enemy*> _enemies; // vector de objetos enemigo
	std::vector<SceneNode*> _enemiesNode; // vector de nodos enemigo
	std::vector<std::pair<int, int>> _enemiesPos; // posicion de los enemigos en coordenadas de bloques
	int enemyCount = 0;

	// --- Textures
	std::string matwall;
	std::string matfloor;

	// --- UI
	OgreBites::Label* stageLabel = nullptr;
	OgreBites::TextBox* infoTextBox = nullptr;

	// --- Luces
	std::string lightType;
	Ogre::Light* _light = nullptr;
	Ogre::SceneNode* _lightNode = nullptr;

	// --- Game info
	int stage = 1;
	int points = 0;

	// METODOS
	// --- Update
	void update();
	void updateHero();
	void updateUI();
	void updateEnemies();
	void updateLuz();

	// --- Auxiliares
	void DebugMap();
	pair<int, int> vectorToMap(Vector3 pos); // para pasar a coordenadas de bloques

	// --- Check...
	bool checkMove(pair<int, int> pos, pair<int, int> dir); // si delante tiene empty
	bool checkForward(pair<int, int> pos, pair<int, int> dir);
	bool checkCentered(pair<int, int> pos, Character* c);
	bool checkCentered2(pair<int, int> pos, Character * c); // intento de mejorar checkCentered
	bool checkCentered3(pair<int, int> pos, Character * c); // intento de mejorar checkCentered por ultima vez
	bool checkCollision();
	std::pair<int,int> checkCrossroads(pair<int, int> pos, pair<int, int> dir);

	// --- Suelo
	void createFloor();

	// --- Luces
	void createLuz();

public:
	Labyrinth() = default;

	void setupLabyrinth(SceneManager* mSM, Hero* hero, SceneNode* heroscn, std::vector<Enemy*> enemies, std::vector<SceneNode*> enemiesNode);
	void readFile(string fileName); // leer el fichero

	void registerUI(OgreBites::Label* label, OgreBites::TextBox* textbox); // registra UI

	virtual void frameRendered(const Ogre::FrameEvent& evt); // update

	// --- Setters
	void setStage(int i) { stage = i; }
	void nextStage() { stage++; }
	void addPoints(int i) { points += i; }

	// --- Getters
	int getStage() { return stage; }
	int getPoints() { return points; }
};