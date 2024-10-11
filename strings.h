#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H

#include <string>
/*
 * Rooms
 */
const std::string r1name = "Room 1";
const std::string r1desc = "You are in room 1. It's really quite boring. There's a passage to the north or east.";
const std::string r2name = "Blue Room";
const std::string r2desc = "You are the blue room. You know because it's blue. That's about all though. There's a passage to the east or south.";
const std::string r3name = "Green Room";
const std::string r3desc = "you are in the Green room. There is a passage west or south";
const std::string r4name ="Yellow Room";
const std::string r4desc = "Your are in the yellow room. There is a passage west or north";
/*
 * GameObjects
 */
const std::string obj1name = "sword";
const std::string obj1desc = "tool to attack";
const std::string obj1key = "000";
const std::string obj2name = "shield";
const std::string obj2desc = "tool to defend";
const std::string obj2key = "001";
const std::string obj3name = "map";
const std::string obj3desc = "utility tool";
const std::string obj3key = "002";
const std::string obj4name = "potion";
const std::string obj4desc = "health item";
const std::string obj4key = "003";

const std::string badExit = "You can't go that way.";
const std::string badCommand = "I don't understand that.";
const std::string EmptyInv = "Your inventory is empty";
const std::string noRoom = "Not in room";
const std::string noInve= "Not in inventory";
const std::string Added = "added";
const std::string test = "method works";
const std::string dropped ="dropped";
const std::string roomObj = "Items in the Room:\n";
const std::string invObj = "Items in the inventory:\n";


#endif //TEXTADV_STRINGS_H
