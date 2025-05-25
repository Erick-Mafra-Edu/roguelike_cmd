#ifndef skill_hpp
#define skill_hpp
#include <string>
// using namespace std;

struct skill
{
    std::string name;
    std::string description = "";
    unsigned short int requirementLevel = 0;
    short int requiredSkillId = -1;
    unsigned short int skillPointCust = 0;
    bool unlocked = false;
};
struct skillTree
{
    skill skills[18] = {
        {"i am the god of war", "Tenha a força de um Deus grego", 0, -1, 2},
        {"Medo Reverso", "Ao invés de eles virem até você, você que vai até eles", 0, -1, 2},
        {"Espada do Caos", "Ataques devastadores com lâminas duplas flamejantes.", 1, -1, 2},
        {"Golpe Sombrio", "Evoca sombras para um ataque furtivo letal.", 2, 0, 1},
        {"Fúria do Berserker", "Aumenta o dano drasticamente por tempo limitado.", 3, 0, 1},
        {"Dança das Lâminas", "Sequência de golpes rápidos e estilizados.", 4, 2, 1},

        // Mágicas
        {"Chama Arcana", "Dispara uma bola de fogo mística.", 1, -1, 3},
        {"Barreira Etérea", "Escudo mágico que absorve dano.", 2, 4, 3},
        {"Tempestade de Gelo", "Congela inimigos em área com uma nevasca.", 3, 4, 4},
        {"Corrente Elétrica", "Raio que salta entre vários inimigos.", 4, 5, 4},

        // Defesa & Suporte
        {"Aura de Cura", "Regenera vida de aliados próximos.", 2, -1, 5},
        {"Grito de Guerra", "Aumenta o ataque e moral dos aliados.", 3, 8, 5},
        {"Postura Defensiva", "Reduz dano recebido temporariamente.", 2, -1, 1},
        {"Reflexo Rápido", "Aumenta chance de esquiva drasticamente.", 3, 10, 1},

        // Estratégicas & Passivas
        {"Mestre das Táticas", "Melhora habilidades quando usadas em sequência.", 4, 1, 1},
        {"Conhecimento Ancestral", "Amplifica magias esquecidas.", 4, 6, 1},
        {"Aprendiz Rápido", "Ganha XP extra ao usar novas habilidades.", 1, -1, 2},
        {"Presença Intimidante", "Reduz moral de inimigos ao redor.", 3, 9, 1}};
    unsigned short int size = 0;
};
#endif
