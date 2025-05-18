#include <iostream>
// #include "./player.h"
#include <fstream>
// using namespace std;

void saveGame(Game &game){
    //for testing i have used All Items Function
    //AllItems(test.player.inventory);
    std::ofstream fileSave("C:\\Users\\Erick\\roguelike_cmd\\gameSave.save");
    fileSave << "[Roguelike ASCII]"<<endl;
    fileSave << "[Player]"<<endl;
    fileSave << "Health"<<"\t"<<game.player.health<<endl;
    fileSave << "Damage"<<"\t"<<game.player.damage<<endl;
    fileSave << "Position"<<"\t"<<game.player.position.X<<"\t"<<game.player.position.Y<<endl;
    fileSave << "Shield"<<"\t"<<game.player.shield<<endl;
    fileSave << "[Inventory]"<<endl;
    fileSave << "Size" << "\t" << game.player.inventory.size << endl;   
    fileSave << "[Items]"<<endl;
    for (size_t i = 0; i < game.player.inventory.size; i++)
    {
        fileSave << "Type"<<"\t"<<game.player.inventory.items[i].type<<endl;
        fileSave << "Quantity"<<"\t"<<game.player.inventory.items[i].quantity<<endl;
        fileSave << "Durability"<<"\t"<<game.player.inventory.items[i].durability<<endl;
        fileSave << "Damage"<<"\t"<<game.player.inventory.items[i].damage<<endl;
        fileSave << "Defense"<<"\t"<<game.player.inventory.items[i].defense<<endl;
        fileSave << "Heal"<<"\t"<<game.player.inventory.items[i].heal<<endl;
        // fileSave << "Effects"<<"\t"<<test.player.inventory.items[i].effects<<endl;
        fileSave << "Art"<<"\t"<<game.player.inventory.items[i].art<<endl;
        fileSave << "MidX"<<"\t"<<game.player.inventory.items[i].midX<<endl;
        fileSave << "MidY"<<"\t"<<game.player.inventory.items[i].midY<<endl;
        fileSave << "Description"<<"\t"<<game.player.inventory.items[i].description[0]
        <<"\t"<<game.player.inventory.items[i].description[1]
        <<"\t"<<game.player.inventory.items[i].description[2]<<endl;
    }
    fileSave << "[Game]" << endl;
    fileSave << "Seed" << "\t" << game.seed << endl;
    fileSave << "ReturnType" << "\t" << game.returnType << endl;
    fileSave << "inMap"<<"\t"<<game.inMap.x << "\t" << game.inMap.y <<endl;
    fileSave << "Rooms Moved" << "\t" << game.roomsMoved << endl;
    bool playerEmpty = false;
    for (size_t i = 0; !playerEmpty && i < 100; i++)
    {
        if (game.points[i] == 0 && game.nick[i].nick[0] == '\0')
        {
            playerEmpty = true;
        }else{
            fileSave << "Points" << "\t" << game.points[i] << endl;
            fileSave << "Nick" << "\t" << game.nick[i].nick[0] << game.nick[i].nick[1] << game.nick[i].nick[2] << endl;
        }
    }
    fileSave.close();
}