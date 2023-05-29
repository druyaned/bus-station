#include "Utils.h"

extern Account current_account;

//-FUNCTIONS----------------------------------------------------------------------------------------

void preparation()
{
    read_accounts();
    read_routes();
}

void account_enter() // menu
{
    if (current_account.login.empty()) // i.e. if the current account isn't set
        cout << "[CURRENT-USER]: No one has logged in yet.\n";
    else // so the current account is set
        cout << "[CURRENT-USER]: " << current_account.login << endl;
    // it's time to make a choice
    string enter_menu = "[ENTER-MENU]\n0. quit\n1. Authorization\n2. Registration\n: ";
    int choice;
    bool enter_loop = true;
    while (enter_loop)
    {
        choice = make_choice('0', '2', enter_menu);
        switch (choice)
        {
            case 0: enter_loop = !quit(); break;
            case 1: enter_loop = !account_authorization(); break;
            case 2: enter_loop = !account_registration(); break;
            default:
                enter_loop = false;
                cout << "Something went wrong. Exiting...";
                exit(EXIT_FAILURE);
                break;
        }
    }
}

void account_actions()
{
    bool account_loop = true;
    while (account_loop)
    {
        if (current_account.type == AccountType::USER)
            user_actions(account_loop);
        else
            admin_actions(account_loop);
    }
}
