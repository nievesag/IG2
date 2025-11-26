#include "Labyrinth.h"
#include "Wall.h"
#include "Empty.h"
#include "Constants.h"
#include "Fisher.h"

using namespace std;

// --------- INIT
void Labyrinth::setupLabyrinth(SceneManager* mSM,
    Hero* hero, SceneNode* heroscn,
    std::vector<Enemy*> enemies, std::vector<SceneNode*> enemiesNode,
    SceneNode* cam)
{
    _mSM = mSM; // manager
    _labyrinthNode = _mSM->getRootSceneNode()->createChildSceneNode("nLabMain"); // nodo laberinto

    _hero = hero;           // objeto hero

    _enemies = enemies;

    playingAnim = true;

    mCamNode = cam;
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

    mAnim = new Animative(Constants::animPos, _mSM->getRootSceneNode()->createChildSceneNode("animNode"), _mSM, "cube.mesh");
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

void Labyrinth::createSky()
{
    Ogre::Plane plane;
    plane.d = 20;
    plane.normal = Ogre::Vector3::UNIT_Z + Ogre::Vector3::UNIT_Y;
    _mSM->setSkyPlane(true, plane, "Examples/SpaceSkyPlane", 1, 1, true, 1.5, 50, 50);
}

void Labyrinth::createLuz()
{
    _mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5, 1.0));
    _light = _mSM->createLight("Luzmap");
    _light->setDiffuseColour(0.9, 0.9, 0.9);
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
bool Labyrinth::keyPressed(const OgreBites::KeyboardEvent& evt) 
{
    if (evt.keysym.sym == SDLK_b) // darle a la b
    {
        placeBomb(_hero->getPosition());
    }
    if (evt.keysym.sym == SDLK_l)
    {
        activateGame();
    }

    return true;
}

void Labyrinth::frameRendered(const Ogre::FrameEvent& evt)
{
    if (!playingAnim)
        update(evt.timeSinceLastEvent);
    else
        updateAnim(evt.timeSinceLastFrame);
}

