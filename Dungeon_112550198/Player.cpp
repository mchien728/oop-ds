#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <time.h>
#include "Monster.h"
#include "Room.h"
#include "GameCharacter.h"
#include "Player.h"

using namespace std;
Player::Player(){
    //empty
}

Player::Player(string startName, string startRole, int max, int attack, int defense):GameCharacter(startName, "Student", max, attack, defense){
    this->role = startRole;
    this-> currentRoom = NULL;
    this-> previousRoom = NULL;
    this->hungerValue = 100;
    this->thirstValue = 100;
    this->poisonValue = 0;
    this->inventory.clear();
}

void Player::addItem(Item items){
    this -> increaseStates(items.getHealth(), items.getAttack(), items.getDefense(), items.getHunger(), items.getThirst(), items.getPoison());
    //cout << items.getHealth() << items.getAttack() << items.getDefense() << endl;
    inventory.push_back(items);
}

void Player::increaseStates(int upHealth, int upAttack, int upDefense, int upHunger, int upThirst, int upPoison){
    if(upHealth > 0){
        int newHealth = min(getMaxHealth(), getCurrentHealth()+upHealth);
        this-> setCurrentHealth(newHealth);
    }
    else{
        int newHealth = max(0, getCurrentHealth()+upHealth);
        this-> setCurrentHealth(newHealth);
    }
    if(upAttack > 0){
        int newAttack = getAttack() + upAttack;
        this-> setAttack(newAttack);
    }
    else{
        int newAttack = max(0, getAttack() + upAttack);
        this-> setAttack(newAttack);
    }

    if(upDefense > 0){
        int newDefense = getDefense() + upDefense;
        this-> setDefense(newDefense);
    }
    else{
        int newDefense = max(0, getDefense() + upDefense);
        this-> setDefense(newDefense);
    }

    if(upHunger > 0){
        int newHunger = min(100, getHunger()+upHunger);
        this-> setHunger(newHunger);
    }
    else{
        int newHunger = max(0, getHunger()+upHunger);
        this-> setHunger(newHunger);
    }

    if(upThirst > 0){
        int newThirst = min(100, getThirst()+upThirst);
        this-> setThirst(newThirst);
    }
    else{
        int newThirst = max(0, getThirst()+upThirst);
        this-> setThirst(newThirst);
    }

    int newPoison = max(0, getPoison() + upPoison);
    this-> setPoison(newPoison);
}

void Player::changeRoom(Room* change){
    this-> previousRoom = this-> currentRoom;
    this-> currentRoom = change;
}

bool Player::isHunger(){
    if(getHunger() <= 0){
        return true;
    }
    return false;
}

bool Player::isThirst(){
    if(getThirst() <= 0){
        return true;
    }
    return false;
}

bool Player::isPoison(){
    if(getPoison() > 0){
        return true;
    }
    return false;
}

bool Player::triggerEvent(Object* obj){
    return false;
}

void Player::setCurrentRoom(Room* now){
    this-> setPreviousRoom(this-> currentRoom);
    this-> currentRoom = now;
}

void Player::setPreviousRoom(Room* old){
    this-> previousRoom = old;
}

void Player::setInventory(vector<Item> items, bool yes){    //是否要輸出獲得item的對話(可能只是record)
    if(yes){
        for(auto i: items){
            i.triggerEvent(this);
        }
        this-> inventory = items;
    //確保 Player 物件的 inventory 成員在 setInventory 方法執行後包含了 items 向量中的所有物品
    }
    else if(!yes){
        this->inventory = items;
    }     
   
}

bool Player::skillOccur(){
    srand(time(NULL));
    int yes = rand()%5;
    if(yes > 2){
        return true;
    }
    return false;
}

