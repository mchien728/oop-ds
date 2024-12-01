#include <cstdlib>
#include <algorithm>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include "Player.h"
#include "Monster.h"

Monster::Monster():GameCharacter("unknown", "Monster", 0, 0, 0){
    //empty
}

Monster::Monster(string newName, int max, int attack, int defense): GameCharacter(newName, "Monster", max, attack, defense){
    //empty
    if(newName == "Final"){
        this->setSkill("死亡的質問");
    }
    if(newName == "Midterm"){
        this->setSkill("要停修嗎?");
    }
    if(newName == "HW" || newName == "Quiz"){
        this->setSkill("你是甚麼系的?");
    }
    else{
        this->setSkill("NULL");
    }
}

Monster::Monster(const Monster* now){
    this -> setName(now -> getName());
    this -> setTag(now -> getTag());
    this -> setMaxHealth(now -> getMaxHealth());
    this -> setCurrentHealth(now -> getCurrentHealth());
    this -> setAttack(now -> getAttack());
    this -> setDefense(now -> getDefense());
    if(now->getName() == "Final"){
        this->setSkill("死亡的質問");
    }
    if(now->getName() == "Midterm"){
        this->setSkill("要停修嗎?");
    }
    if(now->getName() == "HW" || now->getName() == "Quiz"){
        this->setSkill("你是甚麼系的?");
    }
    else{
        this->setSkill("");
    }
}

// record use
void Monster::listInfo(ofstream& out) const {
    Object::listInfo(out);
    out << getCurrentHealth() << " " << getMaxHealth() << " ";
    out << getAttack() << " " << getDefense() << endl;
}


void Monster::showInfo() const {
    cout << this -> getName() << '\n';
    int hp =  this -> getCurrentHealth();
    cout << "HP: " << hp << ", ";
    // Attack
    int at = this -> getAttack();
    cout << "Attack: " << at << ", ";
    // Defense
    int df = this -> getDefense();
    cout << "Defense: " << df << '\n';
}

bool Monster::skillOccur(){
    srand(time(NULL));
    int yes = rand()%3;
    if(yes == 2){
        return true;
    }
    return false;
}

