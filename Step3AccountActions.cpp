#include "Utils.h"

extern Account accounts[MAX_N_ACCOUNTS];
extern int n_accounts; // number of accounts
extern BusRoute routes[MAX_N_ROUTES];
extern int n_routes; // number of routes
extern Account current_account;

using StructureType::ACCOUNTS;
using StructureType::BUS_ROUTES;
using AccountType::USER;
using AccountType::ADMIN;
using BusType::SMALL;
using BusType::MEDIUM;
using BusType::LARGE;

typedef long long ll;

//-CONSTANTS----------------------------------------------------------------------------------------

const ll MINUTES_IN_HOUR = 60LL;
const ll MINUTES_IN_DAY = MINUTES_IN_HOUR * 24LL;
const ll MINUTES_IN_MONTH = MINUTES_IN_DAY * 31LL;
const ll MINUTES_IN_YEAR = MINUTES_IN_MONTH * 12LL;

//-AUXILIARY-FUNCTIONS------------------------------------------------------------------------------

bool define_structure_type(StructureType &st)
{
    const string sctruct_menu = "\n[MENU-OF-SCRUCTURES]:\n1. accounts\n2. bus routes\n: ";
    int choice = make_choice('1', '2', sctruct_menu);
    switch (choice)
    {
        case 1: st = ACCOUNTS; break;
        case 2: st = BUS_ROUTES; break;
        case -1: return false;
        default: cout << "Something went wrong after choice making...\n"; return false;
    }
    return true;
}

inline int by_type(const Account &a1, const Account &a2)
{
    return a1.type - a2.type;
}

inline int by_pass(const Account &a1, const Account &a2)
{
    return a1.password < a2.password ? -1 : (a1.password == a2.password ? 0 : 1);
}

inline int by_type(const BusRoute &r1, const BusRoute &r2)
{
    return r1.type - r2.type;
}

inline int by_destination(const BusRoute &r1, const BusRoute &r2)
{
    return r1.destination < r2.destination ? -1 :
        (r1.destination == r2.destination ? 0 : 1);
}

int by_departure(const BusRoute &r1, const BusRoute &r2)
{
    DateTime dt1 = r1.departure;
    DateTime dt2 = r2.departure;
    ll m1 = dt1.year * MINUTES_IN_YEAR + dt1.month * MINUTES_IN_MONTH +
        dt1.day * MINUTES_IN_DAY + dt1.hour * MINUTES_IN_HOUR + dt1.minute;
    ll m2 = dt2.year * MINUTES_IN_YEAR + dt2.month * MINUTES_IN_MONTH +
        dt2.day * MINUTES_IN_DAY + dt2.hour * MINUTES_IN_HOUR + dt2.minute;
    return m1 < m2 ? -1 : (m1 == m2 ? 0 : 1);
}

int by_arrival(const BusRoute &r1, const BusRoute &r2)
{
    DateTime dt1 = r1.arrival;
    DateTime dt2 = r2.arrival;
    ll m1 = dt1.year * MINUTES_IN_YEAR + dt1.month * MINUTES_IN_MONTH +
        dt1.day * MINUTES_IN_DAY + dt1.hour * MINUTES_IN_HOUR + dt1.minute;
    ll m2 = dt2.year * MINUTES_IN_YEAR + dt2.month * MINUTES_IN_MONTH +
        dt2.day * MINUTES_IN_DAY + dt2.hour * MINUTES_IN_HOUR + dt2.minute;
    return m1 < m2 ? -1 : (m1 == m2 ? 0 : 1);
}

inline int by_ticket_cost_BYN(const BusRoute &r1, const BusRoute &r2)
{
    return r1.ticket_cost_BYN - r2.ticket_cost_BYN;
}

inline int by_n_tickets(const BusRoute &r1, const BusRoute &r2)
{
    return r1.n_tickets - r2.n_tickets;
}

inline int by_tickets_left(const BusRoute &r1, const BusRoute &r2)
{
    return r1.tickets_left - r2.tickets_left;
}

