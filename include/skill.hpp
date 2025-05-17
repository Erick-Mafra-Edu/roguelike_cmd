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
    skill skills[10]={
        {"i am the god of war","Tenha a força de um Deus grego",-1,100},
        {"Medo Reverso","Ao invés de eles virem até a você você que vai até eles",0,100},
    };
    unsigned short int size = 0;

};
#endif