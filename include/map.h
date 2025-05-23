#include "./primitiveTypes.h"
#include "./enemy.h"

using namespace std;

// Toda a criação do tipo map
struct Gamemap
{
    static const short int maxEnemy = 4; // inimigos máximos por sala
    enemy enemyList[maxEnemy];
    bool boss = false; // WIP

    // Tamanho máximo do mapa e outras funções sobre
    int map[16][16] = {};
    enum mapSpawnPositions
    {
        top,
        bottom,
        left,
        right,
    };
    // Todas as coisas usadas na criação do mapa
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
        escada,
    };
    entities entity;
    Position spawnPos[4];
    void clearEnemyRoom()
    {
        for (int i = 0; i < maxEnemy; i++)
        {
            enemyList[i] = {};
        }
    }
    static const DWORD padrao = (0 << 4) | 7;    /* Define o mapa para printar fundo preto e escrita branca */
    static const DWORD branco = (0 << 4) | 15;   /* Define o mapa para printar fundo preto e escrita branca */
    static const DWORD amarelo = (0 << 4) | 14;  /* Define o mapa para printar fundo preto e escrita amarela */
    static const DWORD azul = (0 << 4) | 9;      /* Define o mapa para printar fundo preto e escrita azul */
    static const DWORD vermelho = (0 << 4) | 12; /* Define o mapa para printar fundo preto e escrita vermelha */
    DWORD themeColor = padrao;                   /* Define para começar na cor padrão */
};