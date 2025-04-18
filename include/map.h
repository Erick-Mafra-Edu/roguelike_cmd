#include "./primitiveTypes.h"
#include "./enemy.h"

using namespace std;

struct map
{
    static const short int maxEnemy = 4;
    enemy enemyList[maxEnemy];
    bool boss = false;

    int map[16][16] = {};
    enum mapSpawnPositions
    {
        top,
        bottom,
        left,
        right,
    };
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
    enum difficulty
    {
        // need logic to add difficulty when pass level
        easy,
        medium,
        hard,
    };
    entities entity;
    Position spawnPos[4];
    difficulty enemyLevel = map::difficulty::easy;
    void clearEnemyRoom(){
        for(int i = 0; i < maxEnemy; i++){
            enemyList[i] = {};
        }
    }
};