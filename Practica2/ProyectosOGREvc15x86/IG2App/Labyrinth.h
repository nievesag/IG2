#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreMeshManager.h>
#include <OgreParticleSystem.h>
#include <SDL_keycode.h>
#include <iostream>
#include <vector>
#include "Character.h"
#include "Hero.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Animation.h"

#include "IG2Object.h"
#include "Object.h"
#include "SmokeZone.h"

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
	std::pair<int, int> _heroInitPos = { 1,1 }; // posicion inicial para moverle al perder
	std::pair<int, int> _heroPos = { 1,1 }; // posicion del hero en coordenadas de bloques

	// --- Enemies
	std::vector<Enemy*> _enemies; // vector de objetos enemigo
	std::vector<std::pair<int, int>> _enemiesPos; // posicion de los enemigos en coordenadas de bloques
	int enemyCount = 0;

	// --- Bombs
	int currentBombs = 0;
	//std::vector<Bomb*> _bombs; // vector de bombas
	std::queue<Bomb*> _bombsPool; // pool de bombas

	std::vector<std::pair<int, int>> _affectedTiles; // casillas afectadas en este update
	std::queue<SmokeZone*> smokePSysPool; // pool de sistemas de particulas de humo (? una pila)
	Ogre::ParticleSystem* sysHumo = nullptr;

	void placeBomb(Vector3 pos);
	void placeSmoke(std::vector<std::pair<int, int>> affectedTiles);
	void explodeCharacter(Character* c);

	// inicializar pools
	void generateBombs();
	void generateSmokes();

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

	// Camara
	SceneNode* mCamNode;

	// --- Animacion
	bool playingAnim;
	Animative* mAnim;


	// METODOS
	// --- Update
	void update(Real t);
	void updateHero();
	void updateUI();
	void updateEnemies();
	void updateLuz();
	void updateBombs(Real t);
	void clearMap();

	// --- Animación Inicial
	void updateAnim(Real t);
	void activateGame();

	// --- Auxiliares
	void DebugMap();
	pair<int, int> vectorToMap(Vector3 pos); // para pasar a coordenadas de bloques
	Vector3 mapToVector(pair<int, int>  pos); // para pasar a coordenadas de mundo

	// --- Check...
	bool checkMove(pair<int, int> pos, pair<int, int> dir); // si delante tiene empty
	bool checkForward(pair<int, int> pos, pair<int, int> dir);
	bool checkCentered(pair<int, int> pos, Character * c); // saber si estas en el centro
	bool checkCollision();
	std::pair<int,int> checkCrossroads(pair<int, int> pos, pair<int, int> dir);

	// --- Bombas
	void setAffectedTiles(pair<int, int> bombPos);

	// --- Suelo
	void createFloor();

	// --- Luces
	void createLuz();

public:
	Labyrinth() = default;

	void setupLabyrinth(SceneManager* mSM, Hero* hero, SceneNode* heroscn, std::vector<Enemy*> enemies, std::vector<SceneNode*> enemiesNode, SceneNode* cam);
	void readFile(string fileName); // leer el fichero

	void registerUI(OgreBites::Label* label, OgreBites::TextBox* textbox); // registra UI

	virtual void frameRendered(const Ogre::FrameEvent& evt); // update
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	// --- Setters
	void setStage(int i) { stage = i; }
	void nextStage() { stage++; }
	void addPoints(int i) { points += i; }

	// --- Getters
	int getStage() { return stage; }
	int getPoints() { return points; }
};