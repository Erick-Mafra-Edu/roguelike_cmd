#include "./map.h"
#include "./enemy.h"
#include <ctime>

#include <windows.h>

int Seed(int y, int x,int seed){ // Adicionando geração infinitas de mapas
    seed = (y*983)+(x*797)+(seed*929);
    seed = seed % 13+1;
    return seed;//selectMap
}
int generateSeed(){ // Limite máximo
    srand(time(NULL));
    return rand()%999999;
}
int enemyHealth =10,enemyDamage=10;
void definedMap(Gamemap &currentMap, short int newMap[16][16])
{
    int amount = 0;
    currentMap.clearEnemyRoom(); // Garante que a lista de inimigos está limpa

    
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            currentMap.map[i][j] = newMap[i][j];
        }
    }
    enemyHealth+=rand()%5+1; // Adiciona dificuldade ao inimigos progressivamente
    enemyDamage+=rand()%5+1; // Adiciona dificuldade ao inimigos progressivamente
    for (int i = 0; i < 16; i++) 
    {
        for (int j = 0; j < 16; j++)
        {
            // Verifica se:
            // - Ainda há espaço na lista de inimigos (amount < maxEnemy)
            // - A posição atual no mapa é um piso (floor)
            // - A chance aleatória (1%) ocorreu
            if (amount < currentMap.maxEnemy && currentMap.map[i][j] == Gamemap::entities::floor && (rand() % 100 < 1))
            {
                // Se todas as condições forem verdadeiras, adicione o inimigo:
                currentMap.map[i][j] = currentMap.entities::enemy; // Coloca o inimigo visualmente no mapa
                currentMap.enemyList[amount] = enemy();            // Adiciona um novo inimigo à lista
                currentMap.enemyList[amount].health=enemyHealth;
                currentMap.enemyList[amount].damage=enemyDamage;
                
                // Define a posição do inimigo na lista.
                // ATENÇÃO: COORD usa X, Y. No loop, j é coluna (X) e i é linha (Y).
                currentMap.enemyList[amount].position = {(short)j, (short)i};

                amount++; // Incrementa o contador de inimigos adicionados à lista
            }
        }
    }
     
}


