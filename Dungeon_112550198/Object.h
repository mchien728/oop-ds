#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Object
{
private:
    string name;
    string tag;
public:
    Object();
    Object(string,string);

    /* pure virtual function */
    virtual bool triggerEvent(Object*) = 0;

    /* Set & Get function*/
    void setName(string);
    void setTag(string);
    string getName() const;
    string getTag() const;
    void listInfo(ofstream&) const;
};
ostream& operator<<(ostream&, const Object&);

#endif // OBJECT_H_INCLUDED
