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
const int EMPTY = -2;
const int NOT_FOUND = -1;

//-AUXILIARY-FUNCTIONS------------------------------------------------------------------------------

/**
 *  Provides an input of MENU-OF-SCRUCTURES.
 *  Structure menu to choose between ACCOUNTS adn BUS_ROUTES.
 */
void define_structure_type(StructureType &st)
{
    string sctruct_menu = "[MENU-OF-SCRUCTURES]:\n0. quit\n1. accounts\n2. bus routes\n: ";
    int choice = make_choice('0', '2', sctruct_menu);
    switch (choice)
    {
        case 0: quit(); break;
        case 1: st = ACCOUNTS; break;
        case 2: st = BUS_ROUTES; break;
        default:
            cout << "Something went wrong. Exiting...\n";
            exit(EXIT_FAILURE);
            return;
    }
}

/**
 *  Returns EMPTY, NOT_FOUND or found index in the accounts.
 *  In fail case does NOT print any messages.
 */
int input_login(string &login)
{
    cout << "Login: ";
    getline(cin, login);
    if (login.empty())
        return EMPTY;
    int found_ind = NOT_FOUND;
    for (int i = 0; i < n_accounts; ++i)
    {
        if (accounts[i].login == login)
        {
            found_ind = i;
            break;
        }
    }
    return found_ind;
}

/**
 *  Returns EMPTY (if input fails or it's negative), NOT_FOUND or
 *  found index in the routes.
 *  In fail case does NOT print any messages.
 */
int input_route_number(int &route_number)
{
    char input[MAX_INPUT_SIZE] = "";
    cout << "Bus route number: ";
    cin.getline(input, MAX_INPUT_SIZE);
    if (!parse_int(route_number, input)) // input fails
        return EMPTY;
    if (route_number < 0) // if negative
        return EMPTY;
    int found_ind = NOT_FOUND;
    for (int i = 0; i < n_routes; ++i)
    {
        if (routes[i].route_number == route_number)
        {
            found_ind = i;
            break;
        }
    }
    return found_ind;
}

/** Returns false if input failed. */
bool input_non_login(const string &login, Account &account)
{
    char input[MAX_INPUT_SIZE] = "";
    cout << "Type (USER or ADMIN): ";
    cin.getline(input, MAX_INPUT_SIZE);
    AccountType type {};
    if (!parse_account_type(type, input))
    {
        cout << "Invalid type!\n";
        return false;
    }
    string password {};
    cout << "Password: ";
    getline(cin, password);
    if (password.empty())
    {
        cout << "Password can't be empty!\n";
        return false;
    }
    account = { login, type, password };
    return true;
}

