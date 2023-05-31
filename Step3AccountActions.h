//  3rd stage of the program
#ifndef Step3AccountActions_h
#define Step3AccountActions_h

#include "Step0BusStation.h"

//-MENUS--------------------------------------------------------------------------------------------

/**
 *  User action selection with {@code make_choice} usage;
 *  all actions relate to the {@code routes}.
 *  @param  quit    an indicator to stop the program
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool user_actions(bool &quit);

/**
 *  Admin action selection with {@code make_choice} usage;
 *  all actions can relate to the {@code accounts} or to the {@code routes}.
 *  @param  quit    an indicator to stop the program
 *  @param  struct_type to know the structure to apply the account functions
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool admin_actions(bool &quit, StructureType &struct_type);

//-USER-AND-ADMIN-ACTIONS---------------------------------------------------------------------------

/**
 *  Simply shows the array of the structure that is defined by the {@code struct_type}.
 *  @param  struct_type to know the structure to apply the function
 */
void view(const StructureType &struct_type);

/**
 *  Searches for an element's identifier in the array of the structure
 *  that is defined by the {@code struct_type}.
 *  @param  struct_type to know the structure to apply the function
 */
void search(const StructureType &struct_type);

/**
 *  Sorts the full array of the structure that is defined by the {@code struct_type}
 *  by any of the element's field, than writes the array into the file
 *  and lastly shows the array.
 *  @param  struct_type to know the structure to apply the function
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool sort(const StructureType &struct_type);

//-ADMIN-ONLY-ACTIONS-------------------------------------------------------------------------------

/**
 *  Requests an input of all fields of the structure that is defined
 *  by the {@code struct_type}, than writes it into the file
 *  and adds to the array.
 *  @param  struct_type to know the structure to apply the function
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool add(const StructureType &struct_type);

/**
 *  Requests an input of all fields of the defined by an identifier element
 *  of the structure that is defined by the {@code struct_type},
 *  than adds it to the array and writes the file.
 *  @param  struct_type to know the structure to apply the function
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool edit(const StructureType &struct_type);

/**
 *  Removes by an identifier element of the structure that is defined
 *  by the {@code struct_type}, than writes the file.
 *  @param  struct_type to know the structure to apply the function
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool remove(const StructureType &struct_type);

#endif /* Step3AccountActions_h */
