#include <fstream>
#include "NPC.h"

NPC::NPC(): GameCharacter("unknown", "NPC", 20, 20, 50){
    //empty
}

NPC::NPC(string startname, string script, vector<Item> v):GameCharacter(startname, "NPC", 20, 20, 50){
    this->script = script;
    this->commodity = v;
}

NPC::NPC(const NPC* now) {
	this -> setName(now -> getName());
    this -> setTag(now -> getTag());
    this -> setMaxHealth(now -> getMaxHealth());
    this -> setCurrentHealth(now -> getCurrentHealth());
    this -> setAttack(now -> getAttack());
    this -> setDefense(now -> getDefense());
    this -> setCommodity(now -> getCommodity());
    this -> setScript(now -> getScript());
}

void NPC::listCommodity(){
    cout << "Number of item(s): " << commodity.size() << endl; 
    for(auto i: commodity){
        cout << i.getName() << " : ";
	    cout << i.getHealth() << " " << i.getAttack() << " " << i.getDefense() << " ";
	    cout << i.getHunger() << " " << i.getThirst() << " " << "?";
	    cout << "  (health/attack/defense/hunger/thirst/poison)" << endl;
    }
}

bool NPC::triggerEvent(Object* obj){
    Player* players = dynamic_cast<Player*>(obj);
    if(players == NULL){
        return false;
    }
    cout << "Oh! You encounter [NPC]" << this->getName() << ", pick one item below!" << endl;
    listCommodity();

    string itemName;
    cin >> itemName;
    bool ok;
    vector<Item> temp;
    temp.clear();
    for(auto i: commodity){
        if(i.getName() == itemName){
            ok = i.triggerEvent(players);
            continue;
        }
        temp.push_back(i);
    }

    if(ok){
        this->setCommodity(temp);
        return (this->commodity.size() == 0);
    }

    cout << "What that item? I can't find." << endl;
    return false;
}

void NPC::setScript(string newScript){
    this->script = newScript;
}

void NPC::setCommodity(vector<Item> v){
    this->commodity = v;
}

string NPC::getScript() const{
    return this->script;
}

vector<Item> NPC::getCommodity() const{
    return this->commodity;
}

// record use only
void NPC::listInfo(ofstream& out) const {
	Object::listInfo(out);
	out << this->getScript() << endl << commodity.size() << endl;
	for (auto i : commodity) {
		i.listInfo(out);
	}
}

ostream& operator<<(ostream& out, const NPC& npc) {
	out << "NPC: " << npc.getName();
	return out;
}
