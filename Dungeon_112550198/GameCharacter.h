#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class GameCharacter: public Object
{
private:
    string name;
    string skill;
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
public:
    GameCharacter();
    GameCharacter(string,string,int,int,int);
    bool checkIsDead();
    int takeDamage(int);

    /* Set & Get function*/
    void setSkill(string);
    void setMaxHealth(int);
    void setCurrentHealth(int);
    void setAttack(int);
    void setDefense(int);
    string getSkill() const;
    int getMaxHealth() const;
    int getCurrentHealth() const;
    int getAttack() const;
    int getDefense() const;
};
#endif // GAMECHARACTER_H_INCLUDED
