#include "Labyrinth.h"
#include "Wall.h"
#include "Empty.h"
#include "Constants.h"

using namespace std;

void Labyrinth::setupLabyrinth(SceneManager* mSM, Hero* hero)
{
    _mSM = mSM;
    _labyrinthNode = _mSM->getRootSceneNode()->createChildSceneNode("nLabMain");
    _hero = hero;
    
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
                line.push_back(muro);
            }
            else if (fila[j] == 'o')
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                Object* vacio = new Empty(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize), node, _mSM);
                line.push_back(vacio);
            }
            else if (fila[j] == 'h') 
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                line.push_back(new Empty(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize), node, _mSM)); // vacio en el mapa
          
                _hero->setPosition(Vector3(j * Constants::mapSize, 0, i * Constants::mapSize));
            }
            
            // labyrinth[i,j] = fila[j];
        }

        map.push_back(line);
    }
    //DebugMap();

    cin.rdbuf(cinbuf);
}

void Labyrinth::frameRendered(const Ogre::FrameEvent& evt) 
{
    Vector3 wantToMove = _hero->getLastPosibleDirection();
    pair<int, int> dirToMove = { wantToMove.x, wantToMove.z };

    _heroPos = vectorToMap(_hero->getPosition());
    std::cout << _heroPos.first << " " << _heroPos.second << "\n";

    bool movable = checkMove(_heroPos, dirToMove);

    _hero->moveCharacter();
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

pair<int, int> Labyrinth::vectorToMap(Vector3 pos)
{
    return pair<int, int>(pos.x / Constants::mapSize, pos.z / Constants::mapSize);
}

bool Labyrinth::checkMove(pair<int, int> pos, pair<int, int> dir)
{
    int x = pos.first + dir.first;
    int z = pos.second + dir.second;

    return map[x][z]->isEmpty();
}
