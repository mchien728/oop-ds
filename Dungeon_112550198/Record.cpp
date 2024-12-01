#include <unistd.h>
#include <fstream>
#include "Record.h"

using namespace std;

Record::Record(){
    //empty
}

void Record::savePlayer(Player* now, ofstream& out){
    now-> listInfo(out);
    out << now->getRole() << endl;
    out << now->getMaxHealth() << " " << now->getCurrentHealth() << " " << now->getAttack() << " " << now->getDefense() << endl;
    out << now->getHunger() << " " << now->getThirst() << " " << now->getPoison() << endl;

    Room* current = now->getCurrentRoom();
    Room* prev = now->getPreviousRoom();
    out << current-> getIndex() << " ";
	out << prev-> getIndex() << endl;

    vector<Item> inventory = (*now).getInventory();
	out << inventory.size() << endl;
	for (auto i : inventory) {
		i.listInfo(out);
	}
}

void Record::saveRooms(vector<Room>& v, ofstream& out){
    out << v.size() << endl;
    for (auto i : v) {
		out << (i.getIsExit() ? 1 : 0) << endl;

		out << i.getType() << " " << i.getSkill() << " " << i.getHelp() << endl;
        // connect room
		out << (i.getUpRoom()    == NULL ? -1 : (*(i.getUpRoom())).getIndex()) << " ";
		out << (i.getDownRoom()  == NULL ? -1 : (*(i.getDownRoom())).getIndex()) << " ";
		out << (i.getLeftRoom()  == NULL ? -1 : (*(i.getLeftRoom())).getIndex()) << " ";
		out << (i.getRightRoom() == NULL ? -1 : (*(i.getRightRoom())).getIndex()) << endl;
	
		vector<Object*> e = i.getObjects();
		out << e.size() << endl;
		for(int k=0; k<e.size(); k++){
			NPC* npcs = dynamic_cast<NPC*>(e[k]);
			Monster* mons = dynamic_cast<Monster*>(e[k]);
			if(npcs != NULL){
				npcs->listInfo(out);
			}
			if(mons != NULL){
				mons->listInfo(out);
			}
		}
    }
}

void Record::loadPlayer(Player* now, ifstream& in, vector<Room>& rooms){
    string tag, name, role;
    in >> tag >> name;
	in.ignore();
    in >> role;
	in.ignore();

    int maxHealth, currentHealth, attack, defense;
    in >> maxHealth >> currentHealth >> attack >> defense;
	in.ignore();
    int hungerValue, thirstValue, poisonValue;
    in >> hungerValue >> thirstValue >> poisonValue;
	in.ignore();
    *now = *(new Player(name, role, maxHealth, attack, defense));
    now-> setCurrentHealth(currentHealth);
    now-> setHunger(hungerValue);
    now-> setThirst(thirstValue);
    now-> setPoison(poisonValue);

    int curRoomid, prevRoomid;
    in >> curRoomid >> prevRoomid;
	in.ignore();
    
    now-> setCurrentRoom(&rooms[curRoomid-1]);
    now-> setPreviousRoom(&rooms[prevRoomid-1]);

    vector<Item> inventory;
	int t; in >> t;
	while (t--) {
		in >> tag >> name;
		in.ignore();
		int h, a, d, hun, thi, poi; 
        in >> h >> a >> d;
		in >> hun >> thi >> poi;
		in.ignore();
		inventory.push_back(Item(name, h, a, d, hun, thi, poi));
	}
	now -> setInventory(inventory, false);
}

void Record::loadRooms(vector<Room>& rooms, ifstream& in){
    int n;
    in >> n;
	in.ignore();
    for(int i=0; i<n; i++){
        rooms.push_back(Room());
        rooms[i].setIndex(i+1);
    }
    for (int i = 0; i < n; i++) {
		int isExit; 
        in >> isExit;
		rooms[i].setIsExit((isExit == 1 ? true : false));

		in.ignore();
		string type, skill, help;
		in >> type >> skill >> help;
		rooms[i].setType(type);
		rooms[i].setSkill(skill);
		rooms[i].setHelp(help);
		in.ignore();

        int up, down, left, right; 
        in >> up >> down >> left >> right;
		in.ignore();
		if (up != -1){
            rooms[i].setUpRoom(&rooms[up - 1]);
        }
		if (down != -1){
            rooms[i].setDownRoom(&rooms[down - 1]);
        }
		if (left != -1){
            rooms[i].setLeftRoom(&rooms[left - 1]);
        }
		if (right != -1){
            rooms[i].setRightRoom(&rooms[right - 1]); 
        }

        int objNum;
        in >> objNum;
		in.ignore();
        vector<Object*> objs; 
        objs.clear();

		while (objNum--) {
			string tag, name; 
            in >> tag >> name;
			in.ignore();

			if (tag == "Monster") {
				int cth, mxh, att, def;
				in >> cth >> mxh >> att >> def;
				objs.push_back(new Monster(name, mxh, att, def));
				
				Monster* mos = dynamic_cast<Monster*>(objs.back());
				(*mos).setCurrentHealth(cth);
			}

			if (tag == "NPC") {
				string scr; 
                in >> scr;
				in.ignore();
				int size; 
                in >> size;
				in.ignore();

				vector<Item> comm; 
				comm.clear();
				for (int j = 1; j <= size; j++) {
					string itnam, ittag; 
                    in >> ittag >> itnam;
					in.ignore();
					int h, a, d, hun, thi, poi; 
        			in >> h >> a >> d;
					in >> hun >> thi >> poi;
					comm.push_back(Item(itnam, h, a, d, hun, thi, poi));
				}
				objs.push_back(new NPC(name, scr, comm));
			}

			if (tag == "Item") {
				int h, a, d, hun, thi, poi; 
				in >> h >> a >> d;
				in >> hun >> thi >> poi;
				objs.push_back(new Item(name, h, a, d, hun, thi, poi));
			}
		}
		rooms[i].setObjects(objs);
	}
}


void Record::loadFromFile(string name, Player* now, vector<Room>& v) {
	ifstream file_read;
	
	cout << "Map ........ ";
	file_read.open((name + "_map.txt").c_str());
	loadRooms(v, file_read);
	file_read.close();
	sleep(1);

	cout << "Finished\n";


	cout << "User ....... ";

	file_read.open((name + "_usr.txt").c_str());
	loadPlayer(now, file_read, v);
	file_read.close();
	sleep(1);

	cout << "Finished\n";
}

// save record
void Record::saveToFile(Player* now, vector<Room>& v) {
	string name = (*now).getName();
	std::ofstream out;

	out.open((name + "_map.txt").c_str());
	this -> saveRooms(v, out);
	out.close();

	out.open((name + "_usr.txt").c_str());
	this -> savePlayer(now, out);
	out.close();

	cout << "\nRecord Saved\n";
}

bool Record::checkFile(string name){
    std::ifstream file_read;

	string fileName = name + "_usr.txt";
	file_read.open((fileName).c_str());
	if (!file_read.good()){
        return false;
    }
	file_read.close();

	fileName = name + "_map.txt";
	file_read.open((fileName).c_str());
	if (!file_read.good()){
        return false;
    }
	file_read.close();
	
	return true;
}

