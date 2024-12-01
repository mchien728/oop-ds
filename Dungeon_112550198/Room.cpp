#include <cstdlib>
#include <algorithm>
#include <unistd.h>
#include <time.h>
#include "Room.h"
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
using namespace std;

Room::Room(){
    upRoom = NULL;
    downRoom = NULL;
    leftRoom = NULL;
    rightRoom = NULL;

    isExit = false;
	index = -1;
    objects.clear();

    srand(time(NULL));
    int choose = rand()%4;
    if(choose == 0){
        this->type = "Desert";
        this->skill = "Sandstorms";
        this->help = "Oasis";
    }
    if(choose == 1){
        this->type = "Forest";
        this->skill = "Wildlife";
        this->help = "Lake";
    }
    if(choose == 2){
        this->type = "Swamp";
        this->skill = "Trapped";
        this->help = "Crocodile";
    }
    if(choose == 3){
        this->type = "Common";
        this->skill = "NULL";
        this->help = "NULL";
    }
}

Room::Room(bool isExit, int i, vector<Object*> v){
    upRoom = NULL;
    downRoom = NULL;
    leftRoom = NULL;
    rightRoom = NULL;

    this -> isExit = isExit;
	this -> index = i;
	this -> objects = v;
    
    srand(time(NULL));
    int choose = rand()%4;
    if(choose == 0){
        this->type = "Desert";
        this->skill = "Sandstorms";
        this->help = "Oasis";
    }
    if(choose == 1){
        this->type = "Forest";
        this->skill = "Wildlife";
        this->help = "Lake";
    }
    if(choose == 2){
        this->type = "Swamp";
        this->skill = "Trapped";
        this->help = "Crocodile";
    }
    if(choose == 3){
        this->type = "Common";
        this->skill = "NULL";
        this->help = "NULL";
    }
}

void Room::pushObject(Object* put){
    (this->objects).push_back(put);
}

bool Room::popObject(Object* done){
    bool yes = 0;
    vector<Object*> tmp;
    tmp.clear();
    for(auto i: objects){
        if(i == done){
            yes = 1;
            continue;
        }
        tmp.push_back(i);
    }
    this-> setObjects(tmp);

    return yes;
}

void Room::setUpRoom(Room* current){
    this-> upRoom = current;
}

void Room::setDownRoom(Room* current){
    this-> downRoom = current;
}

void Room::setLeftRoom(Room* current){
    this-> leftRoom = current;
}

void Room::setRightRoom(Room* current){
    this-> rightRoom = current;
}

void Room::setIsExit(bool yes){
    this-> isExit = yes;
}

void Room::setIndex(int ind){
    this-> index = ind;
}

void Room::setObjects(vector<Object*> v){
    this-> objects = v;
}

void Room::setType(string types){
    this->type = types;
}

void Room::setSkill(string skills){
    this->skill = skills;
}

void Room::setHelp(string helps){
    this->help = helps;
}

Room* Room::getUpRoom() const{
    return this-> upRoom;
}

Room* Room::getDownRoom() const{
    return this-> downRoom;
}

Room* Room::getLeftRoom() const{
    return this-> leftRoom;
}

Room* Room::getRightRoom() const{
    return this-> rightRoom;
}

vector<Object*> Room::getObjects() const{
    return this->objects;
}

bool Room::getIsExit() const{
    return this->isExit;
}

int Room::getIndex() const{
    return this->index;
}

string Room::getType() const{
    return this->type;
}

string Room::getSkill() const{
    return this->skill;
}

string Room::getHelp() const{
    return this->help;
}

void Room::showMonster() const{
    bool yes = 0;
    for(auto i: objects){
        Monster* mons = dynamic_cast<Monster*>(i);
        if(mons !=NULL){
            yes = 1;
            cout << *mons << endl;
        }
    }
    if(yes == 0){
            cout << "Oh Yeah! There is no target can attack." << endl;
        }
}
bool Room::isNPC(){
    for(auto i: objects){
        NPC* npcs = dynamic_cast<NPC*>(i);
        if(npcs !=NULL){
            return true;
        }
    }
    return false;
}

bool Room::isMonster(){
    for(auto i: objects){
        Monster* mons = dynamic_cast<Monster*>(i);
        if(mons !=NULL){
            return true;
        }
    }
    return false;
}


void Room::showNPC() const{
    bool yes = 0;
    for(auto i: objects){
        NPC* npcs = dynamic_cast<NPC*>(i);
        if(npcs !=NULL){
            yes = 1;
            cout << *npcs << endl;
        }
    }
    if(yes == 0){
            cout << "Oops! No one can communicate with QAQ." << endl;
    }
}


ostream& operator<<(ostream& out, const Room& rooms) {
	out << "Room Info:\n";
	if (rooms.getIsExit()) out << "There is a Exit!!\n";

	vector<Object*> v = rooms.getObjects();
	if (v.size()){
        for (auto i : v) {
			Monster* mons = dynamic_cast<Monster*>(i);
			NPC* npcs = dynamic_cast<NPC*>(i);
			Item* items = dynamic_cast<Item*>(i);

			if (mons != NULL){
                out << *mons << endl;
            }
			if (npcs != NULL){
                out << *npcs << '\n';
            }
			if (items != NULL){
                out << *items << '\n';
            }
		}
    }
	else
		out << "Nothing in this room!";

	return out;
}
