#include <iostream>
#include <conio.h>

using namespace std;
int Seed(int y, int x,int seed){
    seed = (y*983)+(x*797)+(seed*929);
    seed = seed % 13;
    return seed;
}
int generateSeed(){
    srand(time(NULL));
    return rand()%999999;
}
int main() {
    int x = 0, y = 0;
    char input;

    cout << "Use WASD to move. Press Q to quit." << endl;

    do {
        cout << "Current position: (" << x << ", " << y << ")" << endl;
        input = getch();

        switch (input) {
            case 'w':
                y--;
                cout << seed(y,x,696969);
                break;
            case 's':
                y++;
                cout << seed(y,x,696969);
                break;
            case 'a':
                x--;
                cout << seed(y,x,696969);
                break;
            case 'd':
                x++;
                cout << seed(y,x,696969);
                break;
            case 'q':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid input." << endl;
        }
    } while (input != 'q');

    return 0;
}
