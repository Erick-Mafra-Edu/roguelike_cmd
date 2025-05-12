#include <iostream>
#include <fstream>
using namespace std;
// void AllItems(Inventory &inventory){
//     Items sword;
//     // sword.durability = 100; // Para uma possível atualização futura
//     sword.quantity = 1;
//     sword.damage = 10;
//     sword.type = Items::weapon;
//     sword.art = "      .         \n"
//         "     /:\\    (\"\"\")\n"
//         "     |:|     III\n"
//         "     |:|     III\n"
//         "     |:|     III\n"
//         "     |:|   __III__\n"
//         "     |:| /:-.___,-:\\\n"
//         "     |:| \\]  |:|  [/\n"
//         "     |:|     |:|\n"
//         "     |:|     |:|\n"
//         "     |:|     |:|\n"
//         " /]  |:|  [\\ |:|\n"
//         " \\:-'\"\"\"`-:/ |:|\n"
//         "   \"\"III\"\"   |:|\n"
//         "     III     |:|\n"
//         "     III     |:|\n"
//         "     III     |:|\n"
//         "    (___)    \\:/\n"
//         "              \"\n";
//     sword.midX = 16/2;
//     sword.midY = 19/2;
//     inventory.items[0] = sword;
//     Items potion;
//     potion.type = Items::consumables;
//     potion.art = 
//     "   _\n"
//     "  |=|\n"
//     "  | |\n"
//     "  | |\n"
//     " /   \\\n"
//     ".     .\n"
//     "|-----|\n"
//     "|     |\n"
//     "|-----|\n";
//     potion.midX = 7/2;
//     potion.midY = 10;
//     inventory.items[1] = potion;
//     Items apple;
//     apple.type = Items::consumables;
//     apple.art = "     ,--./,-.\n"
//                 "    / #      \\\n"
//                 "   |          |\n"
//                 "    \\        /   \n"
//                 "     `._,._,'\n";
//     apple.midX = 15/2;
//     inventory.items[2]=apple;
//     Items shield;
//     // shield.durability = 100; // Para uma possível atualização possível
//     shield.quantity=1;
//     shield.type = Items::armor;
//     shield.art = "|\\===============/|\n"
//                  "| \\_____________/ |\n"
//                  "|      _____      |\n"
//                  "|     |     |     |\n"
//                  "|     |     |     |\n"
//                  "|  ====     ====  |\n"
//                  "|  ||         ||  |\n"
//                  "|  ||         ||  |\n"
//                  "|  ====     ====  |\n"
//                  "|    ||     ||    |\n"
//                  "|    ||     ||    |\n"
//                  "|    ||     ||    |\n"
//                  "|    ||     ||    |\n"
//                  "|    =========    |\n"
//                  "|=================|\n";
//     shield.midX = 19/2;
//     shield.midY = 15/2;
//     inventory.items[3] = shield;
//     inventory.size = 4;
// }
int saveGame(Game &game){
    //for testing i have used All Items Function
    //AllItems(test.player.inventory);
    ofstream fileSave("gameSave.save");
    fileSave << "[Roguelike ASCII]"<<endl;
    fileSave << "[Player]"<<endl;
    fileSave << "Health"<<"\t"<<game.player.health<<endl;
    fileSave << "Damage"<<"\t"<<game.player.damage<<endl;
    fileSave << "Position"<<"\t"<<game.player.position.X<<"\t"<<game.player.position.Y<<endl;
    fileSave << "[Inventory]"<<endl;
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
    fileSave << "Points" << "\t" << game.points << endl;
    fileSave << "Rooms Moved" << "\t" << game.roomsMoved << endl;

    fileSave.close();
}