bool input_non_route_number(const int &route_number, BusRoute &route)
{
    char input[MAX_INPUT_SIZE] = "";
    cout << "type (SMALL, MEDIUM or LARGE): ";
    cin.getline(input, MAX_INPUT_SIZE);
    BusType type {};
    if (!parse_bus_type(type, input))
    {
        cout << "Invalid type!\n";
        return false;
    }
    string destination {};
    cout << "Destination: ";
    getline(cin, destination);
    if (destination.empty())
    {
        cout << "Destination can't be empty!\n";
        return false;
    }
    cout << "Departure (example: 2023-9-22t17-0): ";
    cin.getline(input, MAX_INPUT_SIZE);
    DateTime departure {};
    if (!parse_date_time(departure, input))
    {
        cout << "Invalid departure!\n";
        return false;
    }
    cout << "Arrival (example: 2023-9-23t17-0): ";
    cin.getline(input, MAX_INPUT_SIZE);
    DateTime arrival {};
    if (!parse_date_time(arrival, input))
    {
        cout << "Invalid arrival!\n";
        return false;
    }
    int ticket_cost_BYN = -1;
    cout << "Ticket cost (in BYN and integer): ";
    cin.getline(input, MAX_INPUT_SIZE);
    if (!parse_int(ticket_cost_BYN, input))
    {
        cout << "Invalid ticket cost!\n";
        return false;
    }
    if (ticket_cost_BYN < 0)
    {
        cout << "Ticket cost can't be negative!\n";
        return false;
    }
    int n_tickets = -1;
    cout << "Number of tickets: ";
    cin.getline(input, MAX_INPUT_SIZE);
    if (!parse_int(n_tickets, input))
    {
        cout << "Invalid number of tickets!\n";
        return false;
    }
    if (n_tickets < 0)
    {
        cout << "Number of tickets can't be negative!\n";
        return false;
    }
    int tickets_left = -1;
    cout << "Tickets left: ";
    cin.getline(input, MAX_INPUT_SIZE);
    if (!parse_int(tickets_left, input))
    {
        cout << "Invalid input!\n";
        return false;
    }
    if (tickets_left < 0)
    {
        cout << "Can't be negative!\n";
        return false;
    }
    route = { route_number, type, destination, departure, arrival,
        ticket_cost_BYN, n_tickets, tickets_left };
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

inline int by_departure(const BusRoute &r1, const BusRoute &r2)
{
    DateTime dt1 = r1.departure;
    DateTime dt2 = r2.departure;
    ll m1 = dt1.year * MINUTES_IN_YEAR + dt1.month * MINUTES_IN_MONTH +
        dt1.day * MINUTES_IN_DAY + dt1.hour * MINUTES_IN_HOUR + dt1.minute;
    ll m2 = dt2.year * MINUTES_IN_YEAR + dt2.month * MINUTES_IN_MONTH +
        dt2.day * MINUTES_IN_DAY + dt2.hour * MINUTES_IN_HOUR + dt2.minute;
    return m1 < m2 ? -1 : (m1 == m2 ? 0 : 1);
}

inline int by_arrival(const BusRoute &r1, const BusRoute &r2)
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

//-FUNCTIONS----------------------------------------------------------------------------------------

void user_actions(bool &outer_loop) // menu
{
    string actions_menu = "[STRUCTURE-TYPE]: Bus Routes\n"
        "[MENU-OF-ACTIONS]:\n0. quit\n1. view\n2. search\n3. sort\n"
        "4. enter-menu\n: ";
    int choice;
    bool user_loop = true;
    while (user_loop)
    {
        choice = make_choice('0', '4', actions_menu);
        switch (choice)
        {
            case 0: user_loop = outer_loop = !quit(); break;
            case 1: user_loop = view(BUS_ROUTES); break;
            case 2: user_loop = search(BUS_ROUTES); break;
            case 3: user_loop = sort(BUS_ROUTES); break;
            case 4: user_loop = false; account_enter(); break;
            default:
                user_loop = outer_loop = false;
                cout << "Something went wrong. Exiting...";
                exit(EXIT_FAILURE);
                return;
        }
    }
}

void admin_actions(bool &outer_loop) // menu
{
    StructureType struct_type {};
    define_structure_type(struct_type);
    // to choose an action
    string accounts_menu = "[STRUCTURE-TYPE]: Accounts\n"
        "[MENU-OF-ACTIONS]:\n0. quit\n1. view\n2. search\n3. sort\n"
        "4. add\n5. edit\n6. remove\n7. menu-of-scructures\n8. enter-menu\n: ";
    string routes_menu = "[STRUCTURE-TYPE]: Bus Routes\n"
        "[MENU-OF-ACTIONS]:\n0. quit\n1. view\n2. search\n3. sort\n"
        "4. add\n5. edit\n6. remove\n7. menu-of-scructures\n8. enter-menu\n: ";
    int choice;
    bool admin_loop = true;
    while (admin_loop)
    {
        if (struct_type == ACCOUNTS)
            choice = make_choice('0', '8', accounts_menu);
        else
            choice = make_choice('0', '8', routes_menu);
        switch (choice)
        {
            case 0: admin_loop = outer_loop = !quit(); break;
            case 1: admin_loop = view(struct_type); break;
            case 2: admin_loop = search(struct_type); break;
            case 3: admin_loop = sort(struct_type); break;
            case 4: admin_loop = add(struct_type); break;
            case 5: admin_loop = edit(struct_type); break;
            case 6: admin_loop = remove(struct_type); break;
            case 7: define_structure_type(struct_type); break;
            case 8: admin_loop = false; account_enter(); break;
            default:
                admin_loop = outer_loop = false;
                cout << "Something went wrong. Exiting...";
                exit(EXIT_FAILURE);
                return;
        }
    }
}

//-FUNCTIONS:-ACTIONS-------------------------------------------------------------------------------

bool view(StructureType struct_type)
{
    if (struct_type == ACCOUNTS)
        show_accounts();
    else
        show_routes();
    return true;
}

bool search(StructureType struct_type)
{
    if (struct_type == ACCOUNTS)
    {
        string login;
        int ind = input_login(login);
        if (ind == EMPTY)
        {
            cout << "Login can't be empty! Let's keep going!\n";
            return true;
        }
        else if (ind != NOT_FOUND) // if found
        {
            string type_str = accounts[ind].type == USER ? "a user" : "an admin";
            cout << "Great news! There is " << type_str << " with the given login!\n";
        }
        else
            cout << "This login is attractive but there is NO such account here!\n";
    }
    else
    {
        int route_number;
        int ind = input_route_number(route_number);
        if (ind == EMPTY)
        {
            cout << "[tongue clicking]... A non-negative integer is required!\n";
            return true;
        }
        else if (ind != NOT_FOUND) // if found
        {
            cout << "Great news! There is "
                    << bus_type_as_string(routes[ind].type)
                    << " bus with given route number!\n";
            cout << "Here it is: " << routes[ind].as_string() << endl;
        }
        else
            cout << "This number is attractive but there is NO such bus route here!\n";
    }
    return true;
}

bool sort(StructureType struct_type)
{
    if (struct_type == ACCOUNTS)
    {
        string sort_menu = "[SORT-MENU]:\n0. back\n"
                "1. login\n2. type\n3. password\n: ";
        int choice;
        choice = make_choice('0', '3', sort_menu);
        switch (choice)
        {
            case 0: break;
            case 1:
                cout << "Sorting...\n";
                quick_sort(accounts, 0, n_accounts - 1);
                cout << "Successfully sorted!\n";
                write_accounts();
                show_accounts();
                break;
            case 2:
                cout << "Sorting...\n";
                quick_sort(accounts, 0, n_accounts - 1, by_type);
                cout << "Successfully sorted!\n";
                write_accounts();
                show_accounts();
                break;
            case 3:
                cout << "Sorting...\n";
                quick_sort(accounts, 0, n_accounts - 1, by_pass);
                cout << "Successfully sorted!\n";
                write_accounts();
                show_accounts();
                break;
            default:
                cout << "Something went wrong. Exiting...";
                exit(EXIT_FAILURE);
                return false;
        }
    }
    else
    {
        string sort_menu = "[SORT-MENU]:\n0. back\n"
                "1. route number\n2. type\n3. destination\n"
                "4. departure\n5. arrival\n6. ticket cost BYN\n"
                "7. total number of tickets\n8. tickets left\n: ";
        int choice;
        choice = make_choice('0', '8', sort_menu);
        switch (choice)
        {
            case 0: break;
            case 1:
                cout << "Sorting...\n";
                quick_sort(routes, 0, n_routes-1);
                cout << "Successfully sorted!\n";
                write_routes();
                show_routes();
                break;
            case 2:
                cout << "Sorting...\n";
                quick_sort(routes, 0, n_routes-1, by_type);
                cout << "Successfully sorted!\n";
                write_routes();
                show_routes();
                break;
            case 3:
                cout << "Sorting...\n";
                quick_sort(routes, 0, n_routes-1, by_destination);
                cout << "Successfully sorted!\n";
                write_routes();
                show_routes();
                break;
            case 4:
                cout << "Sorting...\n";
                quick_sort(routes, 0, n_routes-1, by_departure);
                cout << "Successfully sorted!\n";
                write_routes();
                show_routes();
                break;
            case 5:
                cout << "Sorting...\n";
                quick_sort(routes, 0, n_routes-1, by_arrival);
                cout << "Successfully sorted!\n";
                write_routes();
                show_routes();
                break;
            case 6:
                cout << "Sorting...\n";
                quick_sort(routes, 0, n_routes-1, by_ticket_cost_BYN);
                cout << "Successfully sorted!\n";
                write_routes();
                show_routes();
                break;
            case 7:
                cout << "Sorting...\n";
                quick_sort(routes, 0, n_routes-1, by_n_tickets);
                cout << "Successfully sorted!\n";
                write_routes();
                show_routes();
                break;
            case 8:
                cout << "Sorting...\n";
                quick_sort(routes, 0, n_routes-1, by_tickets_left);
                cout << "Successfully sorted!\n";
                write_routes();
                show_routes();
                break;
            default:
                cout << "Something went wrong. Exiting...";
                exit(EXIT_FAILURE);
                return false;
        }
    }
    return true;
}

//-FUNCTIONS:-ADMIN-ONLY-ACTIONS--------------------------------------------------------------------

bool add(StructureType struct_type)
{
    if (struct_type == ACCOUNTS)
    {
        if (n_accounts == MAX_N_ACCOUNTS)
        {
            cout << "Sorry, the size of the Accounts Data Base has reached the limit. "
                    "So you can't add a new account.\n";
            return true;
        }
        string login = "";
        int ind = input_login(login);
        if (ind == EMPTY)
        {
            cout << "Login can't be empty!\n";
            return true;
        }
        else if (ind != NOT_FOUND) // if found
        {
            cout << "The login \"" << login << "\" exists!\n";
            return true;
        } // if not found
        Account account;
        if (input_non_login(login, account))
        {
            write_account_to_file(account);
            accounts[n_accounts++] = account;
            cout << "Successfully added!\n";
        }
    }
    else
    {
        if (n_routes == MAX_N_ROUTES)
        {
            cout << "Sorry, the size of the Bus Routes Data Base has reached the limit. "
                    "So you can't add a bus route.\n";
            return true;
        }
        int route_number = -1;
        int ind = input_route_number(route_number);
        if (ind == EMPTY)
        {
            cout << "[tongue clicking]... A non-negative integer is required!\n";
            return true;
        }
        else if (ind != NOT_FOUND) // if found
        {
            cout << "The bus route with the number " << route_number << " exists!\n";
            return true;
        } // if not found
        if (route_number < 0)
        {
            cout << "Route number can't be negative!\n";
            return true;
        }
        BusRoute route;
        if (input_non_route_number(route_number, route))
        {
            write_route_to_file(route);
            routes[n_routes++] = route;
            cout << "Successfully added!\n";
        }
    }
    return true;
}

bool edit(StructureType struct_type)
{
    if (struct_type == ACCOUNTS)
    {
        string login = "";
        int ind = input_login(login);
        if (ind == EMPTY)
        {
            cout << "Login can't be empty!\n";
            return true;
        }
        else if (ind == NOT_FOUND)
        {
            cout << "The login \"" << login << "\" does NOT exists!\n";
            return true;
        } // if found
        Account account;
        if (input_non_login(login, account))
        {
            accounts[ind] = account;
            write_accounts();
            cout << "Successfully edited!\n";
        }
    }
    else
    {
        int route_number = -1;
        int ind = input_route_number(route_number);
        if (ind == EMPTY)
        {
            cout << "[tongue clicking]... A non-negative integer is required!\n";
            return true;
        }
        else if (ind == NOT_FOUND)
        {
            cout << "The bus route with the number " << route_number << " does NOT exists!\n";
            return true;
        } // if found
        BusRoute route;
        if (input_non_route_number(route_number, route))
        {
            routes[ind] = route;
            write_routes();
            cout << "Successfully edited!\n";
        }
    }
    return true;
}

bool remove(StructureType struct_type)
{
    if (struct_type == ACCOUNTS)
    {
        string login = "";
        int ind_to_remove = input_login(login);
        if (ind_to_remove == EMPTY)
        {
            cout << "Login can't be empty!\n";
            return true;
        }
        else if (ind_to_remove == NOT_FOUND)
        {
            cout << "The login \"" << login << "\" does NOT exists!\n";
            return true;
        } // if found
        if (current_account.login == login)
        {
            cout << "Can't remove the current account!\n";
            return true;
        }
        for (int i = ind_to_remove; i < n_accounts - 1; ++i)
            accounts[i] = accounts[i + 1];
        --n_accounts;
        write_accounts();
        cout << "Successfully removed!\n";
    }
    else
    {
        int route_number = -1;
        int ind_to_remove = input_route_number(route_number);
        if (ind_to_remove == EMPTY)
        {
            cout << "[tongue clicking]... A non-negative integer is required!\n";
            return true;
        }
        else if (ind_to_remove == NOT_FOUND)
        {
            cout << "The bus route with the number " << route_number << " does NOT exists!\n";
            return true;
        } // if found
        for (int i = ind_to_remove; i < n_routes - 1; ++i)
            routes[i] = routes[i + 1];
        --n_routes;
        write_routes();
        cout << "Successfully removed!\n";
    }
    return true;
}
