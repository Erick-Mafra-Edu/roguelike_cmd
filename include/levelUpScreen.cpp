#include "skill.hpp"
#include <windows.h>
#include <iostream>
#include <conio.h>
// Function to update the selected skill and display its information
void updateAndDisplaySkillInfo(int &move, const CONSOLE_SCREEN_BUFFER_INFO &csbi,
                               const skillTree &skills, bool moveDown, Game game)
{
    // Clear previous selection indicator
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)3, (SHORT)(move + 2)});
    for (short int i = 0; i < skills.skills[move].name.length() + 2; i++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(3 + i), (SHORT)(move + 2)});
        std::cout << " ";
    }
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)3, (SHORT)(move + 2)});
    std::cout << skills.skills[move].name;

    // Clear previous description and cost
    for (short int i = 0; i < skills.skills[move].description.length(); i++) // Use current move's description length for clearing
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(i + 2), (SHORT)(csbi.dwSize.Y - 9)});
        std::cout << " ";
    }
    std::string costString = "Está Habilidade custa: " + std::to_string(skills.skills[move].skillPointCust);
    for (short int i = 0; i < costString.length(); i++) // Use current move's cost string length for clearing
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(i + 2), (SHORT)(csbi.dwSize.Y - 1)});
        std::cout << " ";
    }

    // Update move index
    if (moveDown)
    {
        // The maximum index for skills is 17 (since there are 18 skills, indexed 0-17)
        // The display area for skills seems to be csbi.dwSize.Y - 11 (from the initial loop) - 2 (for 0-based indexing and border)
        // So, the number of visible skill names is csbi.dwSize.Y - 11 - 2 + 1 = csbi.dwSize.Y - 12
        // However, the original code uses csbi.dwSize.Y - 15 as a limit, which might be related to how many skills fit on screen
        // Let's stick to the logic of not exceeding the array bounds first.
        // The maximum index is skills.skills array size - 1, which is 17.
        // The visible limit seems to be csbi.dwSize.Y - 13 (since loop is i < csbi.dwSize.Y - 11, and skills[i-2])
        // Max visible items: (csbi.dwSize.Y - 12) - 2 = csbi.dwSize.Y - 14
        // So, if move is at the last displayable item, it should not increment further if it's also the last skill.
        // The limit csbi.dwSize.Y - 15 seems to be the maximum *value* for move in this context.
        // Let's refine this to ensure it doesn't go out of bounds of the actual skills array.
        // The number of skills is 18. So valid indices are 0 to 17.
        // The number of lines available for skill names is (csbi.dwSize.Y - 11) - 2 = csbi.dwSize.Y - 13
        int displayableSkillSlots = csbi.dwSize.Y - 11 - 2; // Number of lines from y=2 to y=csbi.dwSize.Y-12

        if (move < displayableSkillSlots - 1 && move < 17)
        { // if move is less than the second to last display slot AND less than the actual last skill
            move++;
        }
        else if (move < 17)
        { // if we are at the last display slot, but not the last skill (scrolling needed, but not implemented here)
          // For now, let's cap at the smaller of displayable slots or actual skill count
            if (move < (displayableSkillSlots < 18 ? displayableSkillSlots - 1 : 17))
                move++;
        }
    }
    else // moveUp
    {
        if (move > 0)
        {
            move--;
        }
    }
    // Cap move to ensure it's within the bounds of the skills array (0 to 17)
    if (move < 0)
        move = 0;
    if (move > 17)
        move = 17; // Max index for 18 skills
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - 20 - 2), (SHORT)(2)});
    std::cout << "                     ";
    std::string message = "Você tem " + std::to_string(game.SkillPoints) + " Skill Points";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - message.length() - 2), (SHORT)(2)});
    std::cout << message;
    // Display new selection indicator
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)3, (SHORT)(move + 2)});
    std::cout << "> ";
    std::cout << skills.skills[move].name;

    // Display new description and cost
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)2, (SHORT)(csbi.dwSize.Y - 9)});
    std::cout << skills.skills[move].description;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)2, (SHORT)(csbi.dwSize.Y - 1)});
    std::cout << "Está Habilidade custa: " << skills.skills[move].skillPointCust;
    // Desenhando o botão de ação
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - 40), (SHORT)(csbi.dwSize.Y - 1)});
    std::cout << "                                       ";
    if (!skills.skills[move].unlocked)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - 27), (SHORT)(csbi.dwSize.Y - 1)});
        std::cout << "Aperte Espaço para Comprar";
    }
    else
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - 27), (SHORT)(csbi.dwSize.Y - 1)});
        std::cout << "Habilidade Comprada";
    }
}
void BuySkill(int move, skillTree &skills, Game &game)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    skills.skills[move].unlocked = true;
    if (game.SkillPoints >= skills.skills[move].skillPointCust)
    {
        game.SkillPoints -= skills.skills[move].skillPointCust;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - 40), (SHORT)(csbi.dwSize.Y - 1)});
        std::cout << "                                       ";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - 27), (SHORT)(csbi.dwSize.Y - 1)});
        std::cout << "Habilidade Comprada";
    }
    else
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - 40), (SHORT)(csbi.dwSize.Y - 1)});
        std::cout << "                                       ";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - 40), (SHORT)(csbi.dwSize.Y - 1)});
        std::cout << "Você não tem Skill Points suficiente";
    }
}
void levelUpScreen(Game &game)
{
    // setLocale(LC_ALL, "pt_BR.");
    setlocale(LC_ALL, "pt_BR.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    skillTree skills = skillTree();
    for (short int i = 0; i < csbi.dwSize.X; i++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)i, (SHORT)0});
        std::cout << "-";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)i, (SHORT)(csbi.dwSize.Y - 10)});
        std::cout << "-";
    }
    for (short int i = 0; i < csbi.dwSize.Y - 9; i++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)0, (SHORT)i});
        std::cout << "|";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - 1), (SHORT)i});
        std::cout << "|";
    }
    for (short int i = 2; i < csbi.dwSize.Y - 11; i++)
    {
        // Ensure we don't try to access skills out of bounds if console is too small
        if (i - 2 < 18)
        { // 18 is the number of skills
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)3, (SHORT)i});
            std::cout << skills.skills[i - 2].name;
            // std::cout << skills.skills[i - 2].name.length(); // Original debug line
        }
    }
    int move = 0;
    int input = 0;

    // Initial display for the first skill
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)3, (SHORT)(move + 2)});
    std::cout << "> ";
    std::cout << skills.skills[move].name;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)2, (SHORT)(csbi.dwSize.Y - 9)});
    std::cout << skills.skills[move].description;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)2, (SHORT)(csbi.dwSize.Y - 1)});
    std::cout << "Está Habilidade custa: " << skills.skills[move].skillPointCust;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)(csbi.dwSize.X - 27), (SHORT)(csbi.dwSize.Y - 1)});
    std::cout << "Aperte Espaço para Comprar";
    do
    {
        input = getch();
        switch (input)
        {
        case 's':
        case 'S':
            updateAndDisplaySkillInfo(move, csbi, skills, true, game);
            break;
        case 'w':
        case 'W':
            updateAndDisplaySkillInfo(move, csbi, skills, false, game);
            break;
        case 32: // Spacebar
            // buySkill
            if (!skills.skills[move].unlocked)
                BuySkill(move, skills, game);
        }
    } while (input != 27);

    // std::cout << skills.skills[0].description;
    // return 0;
}