int Monster::skillImplement(Player* players){
    if(this->getSkill() == "死亡的質問"){
        cout << "發動技能: " << this->getSkill() << """" << endl;
        cout << endl;
        string res;
        cout << "你平常有來上課嗎? (Y/N): ";
        cin >> res;
        res[0] = tolower(res[0]);
        sleep(1);

        if(res == "y"){
            if(players->getRole() == "死線趕不到戰士"){
                cout << endl;
                cout << "說謊的騙子! 因為說謊所以受到了教授的撻伐, 傷害+100" << endl;
                return 100;
            }
            else{
                cout << endl;
                cout << "恩真不錯, 認真上課的乖孩子(技能失效)" << endl;
                return 0;
            }
        }

        if(res == "n"){
            if(players->getRole() == "死線趕不到戰士"){
                cout << endl;
                cout << "恩真不錯, 雖然你不認真但人品挺好(技能失效)" << endl;
                return 0;
            }
            else{
                cout << endl;
                cout << "說謊的騙子! 因為說謊所以受到了教授的撻伐留下了陰影, poison + 20" << endl;
                players->setPoison(players->getPoison() + 20);
                return 0;
            }
        }
    }

    if(this->getSkill() == "要停修嗎?"){
        cout << "發動技能: " << this->getSkill() << """" << endl;
        cout << endl;
        cout << "為甚麼要做這種決定(淚), 你讓教授難過了所以攻擊力-50, 傷害+100" << endl;
        players->setAttack(players->getAttack()-50);
        return 100;
    }

    if(this->getSkill() == "你是甚麼系的?"){
        cout << "發動技能: " << this->getSkill() << """" << endl;
        cout << endl;
        string res;
        cout << "等一下同學你是甚麼系的(以xx系回答): ";
        cin >> res;
        if(res == "資工系"){
            cout << "喔...當掉, 傷害+50" << endl;
            return 50;
        } 
        else{
            cout << "喔...是這樣喔, 恭喜沒被盯上, 傷害只要+10" << endl;
            return 10;
        }
    }
    return 0;
}

bool Monster::triggerEvent(Object* obj){
    Player* player = dynamic_cast<Player*>(obj);
    if(player == NULL){
        return false;
    }

    while(1){
        cout << "\nAttacking " << *this << endl;
        cout << "C(c): Attack" << endl;
        cout << "R(r): Retreat" << endl;

        string command;
        cin >> command;
        command[0] = tolower(command[0]);

        if(command != "c" && command != "r"){
            cout << "Invalid command, try again?" << endl;
            continue;
        }
        if(command == "r"){
            cout << "You get W haha, are you scared?" << endl;
            break;
        }
        if(command == "c"){
            int newDamage = 0;
            int damage = this-> takeDamage((*player).getAttack());

            if(player->getHunger() > 0 && player->getCurrentRoom()->getType() == "Forest"){
                player->setHunger(max((player->getHunger()) - 10, 0));
                player->skillhelpOccur(player->getCurrentRoom());
            }
            else if(player->getHunger() > 0){
                player->setHunger(max((player->getHunger() - 5), 0));
            }
            else{
                player->setCurrentHealth(max((player->getCurrentHealth()) - 30, 0));
            }

            if(player->getThirst() > 0 && player->getCurrentRoom()->getType() == "Dessert"){
                player->setThirst(max((player->getThirst() - 10), 0));
                player->skillhelpOccur(player->getCurrentRoom());
            }
            else if(player->getThirst() > 0){
                player->setThirst(max((player->getThirst() - 5), 0));
            }
            else{
                player->setCurrentHealth(max((player->getCurrentHealth()) - 30, 0));
            }

            if(player->getPoison() > 0 && player->getCurrentRoom()->getType() == "Swamp"){
                player->setPoison((player->getPoison())+10);
                player->setCurrentHealth(max(player->getCurrentHealth() - (player->getPoison()), 0));
                player->skillhelpOccur(player->getCurrentRoom());
            }
            else if(player->getPoison() > 0){
                player->setCurrentHealth(max(player->getCurrentHealth() - (player->getPoison()), 0));
            }

            if(player->skillOccur() == 1){
                newDamage  = damage + player->skillImplement();
                while(newDamage < 0){
                    newDamage = damage + player->skillImplement();
                }
            }
            else{
                newDamage = damage;
            }

            int realDamage = min(this->getCurrentHealth(), newDamage);       //避免扣過頭
            this->setCurrentHealth(this->getCurrentHealth() - realDamage);
            cout << "You attack [Monster]" << this-> getName() << ", take "  << newDamage << " damage." << endl;

            if(this->checkIsDead()){
                cout << this->getName() << " is dead, you temporarily escape from getting E!" << endl;

                if(this->getName() == "Final"){
                    player->setisWin(1);
                }
                
                if(this->getName() == "Midterm"){
                    int newHealth = player->getCurrentHealth()+50;
                    int newAttack = player->getAttack()+50;
                    int newDefense = player->getDefense()+50;
                    player->setCurrentHealth(newHealth);
                    player->setAttack(newAttack);
                    player->setDefense(newDefense);

                    srand(time(NULL));
                    int isBuff = rand()%5;
                    if(isBuff == 3){
                        Item buff("不停修的勇氣", 50, 200, 50, 0, 0, -40);
                        cout << "Lucky! You get the buff [Item]""不停修的勇氣""" << endl;
                        buff.triggerEvent(player);
                    }
                    else{
                        Item foods("講座送的豪華便當", 50, 100, 10, 100, 0, 0);
                        cout << "You get [Item]" << foods.getName() << ", eat it hurry!" << endl;
                        foods.triggerEvent(player);
                    }
                }

                if(this->getName() == "Quiz"){
                    int newHealth = player->getCurrentHealth()+10;
                    int newAttack = player->getAttack()+10;
                    int newDefense = player->getDefense()+10;
                    player->setCurrentHealth(newHealth);
                    player->setAttack(newAttack);
                    player->setDefense(newDefense);

                    srand(time(NULL));
                    bool isBuff = rand()%2;
                    if(isBuff){
                        Item buff("短暫的信心", 40, 100, 80, 0, 0, -10);
                        cout << "Lucky! You get the buff""短暫的信心""" << endl;
                        buff.triggerEvent(player);
                    }
                    else{
                        Item foods("買一送一的小華堡", 30, 50, 30, 60, 0, 0);
                        cout << "You get [Item]" << foods.getName() << ", eat it hurry!" << endl;
                        foods.triggerEvent(player);
                    }
                }

                if(this->getName() == "HW"){
                    int newHealth = player->getCurrentHealth()+10;
                    int newAttack = player->getAttack()+10;
                    int newDefense = player->getDefense()+10;
                    player->setCurrentHealth(newHealth);
                    player->setAttack(newAttack);
                    player->setDefense(newDefense);

                    srand(time(NULL));
                    bool isBuff = rand()%2;
                    if(isBuff){
                        Item buff("越挫越勇的鬥志", 20, 50, 100, 0, 0, -20);
                        cout << "Lucky! You get the buff 越挫越勇的鬥志!" << endl;
                        buff.triggerEvent(player);
                        return true;             
                    }
                }
                return true;
            }
        }
        int newDamage = 0;
        int damage = player-> takeDamage(this->getAttack());
        if(this->skillOccur() == 1){
            newDamage  = damage + this->skillImplement(player);
            while(newDamage < 0){
                newDamage = damage + this->skillImplement(player);
            }
        }
        else{
            newDamage = damage;
        }
        int realDamage = min(player->getCurrentHealth(), newDamage);
        player->setCurrentHealth(player->getCurrentHealth() - realDamage);

        cout << "[Monster]" << this->getName() << " attack you, cause you " << newDamage << " damage!" << endl;
        if((*player).checkIsDead()){
            cout << "You got a big E, SEE YOU NEXT YEAR!" << endl;
            sleep(10);
            break;
        }
        cout << *player << endl;
    }
    return false;
}

ostream& operator<<(ostream& out, const Monster& mon) {
	out << "Monster: " << mon.getName() << '\n';
    int t = rand() % 5;
	// HP
    int hp = mon.getCurrentHealth();
    out << "    HP: " << hp - t << " ~ " << hp - t + 5 << ", ";

    // Attack
    int at = mon.getAttack();
    t = rand() % 5;
    out << "Attack: " <<  at - t << " ~ " << at - t + 5 << ", ";

    // Defense
    int df = mon.getDefense();
    t = rand() % 5;
    out << "Defense: " << df - t << " ~ " << df - t + 5;

	return out;
}
