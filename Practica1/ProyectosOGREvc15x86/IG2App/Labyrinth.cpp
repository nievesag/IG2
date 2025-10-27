#include "Labyrinth.h"
#include "Wall.h"
#include "Empty.h"
#include "Constants.h"
#include "Fisher.h"

using namespace std;

// --------- INIT
void Labyrinth::setupLabyrinth(SceneManager* mSM,
    Hero* hero, SceneNode* heroscn,
    std::vector<Enemy*> enemies, std::vector<SceneNode*> enemiesNode)
{
    _mSM = mSM; // manager
    _labyrinthNode = _mSM->getRootSceneNode()->createChildSceneNode("nLabMain"); // nodo laberinto

    _hero = hero;           // objeto hero
    _heroNode = heroscn;    // nodo heroe

    _enemies = enemies;
    _enemiesNode = enemiesNode;
}

void Labyrinth::readFile(string fileName)
{
    ifstream entrada(fileName);

    if (!entrada.is_open())
    {
        cout << "Error abriendo archivo\n";
        return;
    }

    // para poder hacer cin para leer el archivo
    auto cinbuf = cin.rdbuf(entrada.rdbuf());

    cin >> height >> width;  // mapa

    cin >> matwall >> matfloor; // materiales

    cin >> lightType; // luces

    string fila;
    for (int i = 0; i < height; i++)
    {
        cin >> fila;

        std::vector<Object*> line;

        for (int j = 0; j < width; j++)
        {
            string id = to_string(i) + "-" + to_string(j) + "cube";
            // MURO
            if (fila[j] == 'x')
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                Object* muro = new Wall(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize), node, _mSM, "cube.mesh");
                muro->setMaterialName(matwall);
                line.push_back(muro);
            }
            // VACIO
            else if (fila[j] == 'o')
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                Object* vacio = new Empty(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize), node, _mSM);
                line.push_back(vacio);
            }
            // HERO
            else if (fila[j] == 'h')
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                line.push_back(new Empty(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize), node, _mSM)); // vacio en el mapa

                _heroPos.first = j;
                _heroPos.second = i;

                _heroInitPos.first = j;
                _heroInitPos.second = i;

                _hero->setPosition(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize));
            }
            // ENEMIGOS
            else if (fila[j] == 'v')
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                line.push_back(new Empty(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize), node, _mSM)); // vacio en el mapa

                _enemiesPos.push_back({ j,i });
                _enemies[enemyCount]->setPosition(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize));
                enemyCount++;
            }
        }

        map.push_back(line);
    }
    //DebugMap();

    cin.rdbuf(cinbuf);

    createFloor();
    createLuz();
}

void Labyrinth::registerUI(OgreBites::Label* label, OgreBites::TextBox* textbox)
{
    stageLabel = label;
    infoTextBox = textbox;
}

void Labyrinth::createFloor()
{
    MeshManager::getSingleton().createPlane("floor",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        width * Constants::mapSize, height * Constants::mapSize, 100, 80,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);

    Ogre::Entity* plane = _mSM->createEntity("floor");
    SceneNode* nodePlane = _mSM->getRootSceneNode()->createChildSceneNode("floor");
    nodePlane->attachObject(plane);
    nodePlane->setPosition(Vector3((width * Constants::mapSize) / 2, -Constants::mapSize / 2, (height * Constants::mapSize) / 2));
    plane->setMaterialName(matfloor);
}

void Labyrinth::createLuz()
{
    _light = _mSM->createLight("Luzmap");
    _light->setDiffuseColour(0.75, 0.75, 0.75);
    _lightNode = _mSM->getRootSceneNode()->createChildSceneNode("nLuzmap");
    _lightNode->attachObject(_light);

    if (lightType == "point")
    {
        _light->setType(Ogre::Light::LT_POINT);
        //_light->setAttenuation(Constants::mapSize * 10, );
        Vector3 hPos = _hero->getPosition();
        _lightNode->setPosition(Ogre::Vector3(hPos.x, hPos.y + Constants::mapSize / 2, hPos.z));
    }
    else if (lightType == "spotlight")
    {
        _light->setType(Ogre::Light::LT_SPOTLIGHT);
        _lightNode->setPosition(Ogre::Vector3(950, 2500, 1900));
        _lightNode->lookAt(_hero->getPosition(), Ogre::Node::TS_WORLD);
        _light->setSpotlightInnerAngle(Ogre::Angle(Constants::sptInner));
        _light->setSpotlightOuterAngle(Ogre::Angle(Constants::sptOuter));
        _light->setSpotlightFalloff(Constants::sptFalloff);
    }
    else
    {
        _light->setType(Ogre::Light::LT_DIRECTIONAL);
        _lightNode->setDirection(Ogre::Vector3(-0.5, -0.5, -0.5));
    }


}

void Labyrinth::DebugMap()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << "x: " << map[i][j]->getPosition().x << "  z: " << map[i][j]->getPosition().z << "\n";

        }
        cout << "\n";
    }
}

// --------- UPDATE
void Labyrinth::frameRendered(const Ogre::FrameEvent& evt)
{
    update();
}

