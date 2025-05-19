#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const char tabChar = '\t';
int readSave(Game &game)
{
    int indexNick = 0;
    ifstream fileSave("C:\\Users\\Erick\\roguelike_cmd\\gameSave.save");
    string line;
    string pastSession = "";
    string actualSession = "";
    enum valueType
    {
        Health,
        Damage,
        Shield,
        Position,
        Type,
        Quantity,
        Durability,
        Defense,
        Heal,
        Art,
        MidX,
        MidY,
        Description,
        seed,
        ReturnType,
        points,
        roomsMoved,
        Nick,
        inMap,
        Size
    };
    short int i = -1;
    if (fileSave.is_open())
    {
        Player player = game.player;
        while (getline(fileSave, line))
        {
            pastSession = actualSession;
            if (line[0] == '[')
            {
                actualSession = line;
            }
            if (actualSession == "[Roguelike ASCII]")
            {
                cout << "Save Game";
            }
            else if (actualSession == "[Player]")
            {
                cout << "Player Save" << endl;
                string value = "";
                stringstream valuesLine(line);
                bool isValue = false;
                valueType type;
                if (line != "[Player]")
                    while (getline(valuesLine, value, tabChar))
                    {
                        cout << value << endl;
                        if (isValue && type == valueType::Health)
                        {
                            player.health = stoi(value);
                            cout << player.health << " This is Life of Player";
                            isValue = false;
                        }
                        else if (isValue && type == valueType::Damage)
                        {
                            player.damage = stoi(value);
                            cout << player.damage << " This is Damage of Player";
                            isValue = false;
                        }
                        else if (isValue && type == valueType::Position)
                        {
                            player.position.X = stoi(value);
                            player.position.Y = stoi(value);
                        }
                        else if (isValue && type == valueType::Shield)
                        {
                            player.shield = stoi(value);
                        }
                        if (value == "Health")
                        {
                            isValue = true;
                            type = valueType::Health;
                        }
                        else if (value == "Damage")
                        {
                            isValue = true;
                            type = valueType::Damage;
                        }
                        else if (value == "Position")
                        {
                            isValue = true;
                            type = valueType::Position;
                        }
                        else if (value == "Shield")
                        {
                            isValue = true;
                            type = valueType::Shield;
                        }
                    };
                isValue = false;
            }
            else if (actualSession == "[Inventory]")
            {
                string value = "";
                stringstream valuesLine(line);
                bool isValue = false;
                valueType type;
                if (line != "[Inventory]")
                {
                    while (getline(valuesLine, value, tabChar))
                    {
                        if (isValue)
                        {
                            switch (type)
                            {
                            case valueType::Size:
                                player.inventory.size = (SHORT)stoi(value);
                                break;
                            default:
                                break;
                            }
                        }
                        if (value == "Size")
                        {
                            isValue = true;
                            type = valueType::Size;
                        }
                    }
                }
            }
            else if (actualSession == "[Items]")
            {
                // cout<<"Items Save";
                Items item;
                string value = "";
                stringstream valuesLine(line);
                bool isValue = false;
                valueType type;
                if (line != "[Items]")
                    while (getline(valuesLine, value, tabChar))
                    {
                        unsigned short int j;
                        if (isValue)
                        {
                            switch (type)
                            {
                            case valueType::Type:
                                player.inventory.items[i].type = static_cast<Items::TypeofItems>(stoi(value));
                                cout << i << ",";
                                i++;
                                break;
                            case valueType::Quantity:
                                /* code */
                                break;
                            case valueType::Durability:
                                /* code */
                                break;
                            case valueType::Defense:
                                player.inventory.items[i].defense = stoi(value);
                                cout << i << ",";
                                break;
                            case valueType::Heal:
                                player.inventory.items[i].heal = stoi(value);
                                cout << i << ",";
                                break;
                            case valueType::Art:
                                player.inventory.items[i].art += value + "\n";
                                break;
                            case valueType::MidX:
                                player.inventory.items[i].midX = stoi(value);
                                break;
                            case valueType::MidY:
                                player.inventory.items[i].midY = stoi(value);
                                break;
                            case valueType::Description:
                                player.inventory.items[i].description[j++] = value;
                                break;
                            case valueType::Damage:
                                /* code */
                                break;
                            default:
                                break;
                            }
                        }
                        if (value == "Type")
                        {
                            isValue = true;
                            type = valueType::Type;
                        }
                        else if (value == "Quantity")
                        {
                            isValue = true;
                            type = valueType::Quantity;
                        }
                        else if (value == "Durability")
                        {
                            isValue = true;
                            type = valueType::Durability;
                        }
                        else if (value == "Defense")
                        {
                            isValue = true;
                            type = valueType::Defense;
                        }
                        else if (value == "Heal")
                        {
                            isValue = true;
                            type = valueType::Heal;
                        }
                        else if (value == "Art")
                        {
                            isValue = true;
                            type = valueType::Art;
                        }
                        else if (value == "MidX")
                        {
                            isValue = true;
                            type = valueType::MidX;
                        }
                        else if (value == "MidY")
                        {
                            isValue = true;
                            type = valueType::MidY;
                        }
                        else if (value == "Description")
                        {
                            isValue = true;
                            type = valueType::Description;
                            j = 0;
                        }
                        else if (value == "Damage")
                        {
                            isValue = true;
                            type = valueType::Damage;
                        }
                        // if (type != valueType::Art) // SEM SENTIDO
                        // {

                        // }
                    }
            }
            else if (actualSession == "[Game]")
            {
                valueType type;
                bool isValue = false;
                string value = "";
                int indexPoints = 0;

                stringstream valuesLine(line);
                // if(line != "[Game]")
                while (getline(valuesLine, value, tabChar))
                {
                    if (isValue)
                    {
                        switch (type)
                        {
                        case valueType::seed:
                            game.seed = stoi(value);
                            break;
                        case valueType::ReturnType:
                            game.returnType = static_cast<Game::ReturnTypes>(stoi(value));
                            break;
                        case valueType::points:
                            game.points[indexPoints++] = stoi(value);
                            break;
                        case valueType::Nick:
                            for (int i = 0; i < 3; i++)
                            {
                                if (value != "")
                                    game.nick[indexNick].nick[i] = value[i];
                            }
                            indexNick++;
                            break;
                        case valueType::roomsMoved:
                            game.roomsMoved = stoi(value);
                            break;
                        case valueType::inMap:
                            game.inMap.x = stoi(value);
                            game.inMap.y = stoi(value);
                            break;
                        }
                    }
                    if (value == "Seed")
                    {
                        isValue = true;
                        type = valueType::seed;
                    }
                    else if (value == "ReturnType")
                    {
                        isValue = true;
                        type = valueType::ReturnType;
                    }
                    else if (value == "Points")
                    {
                        isValue = true;
                        type = valueType::points;
                    }
                    else if (value == "Rooms Moved")
                    {
                        isValue = true;
                        type = valueType::roomsMoved;
                    }
                    else if (value == "inMap")
                    {
                        isValue = true;
                        type = valueType::inMap;
                    }
                    else if (value == "Nick")
                    {
                        isValue = true;
                        type = valueType::Nick;
                    }
                }
            }
            game.player = player;
            cout << player.inventory.items[0].type;
            cout << player.inventory.items[1].type;
            cout << player.inventory.items[2].type;
            cout << player.inventory.items[3].type;
            cout << endl
                 << player.position.X << "," << player.position.Y << endl;
        }
        fileSave.close();
    }
    return indexNick;
}