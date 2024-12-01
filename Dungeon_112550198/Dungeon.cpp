#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <cctype>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include "NPC.h"
#include "Room.h"
#include "Item.h"
#include "Object.h"
#include "GameCharacter.h"
#include "Player.h"
#include "Monster.h"
#include "Dungeon.h"

using namespace std;

Dungeon::Dungeon(){
    //empty
}

void Dungeon::createPlayer(string newName){
    srand(time(NULL));
    int guess = rand()%3;
    if(guess == 0){
        this->player = Player(newName, "死線趕不到戰士", 120, 180, 300);
        this->player.setSkill("擲筊\\|/");
        this->player.setCurrentRoom(&rooms[0]);
        this->player.setPreviousRoom(&rooms[0]);
        cout << "Oh no! You are ""死線趕不到戰士""! You are so close to be fail! God bless you \\|/.";
        
    }
    if(guess == 1){
        this->player = Player(newName, "平凡的普通大學生", 150, 200, 150);
        this->player.setSkill("寒窗苦讀");
        this->player.setCurrentRoom(&rooms[0]);
        this->player.setPreviousRoom(&rooms[0]);
        cout << "You are ""平凡的普通大學生""! You are safe right now! Continue to study hard or you may also fail." << endl;
        
    }
    if(guess == 2){
        this->player = Player(newName, "萬年書卷得主", 200, 250, 50);
        this->player.setSkill("心如止水");
        this->player.setCurrentRoom(&rooms[0]);
        this->player.setPreviousRoom(&rooms[0]);
        cout << "Wow! You are ""萬年書卷得主""! You are so lucky. Notice that not to be careless." << endl;
        
    }
}

vector<Monster*> loadMonster(){
    vector<Monster*> list_mons;
    list_mons.clear();

    ifstream file_read;
    file_read.open("Monsters.txt");
    if (!file_read.good()) {
		cout << "Monster information loads failed\n";
		exit(0);
	}

    string name;
    int health, attack, defense;
    while(file_read >> name){
        file_read >> health >> attack >> defense;
        file_read.ignore();
        list_mons.push_back(new Monster(name, health, attack, defense));
    }
    file_read.close();
    return list_mons;
}

vector<NPC*> loadsNpc() {
	vector<NPC*> list_npcs;
	list_npcs.clear();

	std::ifstream file_read;
	file_read.open("NPCs.txt");
	if (!file_read.good()) {
		cout << "NPC information loads failed\n";
		exit(0);
	}

	vector<Item> commodity; 
	string name, scr, itnam;
	int n, health, attack, defense, hun, thi, poi;
	while (file_read >> name) {
		file_read.ignore();
		file_read >> scr;
        file_read.ignore();
		file_read >> n;
		commodity.clear();
		while (n>0) {
            file_read.ignore();
			file_read >> itnam >> health >> attack >> defense;
            file_read >> hun >> thi >> poi;
			commodity.push_back(Item(itnam, health, attack, defense, hun, thi, poi));
            n--;
		}
		list_npcs.push_back(new NPC(name, scr, commodity));
        file_read.ignore();
	}
	file_read.close();
	return list_npcs;
}

