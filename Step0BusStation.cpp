#include "Utils.h"

extern Account current_account;

//-FUNCTIONS----------------------------------------------------------------------------------------

bool preparation()
{
    if (!read_accounts())
        return false;
    if (!read_routes())
        return false;
    return true;
}

bool account_enter(bool &quit)
{
    const string enter_menu = current_account.login.empty() ?
        "\n[CURRENT-USER]: [NONE]\n"
            "[ENTER-MENU]\n0. quit\n1. Authorization\n2. Registration\n: " :
        "\n[CURRENT-USER]: " + current_account.login +
            "\n[ENTER-MENU]\n0. quit\n1. Authorization\n2. Registration\n: ";
    int choice;
    do
    {
        choice = make_choice('0', '2', enter_menu);
        switch (choice)
        {
            case 0: return quit = true;
            case 1: account_authorization(); break;
            case 2:
                if (!account_registration())
                    return false;
                break;
            case -1: return false;
            default: cout << "Something went wrong after choice making...\n"; return false;
        }
    } while (current_account.login.empty());
    return true;
}

bool account_actions()
{
    using AccountType::USER;
    using AccountType::ADMIN;
    bool quit = false;
    StructureType struct_type = StructureType::BUS_ROUTES;
    while (!quit)
    {
        if (current_account.type == USER && !user_actions(quit))
            return false;
        else if (current_account.type == ADMIN && !admin_actions(quit, struct_type))
            return false;
    }
    return true;
}