void Labyrinth::update()
{
    bool heroHit = checkCollision();
    if (heroHit)
    {
        _hero->decreaseLives();

        if (_hero->getLives() > 0)
        {
            _heroPos.first = _heroInitPos.first;
            _heroPos.second = _heroInitPos.second;

            _hero->setPosition(Vector3(_heroPos.first * Constants::mapSize, 0, _heroPos.second * Constants::mapSize));
        }
    }

    updateHero();
    updateEnemies();
    updateUI();
    updateLuz();
}

void Labyrinth::updateHero()
{
    if (_hero->getLives() <= 0)
    {
        std::cout << "FIN DE JUEGO" << endl;
        // shutdown application
    }

    Vector3 wantToMove = _hero->getLastPosibleDirection();
    pair<int, int> dirToMove = { wantToMove.x, wantToMove.z };

    Vector3 isMoving = _hero->getCurrentDirection();
    pair<int, int> dirMoving = { isMoving.x, isMoving.z };

    Vector3 realPos = _hero->getPosition();
    _heroPos = vectorToMap(realPos);

    bool turn = checkMove(_heroPos, dirToMove);
    bool movable = checkForward(_heroPos, dirMoving, realPos);
    bool centered = checkCentered(_heroPos, _hero);

    _heroPos.first += dirMoving.first;
    _heroPos.second += dirMoving.second;

    pair<int, int> nextPos = { _heroPos.first + dirToMove.first ,_heroPos.first + dirToMove.second };

    if (centered)
    {
        if (turn)
        {
            _heroPos = nextPos;
            if (isMoving != Vector3(0, 0, 0))
                _heroNode->rotate(_hero->quaternionRotateCharacter());
            _hero->moveCharacter();
        }
        else if (!movable)
            _hero->stopCharacter();
    }
}

void Labyrinth::updateUI()
{
    stageLabel->setCaption("Stage: " + StringConverter::toString(stage));
    infoTextBox->setText("Lives: " + StringConverter::toString(_hero->getLives()) + "\n" +
        "Points: " + StringConverter::toString(getPoints()));
}

void Labyrinth::updateEnemies()
{
    int i = 0;
    for (auto e : _enemies)
    {
        // TODO: gestionar muertes
        pair<int, int> nextDir = checkCrossroads(vectorToMap(e->getPosition()), { e->getCurrentDirection().x, e->getCurrentDirection().z });

    	e->setLastPosibleDirection({ Ogre::Real(nextDir.first), 0, Ogre::Real(nextDir.second) });

        Vector3 wantToMove = e->getLastPosibleDirection();
        pair<int, int> dirToMove = { wantToMove.x, wantToMove.z };

        Vector3 isMoving = e->getCurrentDirection();
        pair<int, int> dirMoving = { isMoving.x, isMoving.z };

        Vector3 realPos = e->getPosition();
        _enemiesPos[i] = vectorToMap(realPos);

        bool turn = checkMove(_enemiesPos[i], dirToMove);
        bool movable = checkForward(_enemiesPos[i], dirMoving, realPos);
        bool centered = checkCentered(_enemiesPos[i], _enemies[i]);

        _enemiesPos[i].first += dirMoving.first;
        _enemiesPos[i].second += dirMoving.second;

        pair<int, int> nextPos = { _enemiesPos[i].first + dirToMove.first ,_enemiesPos[i].first + dirToMove.second };

        if (centered)
        {
            if (turn)
            {
                _enemiesPos[i] = nextPos;
                if (isMoving != Vector3(0, 0, 0))
                    _enemiesNode[i]->rotate(e->quaternionRotateCharacter());
					
                e->moveCharacter();
            }
            else if (!movable)
                e->stopCharacter();
        }

        ++i; // seguir buscando
    }
}

void Labyrinth::updateLuz()
{
    if (_lightNode != nullptr)
    {
        if (lightType == "point")
        {
            Vector3 hPos = _hero->getPosition();
            _lightNode->setPosition(Ogre::Vector3(hPos.x, hPos.y + Constants::mapSize, hPos.z));
        }
        else if (lightType == "spotlight")
            _lightNode->lookAt(_hero->getPosition(), Ogre::Node::TS_WORLD);
    }
}

// --------- AUX
pair<int, int> Labyrinth::vectorToMap(Vector3 pos)
{
    return pair<int, int>(round(pos.x / Constants::mapSize), round(pos.z / Constants::mapSize));
}

// --------- CHECKS
bool Labyrinth::checkMove(pair<int, int> pos, pair<int, int> dir)
{
    int x = pos.first + dir.first;
    int z = pos.second + dir.second;

    return map[z][x]->isEmpty();
}

bool Labyrinth::checkForward(pair<int, int> pos, pair<int, int> dir, Vector3 realPos)
{
    if (!checkMove(pos, dir))
    {
        if (dir.first > 0) // se est� moviendo hacia la derecha
            return false;
        if (dir.first < 0) // se est� moviendo hacia la izquierda
            return false;
        if (dir.second > 0) // se est� moviendo hacia abajo
            return false;
        if (dir.second < 0) // se est� moviendo hacia abajo
            return false;
    }

    return true;
}

