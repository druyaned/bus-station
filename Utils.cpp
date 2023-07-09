#include "Utils.h"

//-AUXILIARY-FUNCTIONS------------------------------------------------------------------------------

/**
 *  An auxiliary function for some parsers;
 *  fills the buffer with the content of the line
 *  starting from the line_index and ending with
 *  the '\0' (including) or the delimiter (excluding);
 *  also skips the delimiter by incrementing the line_ind if needed.
 *  @param  buffer a buffer to fill
 *  @param  line a line with a content to fill the buffer
 *  @param  line_ind an index of the line to start the filling;
 *          will be set after the delimiter or the last filled character
 *  @param  delimiter a character to stop the filling which will be skipped
 *  @return false if the buffer is empty, otherwise true
 */
bool fill_buffer(char *buffer, const char *line, int &line_ind, const char &delimiter)
{
    int i = 0;
    for (; line[line_ind] != '\0' && line[line_ind] != delimiter; ++i, ++line_ind)
        buffer[i] = line[line_ind];
    buffer[i] = '\0';
    if (line[line_ind] == delimiter)
        ++line_ind; // skip delimiter
    if (i == 0)
        return false;
    return true;
}

/**
 *  An auxiliary function for some parsers;
 *  fills the buffer with the content of the line
 *  starting from the line_index and ending with the '\0' (including).
 *  @param  buffer a buffer to fill
 *  @param  line a line with a content to fill the buffer
 *  @param  line_ind an index of the line to start the filling;
 *          will be set after the last filled character
 *  @return false if the buffer is empty, otherwise true
 */
bool fill_buffer(char *buffer, const char *line, int &line_ind)
{
    int i = 0;
    for (; line[line_ind] != '\0'; ++i, ++line_ind)
        buffer[i] = line[line_ind];
    buffer[i] = '\0';
    if (i == 0)
        return false;
    return true;
}

//-PARSERS------------------------------------------------------------------------------------------

bool parse_int(int &variable, const char *line)
{
    if (line[0] == '\0') // empty line
        return false;
    if (line[0] == '0' && line[1] == '\0') // 0 case
    {
        variable = 0;
        return true;
    } // else positive or negative values
    size_t length = strlen(line);
    char ch;
    int temp_val = 0, d = 1;
    for (size_t i = length - 1; 1 <= i; --i, d *= 10)
    {
        ch = line[i];
        if ('9' < ch || ch < '0')
            return false;
        temp_val += (ch - '0') * d;
    }
    char ch0 = line[0], ch1 = line[1]; // if ch0 == '+' or '-' then ch1 is in range [1, 9]
    if (ch0 == '+')                    // else ch0 is in range [1, 9]
    {
        if ('9' < ch1 || ch1 < '1')
            return false;
        variable = temp_val;
        return true;
    }
    else if (ch0 == '-')
    {
        if ('9' < ch1 || ch1 < '1')
            return false;
        variable = -temp_val;
        return true;
    }
    else if ('9' < ch0 || ch0 < '1')
        return false;
    variable = temp_val + (ch0 - '0') * d;
    return true;
}

bool parse_account_type(AccountType &type, const char *line)
{
    if (strcmp(line, "USER") == 0)
        type = AccountType::USER;
    else if (strcmp(line, "ADMIN") == 0)
        type = AccountType::ADMIN;
    else
        return false;
    return true;
}

bool parse_bus_type(BusType &type, const char *line)
{
    if (strcmp(line, "SMALL") == 0)
        type = BusType::SMALL;
    else if (strcmp(line, "MEDIUM") == 0)
        type = BusType::MEDIUM;
    else if (strcmp(line, "LARGE") == 0)
        type = BusType::LARGE;
    else
        return false;
    return true;
}

bool parse_date_time(DateTime &date_time, const char *line)
{
    char buffer[MAX_INPUT_SIZE] = "";
    int line_ind = 0;
    if (!fill_buffer(buffer, line, line_ind, '-'))
        return false;
    int year = -1;
    if (!parse_int(year, buffer) || year < 0)
        return false;
    if (!fill_buffer(buffer, line, line_ind, '-'))
        return false;
    int month = -1;
    if (!parse_int(month, buffer) || 12 < month || month < 1)
        return false;
    if (!fill_buffer(buffer, line, line_ind, 't'))
        return false;
    int day = -1;
    if (!parse_int(day, buffer) || 31 < day || day < 1)
        return false;
    if (!fill_buffer(buffer, line, line_ind, '-'))
        return false;
    int hour = -1;
    if (!parse_int(hour, buffer) || 23 < hour || hour < 0)
        return false;
    if (!fill_buffer(buffer, line, line_ind))
        return false;
    int minute = -1;
    if (!parse_int(minute, buffer) || 59 < minute || minute < 0)
        return false;
    date_time = { year, month, day, hour, minute };
    return true;
}

bool parse_account(Account &account, const char *line)
{
    char buffer[MAX_INPUT_SIZE] = "";
    int line_ind = 0;
    if (!fill_buffer(buffer, line, line_ind, DELIMITER))
        return false;
    string login = buffer;
    if (!fill_buffer(buffer, line, line_ind, DELIMITER))
        return false;
    AccountType type {};
    if (!parse_account_type(type, buffer))
        return false;
    if (!fill_buffer(buffer, line, line_ind))
        return false;
    string password = buffer;
    account = { login, type, password };
    return true;
}

