#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Room;
class Item;

class Player: public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
    string role;
    bool isWin;
    int hungerValue;
    int thirstValue;
    int poisonValue;
public:
    Player();
    Player(string,string,int,int,int);
    void addItem(Item);
    //void addPoisonItem(Item);
    void increaseStates(int,int,int,int,int,int);
    void changeRoom(Room*);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool isHunger();
    bool isThirst();
    bool isPoison();
    
    bool triggerEvent(Object*);
    bool skillOccur();
    int skillImplement();
    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(vector<Item>, bool);
    void setRole(string);
    void setHunger(int);
    void setThirst(int);
    void setPoison(int);

    Room* getCurrentRoom() const;
    Room* getPreviousRoom() const;
    vector<Item> getInventory() const;
    string getRole() const;
    int getHunger() const;
    int getThirst() const;
    int getPoison() const;
    void setisWin(bool);
    bool getisWin() const;
    void skillhelpOccur(Room*);
    void roomskillImplement(Room*);
    void roomHelpImplement(Room*);
};

std::ostream& operator<<(std::ostream&, const Player&);

#endif // PLAYER_H_INCLUDED
