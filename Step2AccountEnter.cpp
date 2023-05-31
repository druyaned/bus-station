#include "Utils.h"

extern Account accounts[MAX_N_ACCOUNTS];
extern int n_accounts;
extern Account current_account;

//-FUNCTIONS----------------------------------------------------------------------------------------

void account_authorization()
{
    cout << "Starting Authorization...\n";
    string login {};
    int ind = input_login(login);
    while (true)
    {
        if (ind == EMPTY)
        {
            cout << "Empty login o_O\n";
            return;
        }
        if (ind == NOT_FOUND)
            cout << "\"" << login << "\" cannot be found here!\n";
        else if (current_account.login == login)
            cout << "That's the current account o_O\n";
        else
            break; // found
        ind = input_login(login);
    }
    string password {};
    cout << "Password: ";
    getline(cin, password);
    if (password.empty())
    {
        cout << "Empty password o_O\n";
        return;
    }
    if (accounts[ind].password == password)
    {
        current_account = accounts[ind];
        cout << "Wonderful! You are logged in!\n";
        return;
    }
    cout << "Alas! Wrong password.\n";
}

bool account_registration()
{
    if (n_accounts == MAX_N_ACCOUNTS)
    {
        cout << "Sorry, the size of the Accounts Data Base has reached the limit, "
                "so you can't be registered.\n";
        return true;
    }
    cout << "Starting Registration...\n";
    string login {};
    int ind = input_login(login);
    while (true)
    {
        if (ind == EMPTY)
        {
            cout << "Empty login o_O\n";
            return true;
        }
        else if (ind != NOT_FOUND)
            cout << "It's already here!\n";
        else
            break; // uniq id
        ind = input_login(login);
    }
    string password;
    cout << "Password: ";
    getline(cin, password);
    if (password.empty())
    {
        cout << "Empty password o_O\n";
        return true;
    }
    Account account = { login, AccountType::USER, password };
    if (!write_account_to_file(account))
        return false;
    accounts[n_accounts++] = account;
    current_account = account;
    cout << "You've just successfully registered! Let's get to the deal.\n";
    return true;
}
