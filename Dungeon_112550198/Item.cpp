#include <fstream>
#include "Item.h"

using namespace std;
Item::Item(): Object("", "it"){
}

Item::Item(string nam, int h, int a, int d, int hun, int thi, int poi): Object(nam, "Item") {
	this-> health = h;
	this-> attack = a;
	this-> defense = d;
	this-> hungerValue = hun;
	this-> thirstValue = thi;
	this-> poisonValue = poi;
}

ostream& operator<<(ostream& out, const Item& items) {
	out << items.getName() << " : ";
	out << items.getHealth() << " " << items.getAttack() << " " << items.getDefense() << " ";
	out << items.getHunger() << " " << items.getThirst() << " " << items.getPoison();
	out << "  (health/attack/defense/hunger/thirst/poison)";
	out << endl;
	return out;
}

// record use only
void Item::listInfo(ofstream& out) const {
	Object::listInfo(out);
	out << getHealth() << " " << getAttack() << " " << getDefense()  << " " << getHunger() << " " << getThirst()  << " "<< getPoison() << endl;
}

// Pick up Item
bool Item::triggerEvent(Object* obj) {
	Player *player = dynamic_cast<Player*>(obj);
    if (player == NULL){
		return false;
	}
	
	if(this->getName() == "Milktea"){
		//碰到就強制使用
		cout << "Oh, no! 你因為早餐店奶茶的魔力開始瘋狂拉肚子, poison + 20, 去找""你親近的人""要解藥吧!" << endl;
	}

	if(this->getName() == "被教授說絕對會考的考古"){
		cout << "Oh, no! 你因為堅信考古絕對會考而完全準備錯方向, 陷入混亂, poison + 40, 去找解藥吧!" << endl;
	}

	if(this->getName() == "Milk"){
		cout << "Congratulation! Poison歸零!" << endl;
	}

	if(this->getName() == "Blacktea"){
		cout << "Congratulation! 能力值提升!" << endl;
	}

	if(this->getName() == "BaconOmelet"){
		cout << "Congratulation! 能力值提升!" << endl;
	}

	if(this->getName() == "Hashbrown"){
		cout << "Congratulation! 能力值提升!" << endl;
	}

	if(this->getName() == "Sandwich"){
		cout << "Congratulation! 能力值提升!" << endl;
	}

	if(this->getName() == "Exercises"){
		cout << "Congratulation! 能力值提升!" << endl;
	}

	if(this->getName() == "EggTart"){
		cout << "Congratulation! 能力值提升!" << endl;
	}

	if(this->getName() == "FriedChicken"){
		cout << "Congratulation! 能力值提升!" << endl;
	}

	if(this->getName() == "捲捲薯條"){
		cout << "Congratulation! 能力值提升!" << endl;
	}

	if(this->getName() == "安格斯牛肉堡"){
		cout << "Congratulation! 能力值提升!" << endl;
	}
	cout << endl;
    (*player).addItem(*this);
	return true;
}

int Item::getHunger() const{
	return this-> hungerValue;
}

int Item::getThirst() const{
	return this-> thirstValue;
}

int Item::getPoison() const{
	return this-> poisonValue;
}

int Item::getHealth() const {
	return this -> health;
}

int Item::getAttack() const {
	return this -> attack;
}

int Item::getDefense() const {
	return this -> defense;
}

void Item::setHunger(int hun){
	this-> hungerValue = hun;
}

void Item::setThirst(int thi){
	this-> thirstValue = thi;
}

void Item::setPoison(int poi){
	this-> poisonValue = poi;
}

void Item::setHealth(int h) {
	this -> health = h;
}

void Item::setAttack(int a) {
	this -> attack = a;
}

void Item::setDefense(int d) {
	this -> defense = d;
}

