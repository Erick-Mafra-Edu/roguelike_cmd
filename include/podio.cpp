#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
void gotoxy(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct RankingEntry {
    std::string name = "\0";
    short int score = 0;
};

// Função que exibe a tela de ranking
void displayRanking(const Game &game) {
    // Copiar dados para vetor de entries
    
    RankingEntry entries[10];
    for (int i = 0; i < 10; ++i) {
        entries[i] = RankingEntry({ game.nick[i].nick, game.points[i] });
    }
    
    // Ordena em ordem decrescente de pontuação
    for (int i = 0; i < 10; ++i) {
        for (int j = i + 1; j < 10; ++j) {
            if (entries[j].score > entries[i].score) {
                RankingEntry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }

    // Limpa tela
    system("cls");

    // Título
    gotoxy(10, 2);
    std::cout << "=== RANKING DE JOGADORES ===";
    
    // Cabeçalho
    gotoxy(10, 4);
    std::cout << "Pos  Nome               Pontos";

    // Exibe cada entry
    for (size_t i = 0; i < 10; ++i) {
        gotoxy(10, 6 + i);
        std::cout << (i + 1);
        gotoxy(15, 6 + i);
        if (entries[i].name[0] != '\0') {
        std::cout << entries[i].name[0]<<entries[i].name[1]<<entries[i].name[2];
        }
        gotoxy(35, 6 + i);
        std::cout << entries[i].score;
    }

    // Espera o usuário pressionar uma tecla para voltar
    gotoxy(10, 8 + 15);
    std::cout << "Pressione qualquer tecla para continuar...";
    _getch();
}