//-MENUS--------------------------------------------------------------------------------------------

bool user_actions(bool &quit)
{
    const string actions_menu = "\n[CURRENT-USER]: " + current_account.login +
        "\n[STRUCTURE-TYPE]: Bus Routes\n"
        "[MENU-OF-ACTIONS]:\n0. quit\n1. view\n2. search\n3. sort\n4. ENTER-MENU\n: ";
    int choice = make_choice('0', '4', actions_menu);
    switch (choice)
    {
        case 0: return quit = true;
        case 1: view(BUS_ROUTES); break;
        case 2: search(BUS_ROUTES); break;
        case 3: return sort(BUS_ROUTES);
        case 4: return account_enter(quit); break;
        case -1: return false;
        default: cout << "Something went wrong after choice making...\n"; return false;
    }
    return true;
}

bool admin_actions(bool &quit, StructureType &struct_type)
{
    const string accounts_menu = "\n[CURRENT-USER]: " + current_account.login +
        "\n[STRUCTURE-TYPE]: Accounts\n"
        "[MENU-OF-ACTIONS]:\n0. quit\n1. view\n2. search\n3. sort\n"
        "4. add\n5. edit\n6. remove\n7. MENU-OF-SCRUCTURES\n8. ENTER-MENU\n: ";
    const string routes_menu = "\n[CURRENT-USER]: " + current_account.login +
        "\n[STRUCTURE-TYPE]: Bus Routes\n"
        "[MENU-OF-ACTIONS]:\n0. quit\n1. view\n2. search\n3. sort\n"
        "4. add\n5. edit\n6. remove\n7. MENU-OF-SCRUCTURES\n8. ENTER-MENU\n: ";
    int choice = (struct_type == ACCOUNTS) ?
        make_choice('0', '8', accounts_menu) :
        make_choice('0', '8', routes_menu);
    switch (choice)
    {
        case 0: return quit = true;
        case 1: view(struct_type); break;
        case 2: search(struct_type); break;
        case 3: return sort(struct_type);
        case 4: return add(struct_type);
        case 5: return edit(struct_type);
        case 6: return remove(struct_type);
        case 7: return define_structure_type(struct_type);
        case 8: return account_enter(quit);
        case -1: return false;
        default: cout << "Something went wrong after choice making...\n"; return false;
    }
    return true;
}

//-USER-AND-ADMIN-ACTIONS---------------------------------------------------------------------------

void view(const StructureType &struct_type)
{
    if (struct_type == ACCOUNTS)
        show_accounts();
    else
        show_routes();
}

void search(const StructureType &struct_type)
{
    if (struct_type == ACCOUNTS)
    {
        string login {};
        int ind = input_login(login);
        if (ind == EMPTY)
            cout << "Login cannot be empty! Let's keep going!\n";
        else if (ind != NOT_FOUND)
        {
            string type_str = accounts[ind].type == USER ? "a USER" : "an ADMIN";
            cout << "Great news! There is " << type_str << " with the given login!\n";
        }
        else
            cout << "Attractive login but it's NOT here!\n";
    }
    else
    {
        int route_number;
        int ind = input_route_number(route_number);
        if (ind == EMPTY)
            cout << "Empty route number o_O\n";
        else if (ind == NOT_POSITIVE)
            cout << "[tongue clicking]... A non-negative integer is required!\n";
        else if (ind != NOT_FOUND)
        {
            cout << "Great news! There is a "
                    << bus_type_as_string(routes[ind].type)
                    << " bus with given route number!\n";
            cout << "Here it is: " << routes[ind].as_string() << endl;
        }
        else
            cout << "Attractive number but it's NOT here!\n";
    }
}

