#include "Labyrinth.h"
#include "Wall.h"
#include "Empty.h"
#include "Constants.h"

using namespace std;

// --------- INIT
void Labyrinth::setupLabyrinth(SceneManager* mSM, Hero* hero, SceneNode* heroscn)
{
    _mSM = mSM;
    _labyrinthNode = _mSM->getRootSceneNode()->createChildSceneNode("nLabMain");
    _hero = hero;
    _heroNode = heroscn;
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

    cin >> height >> width; 

    cin >> matwall >> matfloor;

    string fila;
    for (int i = 0; i < height; i++) 
    {
        cin >> fila;

        std::vector<Object*> line;

        for (int j = 0; j < width; j++) 
        {
            string id = to_string(i) + "-" + to_string(j) + "cube";
            //cout << id << "\n";
            // creamos el muro
            if (fila[j] == 'x') 
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                Object* muro = new Wall(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize), node, _mSM, "cube.mesh");
                muro->setMaterialName(matwall);
                line.push_back(muro);
            }
            else if (fila[j] == 'o')
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                Object* vacio = new Empty(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize), node, _mSM);
                line.push_back(vacio);
                //std::cout << "x: " << j << " z: " << i << "\n";
                //std::cout << line[j]->isEmpty() << "\n";
            }
            else if (fila[j] == 'h') 
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                line.push_back(new Empty(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize), node, _mSM)); // vacio en el mapa
                _heroPos.first = j;
                _heroPos.second = i;
                _hero->setPosition(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize));
            }
            else if (fila[j] == 'v') 
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                line.push_back(new Empty(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize), node, _mSM)); // vacio en el mapa
            }
        }

        map.push_back(line);
    }
    //DebugMap();

    cin.rdbuf(cinbuf);

    createFloor();
}

void Labyrinth::registerUI(OgreBites::Label* label, OgreBites::TextBox* textbox)
{
    stageLabel = label;
    infoTextBox = textbox;
}

void Labyrinth::createFloor()
{
    // >>>>>>>> apartado 4:
    MeshManager::getSingleton().createPlane("floor",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        width*Constants::mapSize, height * Constants::mapSize, 100, 80,
        true, 1, 1.0, 1.0, Vector3::UNIT_Z);
    Ogre::Entity* plane = _mSM->createEntity("floor");
    SceneNode* nodePlane = _mSM->getRootSceneNode()->createChildSceneNode("floor");
    nodePlane->attachObject(plane);
    nodePlane->setPosition(Vector3((width * Constants::mapSize)/2, -Constants::mapSize/2, (height * Constants::mapSize)/2));
    plane->setMaterialName(matfloor);
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
    updateHero();
    updateEnemies();
    updateUI();
}

void Labyrinth::updateHero()
{
    Vector3 wantToMove = _hero->getLastPosibleDirection();
    pair<int, int> dirToMove = { wantToMove.x, wantToMove.z };

    Vector3 isMoving = _hero->getCurrentDirection();
    pair<int, int> dirMoving = { isMoving.x, isMoving.z };

    Vector3 realPos = _hero->getPosition();
    _heroPos = vectorToMap(realPos);
    //std::cout << _heroPos.first << " " << _heroPos.second << "\n";

    bool turn = checkMove(_heroPos, dirToMove);
    bool movable = checkForward(_heroPos, dirMoving, realPos);
    bool centered = checkCentered(_heroPos);

    _heroPos.first += dirMoving.first;
    _heroPos.second += dirMoving.second;

    pair<int, int> nextPos = { _heroPos.first + dirToMove.first ,_heroPos.first + dirToMove.second };

    if (centered)
    {
        if (turn) 
        {
            _heroPos = nextPos;
            if(isMoving != Vector3(0, 0, 0))
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
							"Points: " + StringConverter::toString(_hero->getLives()));
}

void Labyrinth::updateEnemies()
{

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
    float worldSize = Constants::mapSize;
    Vector3 squareCenter(pos.first * worldSize + worldSize / 2, 0, pos.second * worldSize + worldSize / 2);

    if (!checkMove(pos, dir))
    {
        if (dir.first > 0) // se está moviendo hacia la derecha y
            return false;
        if (dir.first < 0) // se está moviendo hacia la izquierda y
            return false;
        if (dir.second > 0) // se está moviendo hacia abajo y
            return false;
        if (dir.second < 0) // se está moviendo hacia abajo y 
            return false;
    }
    
    return true;
}

bool Labyrinth::checkCentered(pair<int, int> pos)
{
    float worldSize = Constants::mapSize; 
    Vector3 squareCenter(pos.first * worldSize, 0, pos.second * worldSize);

    float xS = squareCenter.x;
    int xH = _hero->getPosition().x;

    float zS = squareCenter.z;
    int zH = _hero->getPosition().z;

    return ((xS < xH + 5) && (xS > xH - 5)) && ((zS < zH + 5) && (zS > zH -5));
}
