#include "Utils.h"

//-GLOBAL-VARIABLES---------------------------------------------------------------------------------

Account accounts[MAX_N_ACCOUNTS] {};    // array of registered accounts
int n_accounts = 0;                     // number of accounts
BusRoute routes[MAX_N_ROUTES] {};       // array of registered bus routes
int n_routes = 0;                       // number of routes
Account current_account {};             // current authorized account in the system

//-MAIN---------------------------------------------------------------------------------------------

/**
 *  Main function of the program consists of several steps:
 *  (0) some definitions,
 *  (1) preparation,
 *  (2) account enter,
 *  (3) account actions.
 *  @param  argc    number of the command line arguments
 *  @param  argv    command line arguments
 *  @return {@code EXIT_SUCCESS} in case of normal program behaviour,
 *          otherwise other int value (e.g. {@code EXIT_FAILURE})
 */
int main(int argc, const char * argv[])
{
    preparation();
    bool quit = false;
    if (!account_enter(quit))
        return EXIT_FAILURE;
    if (!quit && !account_actions())
        return EXIT_FAILURE;
    cout << "That was pretty good! C u ;-)\n";
    return EXIT_SUCCESS;
}
