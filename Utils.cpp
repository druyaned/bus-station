#include "Utils.h"

//-AUXILIARY-FUNCTIONS------------------------------------------------------------------------------

/**
 *  An auxiliary function for some parsers;
 *  fills the {@code buffer} with the content of the {@code line}
 *  starting from the {@code line_index} and ending with
 *  the {@code '\0'} (including) or the {@code delimiter} (excluding);
 *  also skips the {@code delimiter} by incrementing the {@code line_ind} if needed.
 *  @param  buffer a buffer to fill
 *  @param  line a line with a content to fill the {@code buffer}
 *  @param  line_ind an index of the {@code line} to start the filling;
 *          will be set after the delimiter or the last filled character
 *  @param  delimiter a character to stop the filling which will be skipped
 *  @return false if the {@code buffer} is empty, otherwise true
 */
inline bool fill_buffer(char *buffer, const char *line, int &line_ind, const char &delimiter)
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
 *  fills the {@code buffer} with the content of the {@code line}
 *  starting from the {@code line_index} and ending with the {@code '\0'} (including).
 *  @param  buffer a buffer to fill
 *  @param  line a line with a content to fill the {@code buffer}
 *  @param  line_ind an index of the {@code line} to start the filling;
 *          will be set after the last filled character
 *  @return false if the {@code buffer} is empty, otherwise true
 */
inline bool fill_buffer(char *buffer, const char *line, int &line_ind)
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
    if (!parse_int(year, buffer))
        return false;
    if (!fill_buffer(buffer, line, line_ind, '-'))
        return false;
    int month = -1;
    if (!parse_int(month, buffer))
        return false;
    if (!fill_buffer(buffer, line, line_ind, 't'))
        return false;
    int day = -1;
    if (!parse_int(day, buffer))
        return false;
    if (!fill_buffer(buffer, line, line_ind, '-'))
        return false;
    int hour = -1;
    if (!parse_int(hour, buffer))
        return false;
    if (!fill_buffer(buffer, line, line_ind))
        return false;
    int minute = -1;
    if (!parse_int(minute, buffer))
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
    if (!parse_int(route_number, buffer))
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
    if (!parse_int(ticket_cost_BYN, buffer))
        return false;
    if (!fill_buffer(buffer, line, line_ind, DELIMITER))
        return false;
    int n_tickets = -1;
    if (!parse_int(n_tickets, buffer))
        return false;
    if (!fill_buffer(buffer, line, line_ind))
        return false;
    int tickets_left = -1;
    if (!parse_int(tickets_left, buffer))
        return false;
    route = { route_number, type, destination, departure,
            arrival, ticket_cost_BYN, n_tickets, tickets_left };
    return true;
}

//-WRITERS------------------------------------------------------------------------------------------

void write_account_to_file(const Account &account)
{
    ofstream fout(FILE_OF_ACCOUNTS, ios::out | ios::app);
    if (!fout.is_open())
    {
        cout << "Error: the file \"" << FILE_OF_ACCOUNTS << "\" could NOT be openned.\n";
        cout << "Exiting...\n";
        exit(EXIT_FAILURE);
    }
    write_account_to_file(account, fout);
    fout.close();
}

void write_route_to_file(const BusRoute &route)
{
    ofstream fout(FILE_OF_ROUTES, ios::out | ios::app);
    if (!fout.is_open())
    {
        cout << "Error: the file \"" << FILE_OF_ROUTES << "\" could NOT be openned.\n";
        cout << "Exiting...\n";
        exit(EXIT_FAILURE);
    }
    write_route_to_file(route, fout);
    fout.close();
}

//-OTHER-FUNCTIONS----------------------------------------------------------------------------------

int make_choice(const char &from, const char &to, const string &prompt_menu)
{
    char ch0;
    char input[MAX_INPUT_SIZE];
    cout << prompt_menu;
    cin.getline(input, MAX_INPUT_SIZE);
    while (cin)
    {
        ch0 = input[0];
        if (ch0 == '\0' || input[1] != '\0') // if input.length != 1
        {
            cout << "The required digit is in the range from "
                << from << " to " << to << ".\n" << prompt_menu;
            cin.getline(input, MAX_INPUT_SIZE);
            continue;
        } // if input.length == 1
        if (from <= ch0 && ch0 <= to)
            return ch0 - '0'; // all's good
        cout << "The required digit is in the range from "
            << from << " to " << to << ".\n" << prompt_menu;
        cin.getline(input, MAX_INPUT_SIZE);
    }
    if (!cin)
    {
        cout << "Error with the system input stream. Exiting...\n";
        exit(EXIT_FAILURE);
    }
    return -1; // fail value
}