void Dungeon::createMap(){
    ifstream file_read;
	file_read.open("map.txt");
	if (file_read.good() == 0) {
		cout << "Map file loads failed\n";
		exit(0);
	}
	int roomNum; 
    file_read >> roomNum;
	for (int i=0; i < roomNum; i++) {
		rooms.push_back(Room());
		rooms[i].setIndex(i + 1);
	}

	int x;
	for (int i = 0; i < roomNum; i++) {
        file_read.ignore();
        file_read >> x; 
        if (x != -1){
            rooms[i].setUpRoom(&rooms[x]); // up
        }
        file_read >> x; 
        if (x != -1){
            rooms[i].setDownRoom(&rooms[x]); // down
        }
        file_read >> x; 
        if (x != -1){
            rooms[i].setLeftRoom(&rooms[x]); // left
        }
        file_read >> x;
        if (x != -1){
            rooms[i].setRightRoom(&rooms[x]); // right
        }
	}
	file_read.close();

	rooms[roomNum - 1].pushObject(monsters[0]); // Boss 
	rooms[roomNum - 1].setIsExit(true);

	int ptrNpc = 0;
    int ptrMons = 1;
    for (int i=1; i < roomNum; i+=rand() % 3) {
		rooms[i].pushObject(new Monster(monsters[ptrMons]));
        ptrMons++;
		if (ptrMons == monsters.size()){
            ptrMons = 2;
	    }
    }
	for (int i=0; i < roomNum; i+=rand() % 3) {
		rooms[i].pushObject(new NPC(npcs[ptrNpc]));
        ptrNpc++;
		if (ptrNpc == npcs.size()){
            ptrNpc = 3;
	    }
    }
}

void Dungeon::handleMovement(){
    Room* current = player.getCurrentRoom();
    Room* prev = player.getPreviousRoom();

    Room* up = (*current).getUpRoom();
    Room* down = (*current).getDownRoom();
    Room* left = (*current).getLeftRoom();
    Room* right = (*current).getRightRoom();
    if(up != NULL){
        cout << "A(a): Go to up room." << endl;
    }
    if(down != NULL){
        cout << "B(b): Go to down room." << endl;
    }
    if(left != NULL){
        cout << "C(c): Go to left room." << endl;
    }
    if(right != NULL){
        cout << "D(d): Go to right room." << endl;
    }
    bool isExit = (*current).getIsExit();
    if(isExit == 1){
        cout << "F(f): Finish the game." << endl;
        //cout << "HAHA" << player.getisWin();
    }

    string direction;
    cin >> direction;
    direction[0] = tolower(direction[0]);
    if(up != NULL && direction == "a"){
        player.setCurrentRoom(up);
    }
    if(down != NULL && direction == "b"){
        player.setCurrentRoom(down);
    }
    if(left != NULL && direction == "c"){
        player.setCurrentRoom(left);
    }
    if(right != NULL && direction == "d"){
        player.setCurrentRoom(right);
    }
    if(direction == "f" && isExit == 1 && player.getisWin() == 1){
        cout << "Congratulation! You successfully escape from 交作業大學!" << endl;
        exit(0);
    }
    int r = rand()%5, tmp = rand()%10;
	if (r < tmp && prev != player.getCurrentRoom()) {
		player.getCurrentRoom() -> pushObject(new Monster(monsters[rand() % (monsters.size() - 1) + 1]));
	}
	r = rand()%5, tmp = rand()%10;
	if (r < tmp && prev != player.getCurrentRoom()) {
		player.getCurrentRoom() -> pushObject(new NPC(npcs[rand() % (npcs.size() - 2) + 2]));
	}
}

bool Dungeon::handleAttack(string name){
    Room* rooms = player.getCurrentRoom();
    for(auto i: (*rooms).getObjects()){
        Monster* mons = dynamic_cast<Monster*>(i);
        if(mons == NULL){
            continue;
        }
        if((*i).getName() == name){
            Object* now = mons;
            if((*now).triggerEvent(&player) == 1){
                (*rooms).popObject(i);
            }
            return true;
        }
    }
    cout << "No monster's name is it, so embarrassed." << endl;
    return false;
}

bool Dungeon::handleCommunicate(string name){
    Room* rooms = player.getCurrentRoom();
    for(auto i: (*rooms).getObjects()){
        NPC* npcs = dynamic_cast<NPC*>(i);
        if(npcs == NULL){
            continue;
        }
        if((*i).getName() == name){
            Object* now = npcs;
            if((*now).triggerEvent(&player) == 1){
                (*rooms).popObject(i);
            }
            return true;
        }
    }
    cout << "No NPC's name is it, so embarrassed." << endl;
    return false;
}

