#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"

using namespace std;

class Monster: public GameCharacter
{
private:
public:
    Monster();
    Monster(string,int,int,int);
    Monster(const Monster*);
    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    void listInfo(ofstream&) const;
    void showInfo() const;
    bool skillOccur();
    int skillImplement(Player*);
    bool triggerEvent(Object*);
};
ostream& operator<<(ostream&, const Monster&);

#endif // ENEMY_H_INCLUDED