int Player::skillImplement(){
    if(this->getSkill() == "擲筊\\|/"){
        cout << "發動技能: " << this->getSkill() << """" << endl;
        cout << endl;
        cout << "從1-3中選個數字: ";
        string num;
        cin >> num;
        if(num == "1"){
            cout << "抱佛腳成功, 追加攻擊!" << endl;
            cout << endl;
            int damage2 = this-> takeDamage(this->getAttack());
            return damage2;
        }
        if(num == "2"){
            cout << "大摔車, 減少我方攻擊" << endl;
            cout << endl;
            int damageDelete = (-1)*(this-> takeDamage(this->getAttack()));
            return damageDelete;
        }
        if(num == "3"){
            if(this->getPoison()>0){
                cout << "Lucky! Poison歸零!" << endl;
                cout << endl;
                this->setPoison(0);
                cout << this;
            }
            else{
                cout << "Oh, 你健康的很呢, 看來不需要幫助了" << endl;
            }
            return 0;
        }
    }
    if(this->getSkill() == "寒窗苦讀"){
        cout << "發動技能: " << this->getSkill() << """" << endl;
        cout << endl;
        cout << "努力是有回報的! 整體能力值上升" << endl;
        cout << endl;
        this->increaseStates(50, 30, 30, 0, 0, 0);
        cout << *this;
        return 0;
    }
    if(this->getSkill() == "心如止水"){
        cout << "發動技能: " << this->getSkill() << """" << endl;
        if(getPoison() > 0){
            cout << endl;
            cout << "你已經進入超人的境界, poison歸零!" << endl;
            cout << endl;
            this->setPoison(0);
            cout << *this;
            return 0;
        }
        else{
            cout << endl;
            cout << "你已經進入超人的境界, hunger和thirst滿點!" << endl;
            cout << endl;
            this->setHunger(100);
            this->setThirst(100);
            cout << *this;
            return 0;
        }
    }
    return 0;
}

void Player::setRole(string newRole){
    this->role = newRole; 
}

void Player::setHunger(int newHunger){
    this->hungerValue = newHunger;
}

void Player::setThirst(int newThirst){
    this->thirstValue = newThirst;
}

void Player::setPoison(int newPoison){
    this->poisonValue = newPoison;
}

Room* Player::getCurrentRoom() const{
    return this-> currentRoom;
}

Room* Player::getPreviousRoom() const{
    return this-> previousRoom;
}

vector<Item> Player::getInventory() const{
    return this-> inventory;
}

string Player::getRole() const{
    return this->role;
}

int Player::getHunger() const{
    return this->hungerValue;
}

int Player::getThirst() const{
    return this->thirstValue;
}

int Player::getPoison() const{
    return this->poisonValue;
}

void Player::setisWin(bool y){
    this-> isWin = y;
}

bool Player::getisWin() const{
    return this-> isWin;
}

void Player::skillhelpOccur(Room* rooms){
    srand(time(NULL));
    int chance = rand()%10;
    if(chance > 6){
        roomskillImplement(rooms);
    }
    else if(chance < 3){
        roomHelpImplement(rooms);
    }
}

void Player::roomskillImplement(Room* rooms){
    if(rooms->getSkill() == "Sandstorms"){
        cout << "房間特性[Sandstorms]發動: hunger-20, thirst-40!" << endl;
        increaseStates(0, 0, 0, -20, -40, 0);
    }
    if(rooms->getSkill() == "Wildlife"){
        cout << "房間特性[Wildlife]發動: [Monster]Tiger 加入戰局!" << endl;
        Monster* tiger = new Monster("Tiger", 100, 50, 50);
        rooms->pushObject(tiger);
    }
    if(rooms->getSkill() == "Trapped"){
        cout << "房間特性[Trapped]發動: 行動受阻, attack-50, defense-30" << endl;
        increaseStates(0, -50, -30, 0, 0, 0);
    }
}

void Player::roomHelpImplement(Room* rooms){
    if(rooms->getHelp() == "Oasis"){
        cout << "房間特性[Oasis]發動: thirst+20!" << endl;
        increaseStates(0, 0, 0, 0, 20, 0);
    }
    if(this->getSkill() == "Lake"){
        cout << "房間特性[Lake]發動: thirst+40" << endl;
        increaseStates(0, 0, 0, 0, 40, 0);
    }
    if(this->getSkill() == "Cro"){
        cout << "房間特性[Crocodile]發動: 善良的crocodile願意送你一程, 保存體力, hunger+20. thirst+10" << endl;
        increaseStates(0, 0, 0, 20, 10, 0);
    }
}


ostream& operator<<(ostream& out, const Player& p) {
    cout << p.getName() << "'s Status:\n";
    // Role
    out << "Role: " << p.getRole() << endl;
    // HP
    out << "HP: " << p.getCurrentHealth() << "/";
    out << p.getMaxHealth() << endl;
    // Attack
    out << "Attack: " << p.getAttack() << endl;
    // Defense  
    out << "Defense: " << p.getDefense() << endl;
    // Hunger
    out << "Hunger: " << p.getHunger() << endl;
    // Thirst
    out << "Thirst: " << p.getThirst() << endl;
    // Poison
    out << "Poison: " << p.getPoison() << endl;
    return out;
}