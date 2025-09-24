#include "Labyrinth.h"
#include "Wall.h"
#include "Empty.h"

void Labyrinth::setupLabyrinth(SceneManager* mSM)
{
    _mSM = mSM;
    _labyrinthNode = _mSM->getRootSceneNode()->createChildSceneNode("nLabMain");
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

        std::vector<IG2Object*> line;

        for (int j = 0; j < width; j++) 
        {
            string id = to_string(i) + "-" + to_string(j) + "cube";
            //cout << id << "\n";
            // creamos el muro
            if (fila[j] == 'x') 
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                IG2Object* muro = new Wall(Vector3(j * 100, 0, i * 100), node, _mSM, "cube.mesh");
                line.push_back(muro);
            }
            else if (fila[j] == 'o')
            {
                SceneNode* node = _labyrinthNode->createChildSceneNode(id);
                IG2Object* vacio = new Empty(Vector3(j * 100, 0, i * 100), node, _mSM);
                line.push_back(vacio);
            }
            
            // labyrinth[i,j] = fila[j];
        }

        map.push_back(line);
    }
    //DebugMap();

    cin.rdbuf(cinbuf);
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