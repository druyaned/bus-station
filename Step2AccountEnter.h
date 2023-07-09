//  2nd stage of the program
#ifndef Step2AccountEnter_h
#define Step2AccountEnter_h

#include <stdlib.h>

/**
 *  Runs the account authorization process with make_choice usage;
 *  firstly determines if the login is valid then verifies the password
 *  and if all's ok sets the current account.
 */
void account_authorization();

/**
 *  Runs the account registration process with cin usage;
 *  firstly determines if the login is valid then verifies the password,
 *  writes a new user to the accounts and to the FILE_OF_ACCOUNTS
 *  and then if all's ok sets the current account.
 *  @return false if an I/O error occurs, otherwise true
 */
bool account_registration();

#endif /* Step2AccountEnter_h */
