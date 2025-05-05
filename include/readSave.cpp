#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "./player.h"
const char tabChar = '\t';
int main(){
    ifstream fileSave("gameSave.save");
    string line;
    string pastSession = "";
    string actualSession = "";
    enum valueType{
        Health,
        Damage,
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
    };
    unsigned short int i = 0;
    if(fileSave.is_open()){
        Player player;
        while (getline(fileSave, line))
        {
            pastSession = actualSession;
            if (line[0] == '['){
                actualSession = line;
            }
            if (actualSession == "[Roguelike ASCII]")
            {
                cout <<"Save Game";
            }else if (actualSession == "[Player]")
            {
                cout << "Player Save" << endl;
                string value = "";
                stringstream valuesLine(line);
                bool isValue= false;
                valueType type;
                if(line != "[Player]") while (getline(valuesLine, value, tabChar))
                {
                    cout << value << endl;
                    if (isValue && type == valueType::Health)
                    {
                        player.health = stoi(value);
                        cout << player.health << " This is Life of Player";
                        isValue = false;
                    }else if (isValue && type == valueType::Damage)
                    {
                        player.damage = stoi(value);
                        cout << player.damage << " This is Damage of Player";
                        isValue = false;
                    }else if (isValue && type == valueType::Position)
                    {
                        player.position.X = stoi(value);
                        player.position.Y = stoi(value);
                        
                    }
                    
                    
                    if (value == "Health"){
                        isValue = true;
                        type = valueType::Health;
                    }else if (value == "Damage"){
                        isValue = true;
                        type = valueType::Damage;
                    }else if (value == "Position"){
                        isValue = true;
                        type = valueType::Position;
                    }
                    
                    
                };
                isValue = false;
                
                
            }else if (actualSession == "[Inventory]")
            {
                // cout<<"Inventory Save";
            }else if (actualSession == "[Items]")
            {
                // cout<<"Items Save";
                Items item;
                string value = "";
                stringstream valuesLine(line);
                bool isValue= false;
                valueType type;
                if(line != "[Items]") while (getline(valuesLine, value, tabChar)){
                    if (isValue)
                    {
                        unsigned short int j = 0;
                        switch (type)
                        {
                        case valueType::Type:
                                player.inventory.items[i].type = static_cast<Items::TypeofItems>(stoi(value));
                                cout<<i<<",";
                                i++;
                            break;
                        case valueType::Quantity:
                            /* code */
                            break;
                        case valueType::Durability:
                            /* code */
                            break;
                        case valueType::Defense:
                            /* code */
                            break;
                        case valueType::Heal:
                                player.inventory.items[i].heal = stoi(value);
                                cout<<i<<",";
                            break;
                        case valueType::Art:
                                player.inventory.items[i].art = value;
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
                    if (value == "Type"){
                        isValue = true;
                        type = valueType::Type;
                    }else if (value == "Quantity"){
                        isValue = true;
                        type = valueType::Quantity;
                    }else if (value == "Durability"){
                        isValue = true;
                        type = valueType::Durability;
                    }else if (value == "Defense"){
                        isValue = true;
                        type = valueType::Defense;
                    }else if (value == "Heal"){
                        isValue = true;
                        type = valueType::Heal;
                    }else if (value == "Art"){
                        isValue = true;
                        type = valueType::Art;
                    }else if (value == "MidX"){
                        isValue = true;
                        type = valueType::MidX;
                    }else if (value == "MidY"){
                        isValue = true;
                        type = valueType::MidY;
                    }else if (value == "Description"){
                        isValue = true;
                        type = valueType::Description;
                    }else if (value == "Damage"){
                        isValue = true;
                        type = valueType::Damage;
                    }
                    // if (type != valueType::Art)
                    // {
                        
                    // }
                    
                }
            }else if (actualSession == "[Game]")
            {
                // cout<<"Game Save";
            }  
        }
        cout<<player.inventory.items[0].type;
        cout<<player.inventory.items[1].type;
        cout<<player.inventory.items[2].type;
        cout<<player.inventory.items[3].type;
        cout << endl << player.position.X <<","<< player.position.Y << endl;
    }
}