bool Labyrinth::checkCentered(pair<int, int> pos, Character* c)
{
    float worldSize = Constants::mapSize;
    Vector3 squareCenter(pos.first * worldSize, 0, pos.second * worldSize);

    float xS = squareCenter.x;
    int xH = c->getPosition().x;

    float zS = squareCenter.z;
    int zH = c->getPosition().z;

    return ((xS < xH + 5) && (xS > xH - 5)) && ((zS < zH + 5) && (zS > zH - 5));
}

bool Labyrinth::checkCollision()
{
    // colision hero-enemigos
    for (auto e : _enemies)
    {
        if (e->checkCharacterCollision(_hero->getAABB()))
        {
            return true;
        }
    }

    return false;
}

std::pair<int, int> Labyrinth::checkCrossroads(pair<int, int> pos, pair<int, int> dir)
{
    /*
    Chuleta direcciones:

             (0,-1)
               ^
               |
    (-1,0) <---+---> (1,0)
               |
               v
             (0,1)
    */

    std::vector<pair<int, int>> posibleDirections; // vector de direcciones posibles salvo 180

    // -- arriba
    int xAr = pos.first + Vector3::NEGATIVE_UNIT_Z.x;
    int zAr = pos.second + Vector3::NEGATIVE_UNIT_Z.z;

    //cout << dir.second << endl;
    //cout << pos.first << " + " << Vector3::NEGATIVE_UNIT_Z.x << " = " << xAr << endl;
    //cout << pos.second << " + " << Vector3::NEGATIVE_UNIT_Z.z << " = " << zAr << endl; 

    if (zAr > 0 // si no se sale
        && dir.second != 1  // si no es el giro de 180 (no vas hacia abajo)
        && map[zAr][xAr]->isEmpty()) // y esta vacia
    {
        //cout << "ARRIBA OPT " << zAr << " " << dir.second << " " << map[zAr][xAr]->isEmpty() << endl;

        // arriba como posible direccion
        posibleDirections.push_back({ Vector3::NEGATIVE_UNIT_Z.x , Vector3::NEGATIVE_UNIT_Z.z });
    }

    // -- abajo
    int xAb = pos.first + Vector3::UNIT_Z.x;
    int zAb = pos.second + Vector3::UNIT_Z.z;

    if (zAb < map.size() // si no se sale
        && dir.second != -1  // si no es el giro de 180 (no vas hacia arriba)
        && map[zAb][xAb]->isEmpty()) // y esta vacia
    {
        //cout << "ABJ OPT " << zAr << " " << dir.second << " " << map[zAr][xAr]->isEmpty() << endl;

        // abajo como posible direccion
        posibleDirections.push_back({ Vector3::UNIT_Z.x , Vector3::UNIT_Z.z });
    }

    // -- izquierda
    int xIz = pos.first + Vector3::NEGATIVE_UNIT_X.x;
    int zIz = pos.second + Vector3::NEGATIVE_UNIT_X.z;


    //cout << dir.second << endl;
    //cout << pos.first << " + " << Vector3::NEGATIVE_UNIT_Z.x << " = " << xAr << endl;
    //cout << pos.second << " + " << Vector3::NEGATIVE_UNIT_Z.z << " = " << zAr << endl; 

    if (xIz > 0 // si no se sale
        && dir.first != 1  // si no es el giro de 180 (no vas hacia derecha)
        && map[zIz][xIz]->isEmpty()) // y esta vacia
    {
        //cout << "IZQ OPT " << zAr << " " << dir.second << " " << map[zAr][xAr]->isEmpty() << endl;
        // izquierda como posible direccion
        posibleDirections.push_back({ Vector3::NEGATIVE_UNIT_X.x , Vector3::NEGATIVE_UNIT_X.z });
    }

    // -- derecha
    int xDe = pos.first + Vector3::UNIT_X.x;
    int zDe = pos.second + Vector3::UNIT_X.z;

    if (xDe < map.size()
        && dir.first != -1  // si no es el giro de 180 (no vas hacia izquierda)
        && map[zDe][xDe]->isEmpty()) // y esta vacia
    {
        // derecha como posible direccion
        posibleDirections.push_back({ Vector3::UNIT_X.x , Vector3::UNIT_X.z });
    }

    // calcular siguiente direccion
    std::pair<int, int> nextDir;

    if (posibleDirections.size() > 1) // si hay mas de una direccion posible
    {
        //cout << "!!! ALEATORIA" << endl;
        int randDir = rand() % posibleDirections.size(); // aleatoria
        nextDir = posibleDirections[randDir];
    }
    else if (posibleDirections.size() == 0) // si se queda en una encrucijada
    {
        //cout << "!!! ENCRUCIJADA" << endl;
        nextDir = { -dir.first, -dir.second }; // giro 180
    }
    else // si solo hay una direccion posible
    {
        //cout << "!!! RECTO" << endl;
        nextDir = posibleDirections.front(); // es esa
    }

    return nextDir;
}