#include <iostream>
#include <string>
#include <vector>
#include "Dungeon.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"


using namespace std;

int main(){
    cout << "Welcome to 交作業大學!" << endl;
    Dungeon dungeon;
    dungeon.startGame();

    cout << "Hope to see you again!" << endl;
    return 0;
}
