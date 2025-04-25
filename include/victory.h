
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
void drawVictoryScreen() {
    system("cls");
    int width = 80;
    int height = 25;

    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 1; i < height - 1; i++) {
        cout << "#";
        for (int j = 1; j < width - 1; j++) {
            if (i == height / 2 && j == width / 2 - 4) {
                cout << "VICTORY!";
                j += 7;
            }
            else {
                cout << " ";
            }
        }
        cout << "#" << endl;
    }

    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;
    _getch();
}
