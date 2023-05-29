#include "Utils.h"

extern Account accounts[MAX_N_ACCOUNTS];
extern int n_accounts;
extern Account current_account;

//-Functions----------------------------------------------------------------------------------------

/** Returns true if authorization has passed successfully, otherwise - false. */
bool account_authorization()
{
    cout << "Starting Authorization...\n";
    string login;
    cout << "Login: ";
    getline(cin, login);
    for (int i = 0; i < n_accounts; ++i) // to figure out is there the login
    {
        if (accounts[i].login == login)
        {
            string password;
            cout << "Password: ";
            getline(cin, password);
            if (accounts[i].password == password) // to verify the password
            {
                current_account = accounts[i]; // to set the current_account
                cout << "Wonderful! You are logged in!\n";
                return true;
            }
            cout << "Alas! Wrong password.\n";
            return false;
        }
    }
    cout << "Ooh... There is no such user.\n";
    return false;
}

/** Returns true if registration has passed successfully, otherwise - false. */
bool account_registration()
{
    if (n_accounts == MAX_N_ACCOUNTS)
    {
        cout << "Sorry, the size of the Accounts Data Base has reached the limit. "
                "So you can't be registered.\n";
        return false;
    }
    cout << "Starting Registration...\n";
    string login;
    bool found;
    do
    {
        found = false;
        cout << "Make a login: ";
        getline(cin, login);
        if (login.empty())
        {
            cout << "Login can't be empty!\n";
            return false;
        }
        for (int i = 0; i < n_accounts; ++i) // to verify the login
        {
            if (accounts[i].login == login)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            cout << "Oops... The login \"" << login <<
                    "\" has already been added. Let's try again!\n";
        }
    } while (found); // at this point the login is unic
    string password;
    cout << "Password: ";
    getline(cin, password);
    if (password.empty())
    {
        cout << "The password must NOT be empty!\n";
        return false;
    }
    // to create a new account
    Account account = { login, AccountType::USER, password };
    accounts[n_accounts++] = account; // to add the new account into the array of accounts
    current_account = account; // to set the current account
    write_account_to_file(account);
    cout << "You've just successfully registered! Let's get to the deal.\n";
    return true;
}

/** Returns true if exiting has passed successfully, otherwise - false. */
bool quit()
{
    cout << "That was pretty good! C u ;-)\n";
    exit(0);
    return true;
}
