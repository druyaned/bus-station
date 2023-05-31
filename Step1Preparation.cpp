#include "Utils.h"

extern Account accounts[MAX_N_ACCOUNTS];
extern int n_accounts;
extern BusRoute routes[MAX_N_ROUTES];
extern int n_routes;

//-CONSTANTS----------------------------------------------------------------------------------------

const int GEN_SIZE = 41;

//-FUNCTIONS----------------------------------------------------------------------------------------

void generate_accounts()
{
    cout << "Generating accounts...\n";
    int i;
    for (i = 0; i < GEN_SIZE; ++i)
    {
        string num = to_string(i);
        accounts[i] =
        {
            "login" + num,
            i % 2 ? AccountType::USER : AccountType::ADMIN,
            "pass" + num
        };
    }
    n_accounts = i;
}

void generate_routes()
{
    cout << "Generating bus routes...\n";
    int i;
    for (i = 0; i < GEN_SIZE; ++i)
    {
        string num = to_string(i);
        DateTime departure =
        {
            2023,
            9 + i % 3,      // month
            8 + i % 9,      // day
            8 + i % 11,     // hour
            15 * (i % 4),   // minute
        };
        DateTime arrival =
        {
            2023,
            9 + i % 3,      // month
            9 + i % 9,      // day
            7 + i % 11,     // hour
            15 * (i % 4),   // minute
        };
        int n_tickets = 32 + i % 17;
        int tickets_left = n_tickets - i % 8;
        routes[i] =
        {
            i,          // route_number
            i % 3 == 0 ? BusType::SMALL : (i % 3 == 1 ? BusType::MEDIUM : BusType::LARGE),
            "destination" + num,
            departure,
            arrival,
            10 + i % 6, // ticket_cost_BYN
            n_tickets,
            tickets_left
        };
    }
    n_routes = i;
}

bool write_accounts()
{
    cout << "Writing accounts...\n";
    ofstream fout(FILE_OF_ACCOUNTS, ios::out | ios::trunc); // will be created if it hasn't been
    if (!fout.is_open())
    {
        cout << "The file \"" << FILE_OF_ACCOUNTS << "\" cannot be openned...\n";
        return false;
    }
    fout << "login;type;password\n"; // header
    for (int i = 0; i < n_accounts; ++i)
        write_account_to_file(accounts[i], fout);
    fout.close();
    return true;
}

bool write_routes()
{
    cout << "Writing bus routes...\n";
    ofstream fout(FILE_OF_ROUTES, ios::out | ios::trunc); // will be created if it hasn't been
    if (!fout.is_open())
    {
        cout << "The file \"" << FILE_OF_ROUTES << "\" cannot be openned...\n";
        return false;
    }
    fout << "route_number;type;destination;departure;arrival;"
            "ticket_cost_BYN;n_tickets;tickets_left\n"; // header
    for (int i = 0; i < n_routes; ++i)
        write_route_to_file(routes[i], fout);
    fout.close();
    return true;
}

bool read_accounts()
{
    ifstream fin(FILE_OF_ACCOUNTS);
    if (fin.fail()) // failed to open; the implication is that the file doesn't exist
    {
        generate_accounts();
        if (!write_accounts())
            return false;
        return true;
    }
    cout << "Reading accounts...\n";
    n_accounts = 0; // to clear the accounts
    char line[MAX_INPUT_SIZE] = "";
    fin.getline(line, MAX_INPUT_SIZE); // header
    fin.getline(line, MAX_INPUT_SIZE); // 1st line
    while (fin)
    {
        Account acc {};
        if (!parse_account(acc, line))
        {
            fin.close();
            cout << "Number of read accounts: " << n_accounts << ".\n";
            return true;
        }
        accounts[n_accounts++] = acc;
        fin.getline(line, MAX_INPUT_SIZE); // next line
    }
    fin.close();
    cout << "Number of read accounts: " << n_accounts << ".\n";
    return true;
}

bool read_routes()
{
    ifstream fin(FILE_OF_ROUTES);
    if (fin.fail()) // failed to open; the implication is that the file doesn't exist
    {
        generate_routes();
        if (!write_routes())
            return false;
        return true;
    }
    cout << "Reading routes...\n";
    n_routes = 0; // to clear the routes
    char line[MAX_INPUT_SIZE] = "";
    fin.getline(line, MAX_INPUT_SIZE); // header
    fin.getline(line, MAX_INPUT_SIZE); // 1st line
    while (fin)
    {
        BusRoute route {};
        if (!parse_route(route, line))
        {
            fin.close();
            cout << "Number of read bus routes: " << n_routes << ".\n";
            return true;
        }
        routes[n_routes++] = route;
        fin.getline(line, MAX_INPUT_SIZE); // next line
    }
    fin.close();
    cout << "Number of read bus routes: " << n_routes << ".\n";
    return true;
}
