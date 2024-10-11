#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include<fstream>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "GameObject.h"

using std::string;
using std::unique_ptr;
using namespace std;

string commandBuffer;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin,*buffer);
}
/**
 * Sets up the map.
 */
void initRooms() {
    auto * obj1 = new GameObject(&obj1name,&obj1desc,&obj1key);
    auto * obj2 = new GameObject(&obj2name,&obj2desc,&obj2key);
    auto * obj3 = new GameObject(&obj3name,&obj3desc,&obj3key);
    auto * obj4 = new GameObject(&obj4name,&obj4desc,&obj4key);

    std::list<GameObject*> roomObj1 = {obj1};
    std::list<GameObject*> roomObj2 = {obj2};
    std::list<GameObject*> roomObj3 = {obj3};
    std::list<GameObject*> roomObj4 = {obj4};

    /*
     * Room objects
     */
    auto * r1 = new Room(&r1name, &r1desc,roomObj1);
    auto * r2 = new Room(&r2name, &r2desc,roomObj2);
    auto * r3 = new Room(&r3name, &r3desc,roomObj3);
    auto * r4 = new Room(&r4name, &r4desc,roomObj4);
    /*
     * GameObject objects
     */


    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);

    r1->setNorth(r2);
    r2->setSouth(r1);
    r2->setEast(r3);
    r3->setWest(r2);
    r3->setSouth(r4);
    r4->setNorth(r3);
    r4->setWest(r1);
    r1->setEast(r4);
}
/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}


/**
 * The main game loop.
 */

