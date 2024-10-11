//
// Created by Alessio Maggio on 15/11/2022.
//

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H
#include <string>
#include <list>

using std::string;
class GameObject {
const string* name;
const string* description;
const string* key;
public:
    /*
     * constructor for GameObject
     */
    GameObject(const string *_name, const string *_desc, const string *_key);
    /*static GameObject* addRoomObject(const string *_name, const string *_desc, const string *_key);
    static void addRoomObject(GameObject* objects);*/
    static GameObject* addInventoryObject(const string *_name,const string *_desc,const string *_key);
    static void addInventoryObject(GameObject* objects);
    const string* getShortName();
    const string* getKey();
    static void RemoveInvItem(GameObject* objects);
    static GameObject* RemoveInvItem(const string *_name, const string *_desc, const string *_key);/*
    static void RemoveRoomItem(GameObject* objects);
    static GameObject* RemoveRoomItem(const string *_name, const string *_desc, const string *_key);*/
    const string* getDesc();

};


#endif //TEXTADV_GAMEOBJECT_H