bool sort(const StructureType &struct_type)
{
    if (struct_type == ACCOUNTS)
    {
        string sort_menu = "\n[SORT-ACCOUNTS-MENU]:"
            "\n0. back\n1. login\n2. type\n3. password\n: ";
        int choice = make_choice('0', '3', sort_menu);
        switch (choice)
        {
            case 0: return true;
            case 1:
                cout << "Sorting by login...\n";
                quick_sort(accounts, 0, n_accounts - 1);
                cout << "Successfully sorted!\n";
                if (!write_accounts())
                    return false;
                show_accounts();
                return true;
            case 2:
                cout << "Sorting by type...\n";
                quick_sort(accounts, 0, n_accounts - 1, by_type);
                cout << "Successfully sorted!\n";
                if (!write_accounts())
                    return false;
                show_accounts();
                return true;
            case 3:
                cout << "Sorting by password...\n";
                quick_sort(accounts, 0, n_accounts - 1, by_pass);
                cout << "Successfully sorted!\n";
                if (!write_accounts())
                    return false;
                show_accounts();
                return true;
            case -1: return false;
            default: cout << "Something went wrong after choice making...\n"; return false;
        }
    }
    else
    {
        string sort_menu = "\n[SORT-BUS-ROUTES-MENU]:"
            "\n0. back\n1. route number\n2. type\n3. destination\n"
            "4. departure\n5. arrival\n6. ticket cost (BYN)\n"
            "7. total number of tickets\n8. tickets left\n: ";
        int choice;
        choice = make_choice('0', '8', sort_menu);
        switch (choice)
        {
            case 0: return true;
            case 1:
                cout << "Sorting by route number...\n";
                quick_sort(routes, 0, n_routes-1);
                cout << "Successfully sorted!\n";
                if (!write_routes())
                    return false;
                show_routes();
                return true;
            case 2:
                cout << "Sorting by type...\n";
                quick_sort(routes, 0, n_routes-1, by_type);
                cout << "Successfully sorted!\n";
                if (!write_routes())
                    return false;
                show_routes();
                return true;
            case 3:
                cout << "Sorting by destination...\n";
                quick_sort(routes, 0, n_routes-1, by_destination);
                cout << "Successfully sorted!\n";
                if (!write_routes())
                    return false;
                show_routes();
                return true;
            case 4:
                cout << "Sorting by departure...\n";
                quick_sort(routes, 0, n_routes-1, by_departure);
                cout << "Successfully sorted!\n";
                if (!write_routes())
                    return false;
                show_routes();
                return true;
            case 5:
                cout << "Sorting by arrival...\n";
                quick_sort(routes, 0, n_routes-1, by_arrival);
                cout << "Successfully sorted!\n";
                if (!write_routes())
                    return false;
                show_routes();
                return true;
            case 6:
                cout << "Sorting by ticket cost (BYN)...\n";
                quick_sort(routes, 0, n_routes-1, by_ticket_cost_BYN);
                cout << "Successfully sorted!\n";
                if (!write_routes())
                    return false;
                show_routes();
                return true;
            case 7:
                cout << "Sorting by total number of tickets...\n";
                quick_sort(routes, 0, n_routes-1, by_n_tickets);
                cout << "Successfully sorted!\n";
                if (!write_routes())
                    return false;
                show_routes();
                return true;
            case 8:
                cout << "Sorting by tickets left...\n";
                quick_sort(routes, 0, n_routes-1, by_tickets_left);
                cout << "Successfully sorted!\n";
                if (!write_routes())
                    return false;
                show_routes();
                return true;
            case -1: return false;
            default: cout << "Something went wrong after choice making...\n"; return false;
        }
    }
    return true;
}

//-ADMIN-ONLY-ACTIONS-------------------------------------------------------------------------------

