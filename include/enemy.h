#pragma once

#include <iostream>
#include "./primitiveTypes.h"

// Define o tipo inimigo
struct enemy
{
    char c = '!';
    Position position;
    short int health = 0,damage = 0;
};
