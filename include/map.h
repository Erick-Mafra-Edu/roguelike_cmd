#include "./primitiveTypes.h"
#include "./enemy.h"

using namespace std;

// Toda a criação do tipo map
struct Gamemap
{
    static const short int maxEnemy = 4; // inimigos máximos por sala
    enemy enemyList[maxEnemy];
    bool boss = false; // WIP

    //Tamanho máximo do mapa e outras funções sobre
    int map[16][16] = {};
    enum mapSpawnPositions
    {
        top,
        bottom,
        left,
        right,
    };
    //Todas as coisas usadas na criação do mapa
    enum entities
    {
        floor = 0,
        parede = 1,
        enemy = 2,
        item,
        chest,
        mimic,
        fakewall = 11,
        portaSupInf = 91,
        portaLat = 92,
        vazio = 9,
        armadilha = 21,
    };
    entities entity;
    Position spawnPos[4];
    void clearEnemyRoom(){
        for(int i = 0; i < maxEnemy; i++){
            enemyList[i] = {};
        }
    }
};