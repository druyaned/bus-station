#include "Utils.h"

//-GLOBAL-VARIABLES---------------------------------------------------------------------------------

Account accounts[MAX_N_ACCOUNTS];
int n_accounts; // number of accounts
BusRoute routes[MAX_N_ROUTES];
int n_routes; // number of routes
Account current_account {};

//-MAIN---------------------------------------------------------------------------------------------

int main(int argc, const char * argv[])
{
    preparation();
    account_enter();
    account_actions();
    return 0;
}