void gameLoop() {
    bool gameOver = false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false; /* */
        inputCommand(&commandBuffer);
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' ', 0));
        auto secondCommand = static_cast<uint8_t>(commandBuffer.find(' ', endOfVerb + 1));
        if ((commandBuffer.compare(0, endOfVerb, "north") == 0) || (commandBuffer.compare(0, endOfVerb, "n") == 0)) {
            commandOk = true;
            Room *northRoom = currentState->getCurrentRoom()->getNorth();
            if (northRoom == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(northRoom);
            }
        }
        if ((commandBuffer.compare(0, endOfVerb, "south") == 0) || (commandBuffer.compare(0, endOfVerb, "s") == 0)) {
            commandOk = true;
            Room *southRoom = currentState->getCurrentRoom()->getSouth();
            if (southRoom == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(southRoom);
            }
        }
        if ((commandBuffer.compare(0, endOfVerb, "east") == 0) || (commandBuffer.compare(0, endOfVerb, "e") == 0)) {
            commandOk = true;
            Room *eastRoom = currentState->getCurrentRoom()->getEast();
            if (eastRoom == nullptr) {
                wrapEndPara();
            } else {
                currentState->goTo(eastRoom);
            }
        }
        if ((commandBuffer.compare(0, endOfVerb, "west") == 0) || (commandBuffer.compare(0, endOfVerb, "w") == 0)) {
            commandOk = true;
            Room *westRoom = currentState->getCurrentRoom()->getWest();
            if (westRoom == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(westRoom);
            }
        }
        if ((commandBuffer.compare(0, endOfVerb, "get") == 0)) {
            if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "000") == 0)) {
                commandOk = true;
                for (auto &obj: currentState->getCurrentRoom()->roomObjects) {
                    if (obj->getKey() == &obj1key) {
                        GameObject::addInventoryObject(obj);
                        currentState->getCurrentRoom()->roomObjects.remove(obj);
                        wrapOut(&Added);
                        wrapEndPara();
                        break;
                    } else if (obj->getKey() != &obj1key) {
                        wrapOut(&noRoom);
                        wrapEndPara();
                    }
                }
            }
            if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "001") == 0)) {
                commandOk = true;
                for (auto &obj: currentState->getCurrentRoom()->roomObjects) {
                    if (obj->getKey() == &obj2key) {
                        GameObject::addInventoryObject(obj);
                        currentState->getCurrentRoom()->roomObjects.remove(obj);
                        wrapOut(&Added);
                        wrapEndPara();
                        break;
                    } else if (obj->getKey() != &obj2key) {
                        wrapOut(&noRoom);
                        wrapEndPara();
                    }
                }
            }
            if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "002") == 0)) {
                commandOk = true;
                for (auto &obj: currentState->getCurrentRoom()->roomObjects) {
                    if (obj->getKey() == &obj3key) {
                        GameObject::addInventoryObject(obj);
                        currentState->getCurrentRoom()->roomObjects.remove(obj);
                        wrapOut(&Added);
                        wrapEndPara();
                        break;
                    } else {
                        wrapOut(&noRoom);
                        wrapEndPara();
                    }
                }
            }
            if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "003") == 0)) {
                commandOk = true;
                for (auto &obj: currentState->getCurrentRoom()->roomObjects) {
                    if (obj->getKey() == &obj4key) {
                        GameObject::addInventoryObject(obj);
                        currentState->getCurrentRoom()->roomObjects.remove(obj);
                        wrapOut(&Added);
                        wrapEndPara();
                        break;
                    } else if (obj->getKey() != &obj3key) {
                        wrapOut(&noRoom);
                        wrapEndPara();
                    }
                }
            }
        }
        if ((commandBuffer.compare(0, endOfVerb, "drop") == 0)) {
            if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "000") == 0)) {
                commandOk = true;
                for (auto &obj: State::inventory) {
                    if (obj->getKey() == &obj1key) {
                        currentState->getCurrentRoom()->roomObjects.push_back(obj);
                        GameObject::RemoveInvItem(obj);
                        wrapOut(&dropped);
                        wrapEndPara();
                        break;
                    } else if (obj->getKey() != &obj1key) {
                        wrapOut(&noInve);
                        wrapEndPara();
                    }
                }
            } else if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "001") == 0)) {
                commandOk = true;
                for (auto &obj: State::inventory) {
                    if (obj->getKey() == &obj2key) {
                        GameObject::RemoveInvItem(obj);
                        currentState->getCurrentRoom()->roomObjects.push_back(obj);
                        wrapOut(&dropped);
                        wrapEndPara();
                        break;
                    } else if (obj->getKey() != &obj2key) {
                        wrapOut(&noInve);
                        wrapEndPara();
                    }
                }

            } else if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "002") == 0)) {
                commandOk = true;
                for (auto &obj: State::inventory) {
                    if (obj->getKey() == &obj3key) {
                        GameObject::RemoveInvItem(obj);
                        currentState->getCurrentRoom()->roomObjects.push_back(obj);
                        wrapOut(&dropped);
                        wrapEndPara();
                        break;
                    } else if (obj->getKey() != &obj3key) {
                        wrapOut(&noInve);
                        wrapEndPara();
                    }
                }
            } else if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "003") == 0)) {
                commandOk = true;
                for (auto &obj: State::inventory) {
                    if (obj->getKey() == &obj4key) {
                        GameObject::RemoveInvItem(obj);
                        currentState->getCurrentRoom()->roomObjects.push_back(obj);
                        wrapOut(&dropped);
                        wrapEndPara();
                        break;
                    } else if (obj->getKey() != &obj4key) {
                        wrapOut(&noInve);
                        wrapEndPara();
                    }
                }
            }
        }
       /* if ((commandBuffer.compare(0, endOfVerb, "room") == 0)) {
            commandOk = true;
            wrapOut(&roomObj);
            for (auto &obj: currentState->getCurrentRoom()->roomObjects) {
                wrapOut(obj->getShortName());
                wrapEndPara();
            }
        }*/
        if ((commandBuffer.compare(0, endOfVerb, "inventory") == 0)) {
            commandOk = true;
            wrapOut(&invObj);
            for (auto &obj: State::inventory) {
                wrapOut(obj->getShortName());
                wrapEndPara();
            }
        }
        if ((commandBuffer.compare(0, endOfVerb, "examine") == 0)) {
            if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "000") == 0)) {
                commandOk = true;
                for (auto &obj: State::inventory) {
                    if (obj->getKey() == &obj1key) {
                        wrapOut(obj->getDesc());
                        wrapEndPara();
                    }
                }
            }
            if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "001") == 0)) {
                commandOk = true;
                for (auto &obj: State::inventory) {
                    if (obj->getKey() == &obj2key) {
                        wrapOut(obj->getDesc());
                        wrapEndPara();
                    }
                }
            }
            if ((commandBuffer.compare(endOfVerb + 1, secondCommand, "002") == 0)) {
                commandOk = true;
                for (auto &obj: State::inventory) {
                    if (obj->getKey() == &obj4key) {
                        wrapOut(obj->getDesc());
                        wrapEndPara();
                    }
                }
            }
        }
        /*save*/
        if ((commandBuffer.compare(0, endOfVerb, "save") == 0)) {
            commandOk = true;
            std::ofstream roomObj1Save("roomObj1Save.txt");
            std::ofstream roomObj2Save("roomObj2Save.txt");
            std::ofstream roomObj3Save("roomObj3Save.txt");
            std::ofstream roomObj4Save("roomObj4Save.txt");
            std::ofstream inventorySave("inventorySave.txt");
            std::ofstream posSave("posSave.txt");
            /*saving the inventory*/
            for (auto &it: State::inventory) {
                inventorySave << *(it->getShortName()) << "\n";
            }
            /*saving the room objects*/
            for(auto &it:currentState->getCurrentRoom()->rooms){
                if(*(it->getRoomName()) == "Room 1") {
                    for(auto it:it->roomObjects){
                        roomObj1Save << *(it)->getShortName() << "\n";
                    }
                }
                if(*(it->getRoomName()) == "Blue Room") {
                    for(auto it:it->roomObjects){
                        roomObj2Save << *(it)->getShortName() << "\n";
                    }
                }
                if(*(it->getRoomName()) == "Green Room") {
                    for(auto it:it->roomObjects){
                        roomObj3Save  << *(it)->getShortName() << "\n";
                    }
                }
                if(*(it->getRoomName()) == "Yellow Room") {
                    for(auto it:it->roomObjects){
                        roomObj4Save  << *(it)->getShortName() << "\n";
                    }
                }
            }
            /*saving the players current position*/
            posSave << *currentState->getCurrentRoom()->getRoomName();
            /*closing the files */
            posSave.close();
            roomObj1Save.close();
            roomObj2Save.close();
            roomObj3Save.close();
            roomObj4Save.close();
            inventorySave.close();
        }
        /*load*/
        if ((commandBuffer.compare(0, endOfVerb, "load") == 0)) {
            commandOk = true;
            for(auto &it:currentState->getCurrentRoom()->rooms){
                it->roomObjects.clear();
            }
            currentState->inventory.clear();
            std::ifstream inventoryLoad("inventorySave.txt");
            std::ifstream roomObj1Load("roomObj1Save.txt");
            std::ifstream roomObj2Load("roomObj2Save.txt");
            std::ifstream roomObj3Load("roomObj3Save.txt");
            std::ifstream roomObj4Load("roomObj4Save.txt");
            std::ifstream  posLoad("posSave.txt");
            /*loading back the inventory*/

                while (!inventoryLoad.eof()) {
                    string line;
                    getline(inventoryLoad, line);
                    if (line == "sword") {
                        auto sword = new GameObject(&obj1name, &obj1desc, &obj1key);
                        GameObject::addInventoryObject(sword);
                    }
                    if (line == "shield") {
                        auto shield = new GameObject(&obj2name, &obj2desc, &obj2key);
                        GameObject::addInventoryObject(shield);
                    }
                    if (line == "map") {
                        auto map = new GameObject(&obj3name, &obj3desc, &obj3key);
                        GameObject::addInventoryObject(map);
                    }
                    if (line == "potion") {
                        auto potion = new GameObject(&obj4name, &obj4desc, &obj4key);
                        GameObject::addInventoryObject(potion);
                    }
                }

                /*loading back the objects in the room*/
                currentState = new State(Room::rooms.front());
                while (!roomObj1Load.eof()) {
                    string line;
                    getline(roomObj1Load, line);
                    for (auto &it: currentState->getCurrentRoom()->rooms) {
                        if (*(it->getRoomName()) == "Room 1") {
                            if (line == "sword") {
                                auto *object = new GameObject(&obj1name, &obj1desc, &obj1key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "shield") {
                                auto *object = new GameObject(&obj2name, &obj2desc, &obj2key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "map") {
                                auto *object = new GameObject(&obj3name, &obj3desc, &obj3key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "potion") {
                                auto *object = new GameObject(&obj4name, &obj4desc, &obj4key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                        }
                    }
                }
                while (!roomObj2Load.eof()) {
                    string line;
                    getline(roomObj2Load, line);
                    for (auto &it: currentState->getCurrentRoom()->rooms) {
                        if (*(it->getRoomName()) == "Blue Room") {
                            if (line == "sword") {
                                auto *object = new GameObject(&obj1name, &obj1desc, &obj1key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }

                            else if (line == "shield") {
                                auto *object = new GameObject(&obj2name, &obj2desc, &obj2key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "map") {
                                auto *object = new GameObject(&obj3name, &obj3desc, &obj3key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "potion") {
                                auto *object = new GameObject(&obj4name, &obj4desc, &obj4key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                        }
                    }
                }
                while (!roomObj3Load.eof()) {
                    string line;
                    getline(roomObj3Load, line);
                    for (auto &it: currentState->getCurrentRoom()->rooms) {
                        if (*(it->getRoomName()) == "Green Room") {
                            if (line == "sword") {
                                auto *object = new GameObject(&obj1name, &obj1desc, &obj1key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "shield") {
                                auto *object = new GameObject(&obj2name, &obj2desc, &obj2key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "map") {
                                auto *object = new GameObject(&obj3name, &obj3desc, &obj3key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "potion") {
                                auto *object = new GameObject(&obj4name, &obj4desc, &obj4key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                        }
                    }
                }
                while (!roomObj4Load.eof()) {
                    string line;
                    getline(roomObj4Load, line);
                    for (auto &it: currentState->getCurrentRoom()->rooms) {
                        if (*(it->getRoomName()) == "Yellow Room") {
                            if (line == "sword") {
                                auto *object = new GameObject(&obj1name, &obj1desc, &obj1key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "shield") {
                                auto *object = new GameObject(&obj2name, &obj2desc, &obj2key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "map") {
                                auto *object = new GameObject(&obj3name, &obj3desc, &obj3key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                            else if (line == "potion") {
                                auto *object = new GameObject(&obj4name, &obj4desc, &obj4key);
                                currentState->getCurrentRoom()->addRoomObject(object);
                                it->addRoomObject(object);
                            }
                        }
                    }
                }
           /*loading the player in their previous room*/
            while(!posLoad.eof()){
                string line;
                getline(posLoad, line);
                for (auto &it: currentState->getCurrentRoom()->rooms) {
                    if (*(it->getRoomName()) == "Room 1") {
                        if (line == "Room 1") {
                            currentState->goTo(it);
                        }
                        }
                    }
                for (auto &it: currentState->getCurrentRoom()->rooms) {
                    if (*(it->getRoomName()) == "Blue Room") {
                        if (line == "Blue Room") {
                            currentState->goTo(it);
                        }
                    }
                }
                for (auto &it: currentState->getCurrentRoom()->rooms) {
                    if (*(it->getRoomName()) == "Green Room") {
                        if (line == "Green Room") {
                            currentState->goTo(it);
                        }
                    }
                }
                for (auto &it: currentState->getCurrentRoom()->rooms) {
                    if (*(it->getRoomName()) == "Yellow Room") {
                        if (line == "Yellow Room") {
                            currentState->goTo(it);
                        }
                    }
                }

            }
            roomObj1Load.close();
            roomObj2Load.close();
            roomObj3Load.close();
            roomObj4Load.close();
            posLoad.close();
            inventoryLoad.close();
               }
        if ((commandBuffer.compare(0, endOfVerb, "quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }
        if (!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}
    int main() {
        initWordWrap();
        initRooms();
        initState();
        currentState->announceLoc();
        gameLoop();
        return 0;
    }