void Dungeon::startGame(){
    srand(time(NULL));

    Record rec;
    cout << "Loading......Please wait...";
    this->monsters = loadMonster();
    this->npcs = loadsNpc();
    cout << "Finished!" << endl;
    sleep(1);

    string name;
    cout << "Enter your name: ";
    cin >> name;
    if (rec.checkFile(name)) {
		cout << "\nPrevious records found, loading....\n";
		rec.loadFromFile(name, &player, rooms);
        
		sleep(1);
        cout << this->player;
        sleep(1);
	}
    else{
        cout << "\nNo before record(s), creating..... ";
		this -> createMap();
        cout << "Finished\n";
	    this -> createPlayer(name);
		sleep(1);
        cout << this->player;
    }
    
	
    this->runDungeon();
}

bool Dungeon::checkGameLogic(){
    if(this->player.checkIsDead() == 1){
        return false;
    }
    return true;
}

void Dungeon::chooseAction(){
    cout << "What you want to do now: " << endl;
    cout << "S(s): Show the status now" << endl;
    cout << "L(l): List the item(s) you have" << endl;
    cout << "M(m): Move to another room" << endl;
    if(player.getCurrentRoom()->isMonster() == 1){
        cout << "A(a): Attack" << endl;
    }
    if(player.getCurrentRoom()->isNPC() == 1){
        cout << "C(c): Chat with someone" << endl;
    }
    cout << "E(e): Exit the game and save record." << endl;
}

bool Dungeon::checkAction(string action){
    if(action.length() != 1){
        return false;
    }
    if(action == "s") return true;
    if(action == "l") return true;
    if(action == "m") return true;
    if(action == "a") return true;
    if(action == "c") return true;
    if(action == "e") return true;

    return false;
}

void Dungeon::runDungeon(){
    while(checkGameLogic() == 1){
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        if(player.getCurrentRoom()->getType() == "Desert"){
                cout << "You are enter Desert! When you attack, your thirst will decrease more!" << endl;
                cout << endl;
            }
            if(player.getCurrentRoom()->getType() == "Forest"){
                cout << "You are enter Forest! When you attack, your hunger will decrease more!" << endl;
                cout << endl;
            }
            if(player.getCurrentRoom()->getType() == "Swamp"){
                cout << "You are enter Swamp! When you attack, your poison will increase!" << endl;
                cout << endl;
            }
            if(player.getCurrentRoom()->getType() == "Common"){
                cout << "Lucky! This room is common!" << endl;
                cout << endl;
            }
        cout << *player.getCurrentRoom() << endl;
        cout << endl;

        chooseAction();
        string action;
        cin >> action;
        action[0] = tolower(action[0]);
        while(checkAction(action) == 0){
            cout << "Invalid input, try again?" << endl;
            std::cin >> action;
        }
        if(action == "s"){
            cout << player << endl;
        }

        if(action == "l"){
            vector<Item> items = player.getInventory();
            if(items.size() == 0){
                cout << "Oh, you have nothing in your backpack QAQ" << endl;
            }
            for(auto i: items){
                cout << i;
            }
            cout << endl;
        }

        if(action == "m"){
            this->handleMovement();
        }

        if(action =="a"){
            (player.getCurrentRoom())->showMonster();
            string attackName;
            do{
                cout << endl;
                cout << "Enter who you want to attack, or you can also enter \"e\" to exit: ";
                std::cin >> attackName;
                if(attackName == "e"){
                    break;
                }
            }while(this->handleAttack(attackName) == 0);

        }

        if(action == "c"){
            (player.getCurrentRoom())->showNPC();
            string talkName;
            do{
                cout << endl;
                cout << "Enter who you want to chat with, or you can also enter \"e\" to exit: ";
                std::cin >> talkName;
                if(talkName == "e"){
                    break;
                }
            }while(this->handleCommunicate(talkName) == 0);
        }

        if(action == "e"){
            Record rec;
            rec.saveToFile(&player, rooms);
            break;
        }
        
        cout << "Loading......" << endl;
        sleep(2);
    }

}


