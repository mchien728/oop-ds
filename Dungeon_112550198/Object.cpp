#include <fstream>
#include "Object.h"

Object::Object(){
    this-> name = "Guest";
    this-> tag = "Unknown";
}

Object::Object(string startName, string startTag){
    this-> name = startName;
    this-> tag = startTag;
}

void Object::setName(string newName){
    this-> name = newName;
}

void Object::setTag(string newTag){
    this-> tag = newTag;
}

string Object::getName() const{
    return this-> name;
}

string Object::getTag() const{
    return this-> tag;
}

void Object::listInfo(ofstream& out) const{
    out << getTag() << " " << getName() << endl;
}

ostream& operator<<(ostream& out, const Object& obj) {
	out << obj.getName();
	return out;
}

