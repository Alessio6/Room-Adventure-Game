//
// Created by DrMark on 10/2/2017.
//


#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include "GameObject.h"


using std::string;

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;


    /**
     * Full description of the room.
     */
    const string* description;

    const string* roomKey;
    /**
     * Pointer to room that is north of this one.
     */
    Room* north;
    Room* south;
    Room* east;
    Room* west;
public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc,std::list<GameObject*> roomObjects);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe() const;

    /**
     * List storing all rooms that have been registered via addRoom().
     */
    static std::list<Room*> rooms;
    /**
     * List storing all the objects in a room registered via addObject().
     */
    std::list<GameObject*> roomObjects;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc,std::list<GameObject*> roomObjects);
    static void addRoom(Room* room);

    Room* getNorth() const;
    void setNorth(Room* _north);

    Room* getSouth() const;
    void setSouth(Room* _south);

    Room* getEast() const;
    void setEast(Room* _east);

    Room* getWest() const;
    void setWest(Room* _west);

    const string* getRoomName();


    void addRoomObject(GameObject* objects);

};

#endif //TEXTADV_ROOM_H