bool parse_route(BusRoute &route, const char *line)
{
    char buffer[MAX_INPUT_SIZE] = "";
    int line_ind = 0;
    if (!fill_buffer(buffer, line, line_ind, DELIMITER))
        return false;
    int route_number = -1;
    if (!parse_int(route_number, buffer) || route_number < 0)
        return false;
    if (!fill_buffer(buffer, line, line_ind, DELIMITER))
        return false;
    BusType type {};
    if (!parse_bus_type(type, buffer))
        return false;
    if (!fill_buffer(buffer, line, line_ind, DELIMITER))
        return false;
    string destination = buffer;
    if (!fill_buffer(buffer, line, line_ind, DELIMITER))
        return false;
    DateTime departure {};
    if (!parse_date_time(departure, buffer))
        return false;
    if (!fill_buffer(buffer, line, line_ind, DELIMITER))
        return false;
    DateTime arrival {};
    if (!parse_date_time(arrival, buffer))
        return false;
    if (!fill_buffer(buffer, line, line_ind, DELIMITER))
        return false;
    int ticket_cost_BYN = -1;
    if (!parse_int(ticket_cost_BYN, buffer) || ticket_cost_BYN < 0)
        return false;
    if (!fill_buffer(buffer, line, line_ind, DELIMITER))
        return false;
    int n_tickets = -1;
    if (!parse_int(n_tickets, buffer) || n_tickets < 0)
        return false;
    if (!fill_buffer(buffer, line, line_ind))
        return false;
    int tickets_left = -1;
    if (!parse_int(tickets_left, buffer) || tickets_left < 0)
        return false;
    route = { route_number, type, destination, departure,
            arrival, ticket_cost_BYN, n_tickets, tickets_left };
    return true;
}

//-WRITERS------------------------------------------------------------------------------------------

bool write_account_to_file(const Account &account)
{
    ofstream fout(FILE_OF_ACCOUNTS, ios::out | ios::app);
    if (!fout.is_open())
    {
        cout << "The file \"" << FILE_OF_ACCOUNTS << "\" cannot be openned.\n";
        return false;
    }
    write_account_to_file(account, fout);
    fout.close();
    return true;
}

bool write_route_to_file(const BusRoute &route)
{
    ofstream fout(FILE_OF_ROUTES, ios::out | ios::app);
    if (!fout.is_open())
    {
        cout << "The file \"" << FILE_OF_ROUTES << "\" cannot be openned.\n";
        return false;
    }
    write_route_to_file(route, fout);
    fout.close();
    return true;
}

//-SHOWERS------------------------------------------------------------------------------------------

void show_accounts()
{
    puts("Accounts:");
    puts("              login|   type|           password");
    puts("-------------------+-------+-------------------");
    for (int i = 0; i < n_accounts; ++i)
    {
        printf("%19s|%7s|%19s\n",
               accounts[i].login.c_str(),
               account_type_as_string(accounts[i].type).c_str(),
               accounts[i].password.c_str());
    }
    printf("Number of accounts: %d\n", n_accounts);
}

void show_routes()
{
    puts("Bus Routes:");
    puts("number|  type|         destination|       departure|         arrival|cost|tickets|left");
    puts("------+------+--------------------+----------------+----------------+----+-------+----");
    for (int i = 0; i < n_routes; ++i)
    {
        printf("%6d|%6s|%20s|%16s|%16s|%4d|%7d|%4d\n",
               routes[i].route_number,
               bus_type_as_string(routes[i].type).c_str(),
               routes[i].destination.c_str(),
               routes[i].departure.as_string().c_str(),
               routes[i].arrival.as_string().c_str(),
               routes[i].ticket_cost_BYN,
               routes[i].n_tickets,
               routes[i].tickets_left);
    }
    printf("Number of routes: %d\n", n_routes);
}

//-INPUT-FUNCTIONS----------------------------------------------------------------------------------

int make_choice(const char &from, const char &to, const string &prompt_menu)
{
    char ch0;
    char input[MAX_INPUT_SIZE];
    cout << prompt_menu;
    cin.getline(input, MAX_INPUT_SIZE);
    while (cin)
    {
        ch0 = input[0];
        if (ch0 == '\0' || input[1] != '\0' || to < ch0 || ch0 < from)
        { // if (input.length != 1) && (ch0 ∉ [from, to])
            cout << "Required digit is in the range from '"
                << from << "' to '" << to << "'.\n" << prompt_menu;
            cin.getline(input, MAX_INPUT_SIZE);
            continue;
        }
        return ch0 - '0';
    }
    cout << "System input fails...\n";
    return -1;
}

int input_login(string &login)
{
    cout << "Login: ";
    getline(cin, login);
    if (login.empty())
        return EMPTY;
    int ind = NOT_FOUND;
    for (int i = 0; i < n_accounts; ++i)
    {
        if (accounts[i].login == login)
        {
            ind = i;
            break;
        }
    }
    return ind;
}

int input_route_number(int &route_number)
{
    char input[MAX_INPUT_SIZE] = "";
    cout << "Bus route number: ";
    cin.getline(input, MAX_INPUT_SIZE);
    if (input[0] == '\0')
        return EMPTY;
    if (!parse_int(route_number, input) || route_number < 0)
        return NOT_POSITIVE;
    int ind = NOT_FOUND;
    for (int i = 0; i < n_routes; ++i)
    {
        if (routes[i].route_number == route_number)
        {
            ind = i;
            break;
        }
    }
    return ind;
}

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
        cout << "Empty password o_O\n";
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
        cout << "Empty destination o_O\n";
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
    if (!parse_int(ticket_cost_BYN, input) || ticket_cost_BYN < 0)
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
    if (!parse_int(n_tickets, input) || n_tickets < 0)
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
    if (!parse_int(tickets_left, input) || tickets_left < 0)
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
