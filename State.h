//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H
#include "Room.h"
#include "GameObject.h"
class State {
    Room *currentRoom;

public:
    static std::list<GameObject*> inventory;
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom() const;
};


#endif //TEXTADV_STATE_H
