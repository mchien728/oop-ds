#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Object.h"

using namespace std;

class Room
{
private:
    Room* upRoom;
    Room* downRoom;
    Room* leftRoom;
    Room* rightRoom;
    string type;
    string skill;
    string help;
    bool isExit;
    int index;
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
public:
    Room();
    Room(bool, int, vector<Object*>);
    void pushObject(Object*);
    bool popObject(Object*); /*pop out the specific object, used when the interaction is done*/

    /* Set & Get function*/
    void setUpRoom(Room*);
    void setDownRoom(Room*);
    void setLeftRoom(Room*);
    void setRightRoom(Room*);
    void setIsExit(bool);
    void setIndex(int);
    void setObjects(vector<Object*>);
    void setType(string);
    void setSkill(string);
    void setHelp(string);
    bool getIsExit() const;
    int getIndex() const;
    vector<Object*> getObjects() const;
    Room* getUpRoom() const;
    Room* getDownRoom() const;
    Room* getLeftRoom() const;
    Room* getRightRoom() const;
    string getType() const;
    string getSkill() const;
    string getHelp() const;
    void showMonster() const;
    void showNPC() const;
    bool isMonster();
    bool isNPC();
};
ostream& operator<<(ostream&, const Room&);

#endif // ROOM_H_INCLUDED
