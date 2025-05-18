#ifndef skill_hpp
#define skill_hpp
#include<string>
using namespace std;
struct skill
{
    string name;
    string description ="";
    unsigned short int requirementLevel = 0;
    short int requiredSkillId = -1;
    unsigned short int xpCust = 0;
};
struct skillTree{
    skill skills[18]={
        {"i am the god of war","Tenha a força de um Deus grego",0,-1,100},
        {"Medo Reverso","Ao invés de eles virem até você, você que vai até eles",0,-1,100},
        {"Espada do Caos", "Ataques devastadores com lâminas duplas flamejantes.", 1, -1, 100},
        {"Golpe Sombrio", "Evoca sombras para um ataque furtivo letal.", 2, 0, 150},
        {"Fúria do Berserker", "Aumenta o dano drasticamente por tempo limitado.", 3, 0, 200},
        {"Dança das Lâminas", "Sequência de golpes rápidos e estilizados.", 4, 2, 250},

        // Mágicas
        {"Chama Arcana", "Dispara uma bola de fogo mística.", 1, -1, 100},
        {"Barreira Etérea", "Escudo mágico que absorve dano.", 2, 4, 150},
        {"Tempestade de Gelo", "Congela inimigos em área com uma nevasca.", 3, 4, 200},
        {"Corrente Elétrica", "Raio que salta entre vários inimigos.", 4, 5, 250},

        // Defesa & Suporte
        {"Aura de Cura", "Regenera vida de aliados próximos.", 2, -1, 100},
        {"Grito de Guerra", "Aumenta o ataque e moral dos aliados.", 3, 8, 150},
        {"Postura Defensiva", "Reduz dano recebido temporariamente.", 2, -1, 100},
        {"Reflexo Rápido", "Aumenta chance de esquiva drasticamente.", 3, 10, 150},

        // Estratégicas & Passivas
        {"Mestre das Táticas", "Melhora habilidades quando usadas em sequência.", 4, 1, 200},
        {"Conhecimento Ancestral", "Amplifica magias esquecidas.", 4, 6, 200},
        {"Aprendiz Rápido", "Ganha XP extra ao usar novas habilidades.", 1, -1, 50},
        {"Presença Intimidante", "Reduz moral de inimigos ao redor.", 3, 9, 150}
    };
    unsigned short int size = 0;

};
#endif
