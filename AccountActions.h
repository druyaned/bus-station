//  3rd stage of the program
#ifndef AccountActions_h
#define AccountActions_h

#include "BusStation.h"

void user_actions(bool &outer_loop); // menu
void admin_actions(bool &outer_loop); // menu
// actions:
bool view(StructureType);
bool search(StructureType);
bool sort(StructureType);
bool add(StructureType); // admin only
bool edit(StructureType);  // admin only
bool remove(StructureType);  // admin only

#endif /* AccountActions_h */
