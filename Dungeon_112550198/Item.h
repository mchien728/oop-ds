#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;

class Player;

class Item: public Object
{
private:
    int health,attack,defense,hungerValue,thirstValue,poisonValue;
public:
    Item();
    Item(string, int, int, int, int, int, int);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    int getHunger() const;
    int getThirst() const;
    int getPoison() const;
    int getHealth() const;
    int getAttack() const;
    int getDefense()const;
    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setHunger(int);
    void setThirst(int);
    void setPoison(int);
    void listInfo(ofstream&) const;
};
ostream& operator<<(ostream&, const Item&);

#endif // ITEM_H_INCLUDED