bool add(const StructureType &struct_type)
{
    if (struct_type == ACCOUNTS)
    {
        if (n_accounts == MAX_N_ACCOUNTS)
        {
            cout << "Sorry, the size of the Accounts Data Base has reached the limit, "
                "so you can't be registered.\n";
            return true;
        }
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
        Account account;
        if (input_non_login(login, account))
        {
            if (!write_account_to_file(account))
                return false;
            accounts[n_accounts++] = account;
            cout << "Successfully added!\n";
        }
    }
    else
    {
        if (n_routes == MAX_N_ROUTES)
        {
            cout << "Sorry, the size of the Bus Routes Data Base has reached the limit. "
                "So you cannot add a bus route.\n";
            return true;
        }
        int route_number = -1;
        int ind = input_route_number(route_number);
        while (true)
        {
            if (ind == EMPTY)
            {
                cout << "Empty route number o_O\n";
                return true;
            }
            else if (ind == NOT_POSITIVE)
                cout << "[tongue clicking]... A non-negative integer is required!\n";
            else if (ind != NOT_FOUND)
                cout << "It's already here!\n";
            else
                break; // uniq id
            ind = input_route_number(route_number);
        }
        BusRoute route;
        if (input_non_route_number(route_number, route))
        {
            if (!write_route_to_file(route))
                return false;
            routes[n_routes++] = route;
            cout << "Successfully added!\n";
        }
    }
    return true;
}

bool edit(const StructureType &struct_type)
{
    if (struct_type == ACCOUNTS)
    {
        string login {};
        int ind = input_login(login);
        while (true)
        {
            if (ind == EMPTY)
            {
                cout << "Empty login o_O\n";
                return true;
            }
            else if (ind == NOT_FOUND)
                cout << "\"" << login << "\" cannot be found here!\n";
            else if (current_account.login == login)
            {
                string password {};
                cout << "Password: ";
                getline(cin, password);
                if (password.empty())
                {
                    cout << "Empty password o_O\n";
                    return true;
                }
                accounts[ind] = { login, ADMIN, password };
                if (!write_accounts())
                    return false;
                cout << "Successfully edited!\n";
                return true;
            }
            else
                break; // found
            ind = input_login(login);
        }
        Account account;
        if (input_non_login(login, account))
        {
            accounts[ind] = account;
            if (!write_accounts())
                return false;
            cout << "Successfully edited!\n";
        }
    }
    else
    {
        int route_number = -1;
        int ind = input_route_number(route_number);
        while (true)
        {
            if (ind == EMPTY)
            {
                cout << "Empty route number o_O\n";
                return true;
            }
            else if (ind == NOT_POSITIVE)
                cout << "[tongue clicking]... A non-negative integer is required!\n";
            else if (ind == NOT_FOUND)
                cout << "\"" << route_number << "\" cannot be found here!\n";
            else
                break; // found
            ind = input_route_number(route_number);
        }
        BusRoute route;
        if (input_non_route_number(route_number, route))
        {
            routes[ind] = route;
            if (!write_routes())
                return false;
            cout << "Successfully edited!\n";
        }
    }
    return true;
}

bool remove(const StructureType &struct_type)
{
    if (struct_type == ACCOUNTS)
    {
        string login {};
        int ind = input_login(login);
        while (true)
        {
            if (ind == EMPTY)
            {
                cout << "Empty login o_O\n";
                return true;
            }
            else if (ind == NOT_FOUND)
                cout << "\"" << login << "\" cannot be found here!\n";
            else if (current_account.login == login)
                cout << "The current account cannot be removed!\n";
            else
                break; // found
            ind = input_login(login);
        }
        for (int i = ind; i < n_accounts - 1; ++i)
            accounts[i] = accounts[i + 1];
        --n_accounts;
        if (!write_accounts())
            return false;
        cout << "Successfully removed!\n";
    }
    else
    {
        int route_number = -1;
        int ind = input_route_number(route_number);
        while (true)
        {
            if (ind == EMPTY)
            {
                cout << "Empty route number o_O\n";
                return true;
            }
            else if (ind == NOT_POSITIVE)
                cout << "[tongue clicking]... A non-negative integer is required!\n";
            else if (ind == NOT_FOUND)
                cout << "\"" << route_number << "\" cannot be found here!\n";
            else
                break; // found
            ind = input_route_number(route_number);
        }
        for (int i = ind; i < n_routes - 1; ++i)
            routes[i] = routes[i + 1];
        --n_routes;
        if (!write_routes())
            return false;
        cout << "Successfully removed!\n";
    }
    return true;
}
