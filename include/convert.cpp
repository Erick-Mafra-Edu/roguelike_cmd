#include<conio.h>
#include<iostream>
#include<thread>
#include<windows.h>
#include<string>

using namespace std;
void CharacterDraw(string art,short int startX){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    short int midX = consoleWidth / 2 - startX;
    int midY = consoleHeight / 2 - 10;
    int counter = 0;
    int lineOffset = 0;
    string line;
    size_t pos = 0, newPos;
    while ((newPos = art.find('\n', pos)) != string::npos)
    {
        counter++;
        line = art.substr(pos, newPos - pos);
        SetConsoleCursorPosition(console, { startX, (SHORT)(midY + lineOffset) });
        cout << line;
        pos = newPos + 1;
        lineOffset++;
    }
}
void TalkInitGame(){
    
    string startTalk = "Nas páginas em branco do destino, uma nova história será escrita. "
    "Com tinta de coragem e papel de incerteza, qual nome assinará este capítulo?";
    for (size_t i = 0; i < startTalk.length(); i++)
    {
        if( _kbhit()){
            break;
        }
        int freq = 300+startTalk[i];
        thread testSound(Beep,freq,150);
        testSound.detach();
        cout << startTalk[i];
        Sleep(100);
    }
    
}
int Converter(int &letra,int input){
    // int input = 1;
    int returnValue = -1;
    switch(input){
        case 'a': case 'A': 
            returnValue = 1;
            letra+=6;
        break;
        case 'b': case 'B': 
            returnValue = 2;
            letra+=6;
        break;
        case 'c': case 'C':
            returnValue = 3;
            letra+=6; 
        break;
        case 'd': case 'D': 
            returnValue = 4;
            letra+=6;
        break;
        case 'e': case 'E':
            returnValue = 5;
            letra+=6;
        break;
        case 'f': case 'F': 
            returnValue = 6;
            letra+=6;
        break;
        case 'g': case 'G': 
            returnValue = 7;
            letra+=6;
        break;
        case 'h': case 'H': 
            returnValue = 8; 
            letra+=6;
        break;
        case 'i': case 'I': 
            returnValue = 9;
            letra+=6;
        break;
        case 'j': case 'J': 
            returnValue = 10;
            letra+=6;
        break;
        case 'k': case 'K': 
            returnValue = 11;
            letra+=6;
        break;
        case 'l': case 'L': 
            returnValue = 12;
            letra+=6;
        break;
        case 'm': case 'M': 
            returnValue = 13;
            letra+=6;
        break;
        case 'n': case 'N': 
            returnValue = 14;
            letra+=6;
        break;
        case 'o': case 'O': 
            returnValue = 15;
            letra+=6;
        break;
        case 'p': case 'P': 
            returnValue = 16;
            letra+=6;
        break;
        case 'q': case 'Q': 
            returnValue = 17;
            letra+=6;
        break;
        case 'r': case 'R': 
            returnValue = 18;
            letra+=6;
        break;
        case 's': case 'S': 
            returnValue = 19;
            letra+=6;
        break;
        case 't': case 'T': 
            returnValue = 20;
            letra+=6;
        break;
        case 'u': case 'U': 
            returnValue = 21;
            letra+=6;
        break;
        case 'v': case 'V': 
            returnValue = 22;
            letra+=6;
        break;
        case 'w': case 'W': 
            returnValue = 23;
            letra+=6;
        break;
        case 'x': case 'X': 
            returnValue = 24;
            letra+=6;
        break;
        case 'y': case 'Y': 
            returnValue = 25;
            letra+=6;
        break;
        case 'z': case 'Z':
            returnValue = 26;
            letra+=6;
        break;
        case 32: //espaço
            returnValue = 27;
            letra+=6;
        break;
        case 8:{ //backspace
            returnValue = 27;
        }
        break;
        default:
        break;
    }
    return returnValue;
}
string asciiAlphabet[27] = {
    // A
    "____\n"
    "|__|\n"
    "|  |\n",

    // B
    " ___\n"
    "|__]\n"
    "|__]\n",

    // C
    "____\n"
    "|   \n"
    "|___\n",

    // D
    "___ \n"
    "|  \\\n"
    "|__/\n",

    // E
    "___ \n"
    "|__ \n"
    "|__ \n",

    // F
    "___ \n"
    "|__ \n"
    "|   \n",

    // G
    "____\n"
    "|___ \n"
    "|___|\n",

    // H
    "_  _\n"
    "|__|\n"
    "|  |\n",

    // I
    " _ \n"
    " | \n"
    " | \n",

    // J
    "___ \n"
    "  | \n"
    "__| \n",

    // K
    "_  _\n"
    "|__/ \n"
    "|  \\\n",

    // L
    "__  \n"
    "|   \n"
    "|__ \n",

    // M
    "_  _\n"
    "|\\/|\n"
    "|  |\n",

    // N
    "_  _\n"
    "|\\ |\n"
    "| \\|\n",

    // O
    "____\n"
    "|  |\n"
    "|__|\n",

    // P
    "____\n"
    "|__|\n"
    "|   \n",

    // Q
    "____\n"
    "|  |\n"
    "|_\\_\\\n",

    // R
    "____\n"
    "|__/\n"
    "|  \\\n",

    // S
    "____\n"
    "[__ \n"
    "___]\n",

    // T
    "___\n"
    " | \n"
    " | \n",

    // U
    "__ __\n"
    "|  |\n"
    "|__|\n",

    // V
    "__ __\n"
    "\\  /\n"
    " \\/ \n",

    // W
    "_  _\n"
    "|\\ |\n"
    "| \\|\n",

    // X
    "_  _\n"
    " \\/ \n"
    " /\\ \n",

    // Y
    "_   _\n"
    " \\_/ \n"
    "  |  \n",

    // Z
    "___ \n"
    " /  \n"
    "/__ \n",
    
    // space
    "    \n"
    "    \n"
    "    \n"
};
Nick SetNick(){
    TalkInitGame();
    Nick nick;
    int letra = 0;
    int input = 0;
    unsigned short int charCounter = 0;
    system("cls");
    do{
        if ( _kbhit() ){
            input = getch();
            if (input != 8){
            nick.nick[charCounter] = toupper(input);
            charCounter++;
            }
        }else{
            input = 0;
        }
        int number = Converter(letra,input);
        if(number > 0){
            CharacterDraw(asciiAlphabet[number-1],letra);
            if (input == 8){
                    letra-=6;
                    nick.nick[charCounter] = '\0';
                    charCounter--;
                if (letra < 0)
                {
                    letra = 0;
                    charCounter--;
                }
            }
        }
        
    }while(charCounter < 3);
    system("cls");
    cout << nick.nick;
    Sleep(5000);
    return nick;
}