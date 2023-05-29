#include "Utils.h"

extern Account accounts[MAX_N_ACCOUNTS];
extern int n_accounts; // number of accounts
extern BusRoute routes[MAX_N_ROUTES];
extern int n_routes; // number of routes

//-Functions----------------------------------------------------------------------------------------

void generate_accounts()
{
    cout << "Generating accounts...\n";
    int i;
    for (i = 0; i < MAX_N_ACCOUNTS / 2; ++i)
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
    for (i = 0; i < MAX_N_ROUTES / 2; ++i)
    {
        string num = to_string(i);
        DateTime departure =
        {
            2023,
            9 + i % 3, // month
            8 + i % 9, // day
            8 + i % 11, // hour
            15 * (i % 4), // minute
        };
        DateTime arrival =
        {
            2023,
            9 + i % 3, // month
            9 + i % 9, // day
            7 + i % 11, // hour
            15 * (i % 4), // minute
        };
        int n_tickets = 32 + i % 17;
        int tickets_left = n_tickets - i % 8;
        routes[i] =
        {
            i, // route_number
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

void write_accounts()
{
    cout << "Writing accounts...\n";
    ofstream fout(FILE_OF_ACCOUNTS, ios::out | ios::trunc); // will be created if it hasn't been
    if (!fout.is_open())
    {
        cout << "Error: the file \"" << FILE_OF_ACCOUNTS << "\" could NOT be openned.\n";
        cout << "Exiting...\n";
        exit(EXIT_FAILURE);
    }
    fout << "login;type;password\n"; // header
    for (int i = 0; i < n_accounts; ++i)
        write_account_to_file(accounts[i], fout);
    fout.close();
}

void write_routes()
{
    cout << "Writing bus routes...\n";
    ofstream fout(FILE_OF_ROUTES, ios::out | ios::trunc); // will be created if it hasn't been
    if (!fout.is_open())
    {
        cout << "Error: the file \"" << FILE_OF_ROUTES << "\" could NOT be openned.\n";
        cout << "Exiting...\n";
        exit(EXIT_FAILURE);
    }
    fout << "route_number;type;destination;departure;arrival;"
            "ticket_cost_BYN;n_tickets;tickets_left\n"; // header
    for (int i = 0; i < n_routes; ++i)
        write_route_to_file(routes[i], fout);
    fout.close();
}

void read_accounts()
{
    ifstream fin(FILE_OF_ACCOUNTS);
    if (fin.fail()) // failed to open; the implication is that the file doesn't exist
    {
        generate_accounts();
        write_accounts();
        return;
    }
    if (!fin.is_open())
    {
        cout << "Error: the file \"" << FILE_OF_ACCOUNTS << "\" could NOT be openned.\n";
        cout << "Exiting...\n";
        exit(EXIT_FAILURE);
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
            break;
        accounts[n_accounts++] = acc;
        fin.getline(line, MAX_INPUT_SIZE); // next line
    }
    fin.close();
}

void read_routes()
{
    ifstream fin(FILE_OF_ROUTES);
    if (fin.fail()) // failed to open; the implication is that the file doesn't exist
    {
        generate_routes();
        write_routes();
        return;
    }
    if (!fin.is_open())
    {
        cout << "Error: the file \"" << FILE_OF_ROUTES << "\" could NOT be openned.\n";
        cout << "Exiting...\n";
        exit(EXIT_FAILURE);
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
            break;
        routes[n_routes++] = route;
        fin.getline(line, MAX_INPUT_SIZE); // next line
    }
    fin.close();
}