void Labyrinth::update(Real t)
{
    updateBombs(t);
    updateSmokeZones(t);

    bool heroHit = checkCollision();
    if (heroHit)
    {
        manageHeroDeath();
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

    bool canMove = checkMove(_heroPos, dirToMove);      // si se puede mover hacia delante
    bool movable = checkForward(_heroPos, dirMoving);   // si se puede mover
    bool centered = checkCentered(_heroPos, _hero);     // si esta centrado

    _heroPos.first += dirMoving.first;
    _heroPos.second += dirMoving.second;

    pair<int, int> nextPos = { _heroPos.first + dirToMove.first ,_heroPos.first + dirToMove.second };

    if (centered)
    {
        if (canMove)
        {
            _heroPos = nextPos;
            if (wantToMove != Vector3(0, 0, 0))
                _hero->yaw(_hero->yawDirection());
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
        if (e->getAlive())
        {
            _enemiesPos[i] = vectorToMap(e->getPosition());
            if (checkCentered(_enemiesPos[i], _enemies[i]))
            {
                // calcula la nueva direccion
                pair<int, int> nextDir = checkCrossroads(vectorToMap(e->getPosition()), { e->getCurrentDirection().x, e->getCurrentDirection().z });
                e->setLastPosibleDirection({ Ogre::Real(nextDir.first), 0, Ogre::Real(nextDir.second) });

                // calcula la nueva posicion
                pair<int, int> nextPos = { _enemiesPos[i].first + nextDir.first ,_enemiesPos[i].first + nextDir.second };
                _enemiesPos[i] = nextPos;

                // rota y mueve
                _enemies[i]->yaw(e->yawDirection());
                e->moveCharacter();
            }
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

void Labyrinth::updateBombs(Real t)
{
    int actives = 0;

    for (int i = 0; i < Constants::maxBombs; ++i) 
    {
        Bomb* b = _bombsPool.front();

        if (b->getActive())
        {
            actives++;
            b->update(t);

            if (b->getExploded())
            {
                // marca las casillas como afectadas
                setAffectedTiles(vectorToMap(b->getPosition()));
                b->clearBomb();
                explodeCharacters();
            }
        }

        _bombsPool.pop();
        _bombsPool.push(b);
    }

    currentBombs = actives;
}

void Labyrinth::updateSmokeZones(Real t)
{
    for (int i = 0; i < Constants::maxSmokes; ++i)
    {
        SmokeZone* z = smokesPool.front();

        if (z->getActive())
        {
            z->update(t);

            if (z->getExpired())
            {
                z->clearSmoke();
            }
        }

        smokesPool.pop();
        smokesPool.push(z);
    }
}

void Labyrinth::updateAnim(Real t)
{
    mAnim->updateAnime(t);
}

void Labyrinth::activateGame()
{
    _hero->setActive(true);

    for (auto ene : _enemies)
    {
        ene->setActive(true);
    }

    playingAnim = false;
    mAnim->setActive(false);

    mCamNode->setPosition(950, 2500, 1900);
    mCamNode->lookAt(Ogre::Vector3(950, 0, 950), Ogre::Node::TS_WORLD);

    createSky();

    generateBombs();
    generateSmokes();
}

// --------- AUX
void Labyrinth::setAffectedTiles(pair<int, int> bombPos)
{
    // Humo de la bomba
    SmokeZone* z = smokesPool.front();
    smokesPool.pop();
    smokesPool.push(z);
    z->createSmoke();
    z->setPosition(mapToVector(bombPos));

    for (int i = 0; i < 4; i++) // recorrer las 4 direcciones
    {
        pair<int, int> searching = bombPos;
        int tilesSearched = 0;

        bool continueSearch = true;
	    while (continueSearch &&
            tilesSearched < Constants::bombReach)  // mientras puedas en esa direccion y queden casillas
	    {
            // si no puedo seguir
            if (!checkMove(searching, { Constants::DirectionsArray[i].x , Constants::DirectionsArray[i].z }))
            {
                continueSearch = false;
            }
            // si puedo seguir
            else
            {
                // avanzo a la siguiente a buscar
                searching.first += Constants::DirectionsArray[i].x;
                searching.second += Constants::DirectionsArray[i].z;

                _affectedTiles.push_back(searching);

                // Coloca humos
                SmokeZone* z = smokesPool.front();
                smokesPool.pop();
                smokesPool.push(z);
                z->createSmoke();
                z->setPosition(mapToVector(searching));

                tilesSearched++;
            }
	    }
    }
}

void Labyrinth::manageHeroDeath()
{
    _hero->stopCharacter();
    _hero->decreaseLives();

    if (_hero->getLives() > 0)
    {
        _heroPos.first = _heroInitPos.first;
        _heroPos.second = _heroInitPos.second;

        _hero->setPosition(Vector3(_heroPos.first * Constants::mapSize, 0, _heroPos.second * Constants::mapSize));
    }
}

void Labyrinth::placeBomb(Vector3 pos)
{
    if (currentBombs < Constants::maxBombs) // se pueden poner bombas 
    {
        Bomb* b = _bombsPool.front();
        _bombsPool.push(b);
        _bombsPool.front()->setPosition(pos);
        _bombsPool.front()->createBomb();
        _bombsPool.pop();
    }
}

void Labyrinth::generateBombs()
{
    for (int i = 0; i < Constants::maxBombs; i++)
    {
        SceneNode* node = _labyrinthNode->createChildSceneNode("bomb" + std::to_string(i));
        Bomb* bomb = new Bomb({0,0,0}, node, _mSM, "sys" + std::to_string(i));
        _bombsPool.push(bomb);
        bomb->setVisible(false);
    }
}

void Labyrinth::generateSmokes()
{
    // pool size = ((4 dir * x casillas por dir)*maxBombs) + 1(pos bomba)
    int size = Constants::maxSmokes;
    for (int i = 0; i < size; i++)
    {
        SceneNode* node = _labyrinthNode->createChildSceneNode("zone" + std::to_string(i));
        SmokeZone* z = new SmokeZone({ 0,0,0 }, node, _mSM, "smoke" + std::to_string(i));
        smokesPool.push(z);
    }
}

void Labyrinth::explodeCharacters()
{
    // colision hero-bomba
    auto it = find(_affectedTiles.begin(), _affectedTiles.end(), _heroPos);
    if (it != _affectedTiles.end())
    {
        cout << "explota heroe" << endl;
        manageHeroDeath();
    }

    // colision enemigos-bomba
    for (int i = 0; i < _enemiesPos.size(); i++)
    {
        auto it = find(_affectedTiles.begin(), _affectedTiles.end(), _enemiesPos[i]);
        if (it != _affectedTiles.end())
        {
            cout << "explota enemigo " << i << endl;

            _enemies[i]->setActive(false);
            _enemies[i]->setVisible(false);
        }
    }

    _affectedTiles.clear();
}

void Labyrinth::clearMap()
{
    // despues de afectar a quien tenga que afectar se resetea
    _affectedTiles.clear();
}

pair<int, int> Labyrinth::vectorToMap(Vector3 pos)
{
    return pair<int, int>(round(pos.x / Constants::mapSize), round(pos.z / Constants::mapSize));
}

Vector3 Labyrinth::mapToVector(pair<int, int> pos)
{
    return { (Real)pos.first * Constants::mapSize,0 ,(Real)pos.second * Constants::mapSize };
}

// --------- CHECKS
bool Labyrinth::checkMove(pair<int, int> pos, pair<int, int> dir)
{
    int x = pos.first + dir.first;
    int z = pos.second + dir.second;

    return map[z][x]->isEmpty();
}

bool Labyrinth::checkForward(pair<int, int> pos, pair<int, int> dir)
{
    if (!checkMove(pos, dir))
    {
        if (dir.first > 0) // se está moviendo hacia la derecha
            return false;
        if (dir.first < 0) // se está moviendo hacia la izquierda
            return false;
        if (dir.second > 0) // se está moviendo hacia abajo
            return false;
        if (dir.second < 0) // se está moviendo hacia abajo
            return false;
    }

    return true;
}

bool Labyrinth::checkCentered(pair<int, int> pos, Character* c)
{
    bool centered = false;
    Vector3 dir = c->getCurrentDirection();

    if (c->getCurrentDirection() != Vector3::ZERO)
    {
        Vector3 targetCenter = Vector3(pos.first, 0, pos.second) * Constants::mapSize;
        Vector3 lastPos = c->getLastPos();
        Vector3 position = c->getPosition();

        if (lastPos.x < targetCenter.x && targetCenter.x < position.x && dir == Vector3::UNIT_X)
            centered = true;

        if (lastPos.z < targetCenter.z && targetCenter.z < position.z && dir == Vector3::UNIT_Z)
            centered = true;

        if (lastPos.x > targetCenter.x && targetCenter.x > position.x && dir == Vector3::NEGATIVE_UNIT_X)
            centered = true;

        if (lastPos.z > targetCenter.z && targetCenter.z > position.z && dir == Vector3::NEGATIVE_UNIT_Z)
            centered = true;
    }
    else 
    {
        centered = true;
    }

    return centered;
}

bool Labyrinth::checkCollision()
{
    // colision hero-enemigos
    for (auto e : _enemies)
    {
        if (e->getActive())
        {
            if (e->checkCharacterCollision(_hero->getAABB()))
            {
                return true;
            }
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

    if (zAr > 0 // si no se sale
        && dir.second != 1  // si no es el giro de 180 (no vas hacia abajo)
        && map[zAr][xAr]->isEmpty()) // y esta vacia
    {
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
        // abajo como posible direccion
        posibleDirections.push_back({ Vector3::UNIT_Z.x , Vector3::UNIT_Z.z });
    }

    // -- izquierda
    int xIz = pos.first + Vector3::NEGATIVE_UNIT_X.x;
    int zIz = pos.second + Vector3::NEGATIVE_UNIT_X.z;

    if (xIz > 0 // si no se sale
        && dir.first != 1  // si no es el giro de 180 (no vas hacia derecha)
        && map[zIz][xIz]->isEmpty()) // y esta vacia
    {
        // izquierda como posible direccion
        posibleDirections.push_back({ Vector3::NEGATIVE_UNIT_X.x , Vector3::NEGATIVE_UNIT_X.z });
    }

    // -- derecha
    int xDe = pos.first + Vector3::UNIT_X.x;
    int zDe = pos.second + Vector3::UNIT_X.z;

    if (xDe < map.size() // si no se sale
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
        int randDir = rand() % posibleDirections.size(); // aleatoria entre 0 y size-1
        nextDir = posibleDirections[randDir];
    }
    else if (posibleDirections.size() == 0) // si se queda en una encrucijada
    {
        nextDir = { -dir.first, -dir.second }; // giro 180
    }
    else // si solo hay una direccion posible
    {
        nextDir = posibleDirections.front(); // es esa
    }

    return nextDir;
}