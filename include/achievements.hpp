#ifndef achievements_h
#define achievements_h
#include <string>
using namespace std;
struct achievements
{
    string name = "";
    string description = "";
    bool unlocked = false;
};
struct AllAchievements
{
    achievements achievements[20]{
        {"Primeiro Passo", "Entre na masmorra pela primeira vez.", false},
        {"Ohh Shit Here go Again", "Morra e volte a masmorra", false},
        {"Turista Perdido", "Mova-se aleatoriamente pelo mapa", false},
        {"Mudança de Clima", "Chegue em outro nivel da masmorra", false},
        {"Novato", "Alcance o nível 5.", false},
        {"Aventureiro", "Alcance o nível 10.", false},
        {"Deus de Mentirinha", "Libere a habilidade de um deus", false},
        {"Guerreiro", "Derrote 10 inimigos.", false},
        {"Caçador", "Derrote 50 inimigos.", false},
        {"Campeão", "Derrote 100 inimigos.", false},
        {"Achador de Bug", "Encontre um item raro que nem o dev lembrava que existia", false}, // Talvez mude no futuro
        {"Colecionador", "Colete 3 itens diferentes.", false},
        {"Acumulador", "Colete 7 itens diferentes.", false},
        {"Abastado", "Acumule 1000 de ouro.", false},        // Talvez mude no futuro
        {"Rico", "Acumule 5000 de ouro.", false},            // Talvez mude no futuro
        {"Toque de Midas", "Acumule 10000 de ouro.", false}, // Talvez mude no futuro
        {"Shiny", "Comer a maça do capiroto.", false},
        {"Referencias?", "Conseguir a arma pá.", false},
        {"Hokage", "Achar a kunai nos baús.", false},
        {"Gamer Lendário", "Desbloquear todas as outras conquistas (quem disse que era fácil?).", false}};
};

#endif