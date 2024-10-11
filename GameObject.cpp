//
// Created by Alessio Maggio on 15/11/2022.
//
#include "GameObject.h"
#include "Room.h"
#include "State.h"

GameObject::GameObject(const std::string *_name, const std::string *_desc, const std::string *_key) :
        name(_name), description(_desc), key(_key){};


/*void GameObject::addRoomObject(GameObject* object){
}*/
/*GameObject* GameObject::addRoomObject(const string* _name, const string *_desc,const string* _key){
    auto *newObject = new GameObject(_name, _desc,_key);
     Room::RoomObjects.push_back(newObject);
    return newObject;
}*/

void GameObject::addInventoryObject(GameObject *object){
    State::inventory.push_back(object);
}
GameObject* GameObject::addInventoryObject(const string* _name, const string *_desc,const string* _key) {
    auto *addInv = new GameObject(_name, _desc, _key);
    State::inventory.push_back(addInv);
    return addInv;
}

void GameObject::RemoveInvItem(GameObject *objects) {
    State::inventory.remove(objects);
}

GameObject* GameObject::RemoveInvItem(const string* _name, const string *_desc,const string* _key) {
    auto *remInv = new GameObject(_name, _desc, _key);
    State::inventory.remove(remInv);
    return remInv;
}

/*void GameObject::RemoveRoomItem(GameObject *objects) {
   Room::roomObjects.remove(objects);
}*/
/*GameObject* GameObject::RemoveRoomItem(const string* _name, const string *_desc,const string* _key) {
    auto *remRoom = new GameObject(_name, _desc, _key);
    Room::roomObjects.remove(remRoom);
   return remRoom;
}*/
const string* GameObject::getDesc() {
    return this->description;
}

const string* GameObject::getShortName() {
    return this->name;
}

const string* GameObject::getKey(){
    return this->key;
}