// Responsável por definir no mapa o que cada coisa é
void printMap(Gamemap &mapCurrent)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            switch (mapCurrent.map[i][j])
            {
            // desenhando piso
            case 0:
                cout << " ";
                break;
            case mapCurrent.entities::parede:
                cout << "\u2588";
                break;
            case mapCurrent.entities::enemy:
                cout << "!";
                break;
            case mapCurrent.entities::portaLat:
                cout << "\u007C";
                break;
            case mapCurrent.entities::portaSupInf:
                cout << "-";
                break;
            case mapCurrent.entities::chest:
                cout << "\u00A4";
                break;
            case mapCurrent.entities::mimic:
                cout << "\u00A4";
                break;
            case mapCurrent.entities::vazio:
                cout << " ";
                break;
            case mapCurrent.entities::fakewall:
                cout << "\u2588";
                break;
            case mapCurrent.entities::armadilha:
                cout << " ";
                break;
            default:
                break;
            }
        }
        cout << endl;
    }
}
// Resposável por movimentações dos inimigos
void updateMoveEnemies(Gamemap &mapCurrent, Position position, HANDLE &hConsole)
{
    if (mapCurrent.enemyList)
    {
        for (int i = 0; i < mapCurrent.maxEnemy; i++)
        {
            int dirX = 0;
            int dirY = 0;

            enemy &currentEnemy = mapCurrent.enemyList[i];
            if (currentEnemy.health > 0){
            
                //limpa posição anterior
                mapCurrent.map[currentEnemy.position.y][currentEnemy.position.x] = mapCurrent.entities::floor;
                SetConsoleCursorPosition(hConsole, {(SHORT)currentEnemy.position.x, (SHORT)currentEnemy.position.y});
                if(currentEnemy.position.x !=0 && currentEnemy.position.y != 0) cout << " ";

                // define a direção
                currentEnemy.position.y < position.y ? dirY = 1 : dirY = -1;
                currentEnemy.position.x < position.x ? dirX = 1 : dirX = -1;
                
                // anula a direção se estiver na reta do player
                currentEnemy.position.y - position.y == 0 ? dirY = 0 : 0;
                currentEnemy.position.x - position.x == 0 ? dirX = 0 : 0;
        
                // verifica se a proxima posição é parede
                if (mapCurrent.map[currentEnemy.position.y + dirY][currentEnemy.position.x + dirX] == mapCurrent.entities::parede ||
                    mapCurrent.map[currentEnemy.position.y + dirY][currentEnemy.position.x + dirX] == mapCurrent.entities::portaLat ||
                    mapCurrent.map[currentEnemy.position.y + dirY][currentEnemy.position.x + dirX] == mapCurrent.entities::portaSupInf ||
                    mapCurrent.map[currentEnemy.position.y + dirY][currentEnemy.position.x + dirX] == mapCurrent.entities::fakewall)
                {
                    dirX = 0;
                    dirY = 0;
                }

                // atualiza a posição se for piso e não é a posição do player
                if (mapCurrent.map[currentEnemy.position.y + dirY][currentEnemy.position.x + dirX] == mapCurrent.entities::floor )
                {
                    currentEnemy.position.x += dirX;
                    currentEnemy.position.y += dirY;
                }
                
                //define a posição do inimigo
                mapCurrent.map[currentEnemy.position.y][currentEnemy.position.x] = mapCurrent.entities::enemy;
                SetConsoleCursorPosition(hConsole, {(SHORT)currentEnemy.position.x, (SHORT)currentEnemy.position.y});

                if(currentEnemy.health > 0){
                    cout << mapCurrent.enemyList->c;
                }
                
                if(currentEnemy.health < 0 && currentEnemy.position.x !=0 && currentEnemy.position.y != 0){
                    cout<< " ";
                }
            }
        }   
    }

        
        // if(mapCurrent.boss){
        //     mapCurrent.clearEnemyRoom();
        //     SetConsoleCursorPosition(hConsole, {0, 0});
        //     printMap(mapCurrent);
        //     mapCurrent.map[5][5] = mapCurrent.entities::enemy;
        //     mapCurrent.enemyList[0] = enemy();
        //     mapCurrent.enemyList[0].health=20;
        //     mapCurrent.enemyList[0].c = 'D';
        //     mapCurrent.enemyList[0].position = {(short)5, (short)5};
        //     mapCurrent.boss = false;
        // }


}
// Criação dos mapas, matriz mãe.
void mapa(Gamemap &newMap,short int mapSelect)
{
    newMap.spawnPos[Gamemap::bottom] = {5, 5};
    newMap.enemy; // Inimigo = Número 2


    short int inicial1[16][16] = {
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    short int inicial2[16][16] = {
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 4, 1, 9, 9, 9, 9, 9, 9},
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    short int inicial3[16][16] = {
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 5, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    short int inicial4[16][16] = {
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 4, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    short int SalaP1[16][16] = {
        {1, 1, 91, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {92, 0, 21, 0, 92, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 1, 91, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    short int SalaP2[16][16] = {
        {1, 1, 91, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {92, 0, 4, 0, 92, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 1, 91, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    short int SalaM1[16][16] = {
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {1, 4, 1, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 11, 1, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {1, 21, 1, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 5, 1, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    short int SalaM2[16][16] = {
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 1, 21, 1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 21, 4, 21, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {92, 0, 0, 1, 21, 1, 0, 0, 0, 92, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9},
        {1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    short int SalaG1[16][16] = {
        {1, 1, 1, 1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 4, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 92},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 92},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 21, 1, 0, 1},
        {1, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 21, 4, 21, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 21, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 1, 1, 1}};

    short int SalaG2[16][16] = {
        {1, 1, 1, 1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 4, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 92},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 92},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 4, 11, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 21, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 1, 1, 1}};


    short int SalaG3[16][16] = {
        {1, 1, 1, 1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 4, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 92},
        {92, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 92},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 21, 5, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 21, 11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 91, 91, 1, 1, 1, 1, 1, 1, 1}};

    short int SalaL1[16][16] = {
        {1, 1, 91, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9},
        {92, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 92, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 9, 9, 9},
        {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 1, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 1, 91, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    short int SalaL2[16][16] = {
        {1, 1, 91, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 9, 9, 9},
        {92, 0, 0, 0, 0, 0, 0, 1, 4, 1, 0, 0, 92, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 1, 9, 9, 9},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 9, 9},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}};

    short int Template[16][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    
    // Seleção da matriz mapa para printar no terminal
    switch (mapSelect)
    {
    case 1:
        definedMap(newMap, inicial1);
        break;
    case 2:
        definedMap(newMap, inicial2);
        break;
    case 3:
        definedMap(newMap, inicial3);
    case 4:
        definedMap(newMap, inicial4);
        break;
    case 5:
        definedMap(newMap, SalaP1);
        break;
    case 6:
        definedMap(newMap, SalaP2);
        break;
    case 7:
        definedMap(newMap, SalaM1);
        break;
    case 8:
        definedMap(newMap, SalaM2);
        break;
    case 9:
        definedMap(newMap, SalaG1);
        break;
    case 10:
        definedMap(newMap, SalaG2);
        break;
    case 11:
        definedMap(newMap, SalaG3);
        break;
    case 12:
        definedMap(newMap, SalaL1);
        break;
    case 13:
        definedMap(newMap, SalaL2);
        break;
    default:
        break;
    }
}
