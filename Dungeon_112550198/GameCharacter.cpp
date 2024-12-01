#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "GameCharacter.h"

using namespace std;

GameCharacter::GameCharacter(){
    //empty
}

GameCharacter::GameCharacter(string startName, string startTag, int max, int attack, int defense): Object(startName, startTag){
    this-> maxHealth = max;
    this-> currentHealth = max;
    this-> attack = attack;
    this-> defense = defense;
    this-> skill = "";
}

bool GameCharacter::checkIsDead(){
    return ((this-> currentHealth) <= 0);
}

int GameCharacter::takeDamage(int damage){
    float defBuff = rand() / RAND_MAX;          //隨機削減defense
    int realDamage = min(max(rand()%5, damage - getDefense() + (int)(defBuff* getDefense()* 0.3)), getCurrentHealth());
    return realDamage;
}

void GameCharacter::setSkill(string skillName){
    this-> skill = skillName;
}

void GameCharacter::setMaxHealth(int newMax){
    this-> maxHealth = newMax;
}

void GameCharacter::setCurrentHealth(int newCurrent){
    this-> currentHealth = newCurrent;
}

void GameCharacter::setAttack(int newAttack){
    this-> attack = newAttack;
}

void GameCharacter::setDefense(int newDefense){
    this-> defense = newDefense;
}

string GameCharacter::getSkill() const{
    return this-> skill;
}

int GameCharacter::getMaxHealth() const{
    return this-> maxHealth;
}

int GameCharacter::getCurrentHealth() const{
    return this-> currentHealth;
}

int GameCharacter::getAttack() const{
    return this-> attack;
}

int GameCharacter::getDefense() const{
    return this-> defense;
}