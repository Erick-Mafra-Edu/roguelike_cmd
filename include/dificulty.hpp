#ifndef diculty_hpp
#define diculty_hpp
#include <iostream>
#include <windows.h>
#include <locale.h>
using namespace std;

template <typename Dificulty>
Dificulty escolha()
{
    Dificulty nivel;
    cout << "Digite a dificuldade: \n";
    cout << "1 ou F || Para dificuldade fácil\n";
    cout << "2 ou N || Para dificuldade normal\n";
    cout << "3 ou D || Para dificuldade difícil\n";
    cout << "Escolha: ";
    cin >> nivel;
    return nivel;
}

template <typename Dificulty>
float Dificuldade(Dificulty nivel, float dificuldade = 0.0)
{
    switch (nivel)
    {
    case 1:
    case 'F':
        cout << "Você escolheu: Fácil\n";
        dificuldade = 0.5;
        break;
    case 2:
    case 'N':
        cout << "Você escolheu: Normal\n";
        dificuldade = 1.0;
        break;
    case 3:
    case 'D':
        cout << "Você escolheu: Difícil\n";
        dificuldade = 2.0;
        break;
    default:
        break;
    }
    return dificuldade;
}
#endif // diculty_hpp