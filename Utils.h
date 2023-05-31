#ifndef Utils_h
#define Utils_h

#include "Step1Preparation.h"
#include "Step2AccountEnter.h"
#include "Step3AccountActions.h" // includes "BusStation.h"

extern Account accounts[MAX_N_ACCOUNTS];
extern int n_accounts;
extern BusRoute routes[MAX_N_ROUTES];
extern int n_routes;

//-CONSTANTS----------------------------------------------------------------------------------------

const int EMPTY = -3;
const int NOT_POSITIVE = -2;
const int NOT_FOUND = -1;

//-STRING-REPRESENTATIONS---------------------------------------------------------------------------

/**
 *  Returns a string representation of the {@code type} or an empty line ("").
 *  @param  type    to represent
 *  @return a string representation of the {@code type} or an empty line ("")
 */
inline string account_type_as_string(const AccountType &type)
{
    return type == AccountType::USER ? "USER" :
        (type == AccountType::ADMIN ? "ADMIN" : "");
}

/**
 *  Returns a string representation of the {@code type} or an empty line ("").
 *  @param  type    to represent
 *  @return a string representation of the {@code type} or an empty line ("")
 */
inline string bus_type_as_string(const BusType &type)
{
    return type == BusType::SMALL ? "SMALL" :
        (type == BusType::MEDIUM ? "MEDIUM" :
         (type == BusType::LARGE ? "LARGE" : ""));
}

//-PARSERS------------------------------------------------------------------------------------------

/**
 *  Parses the {@code line} to fill the {@code variable}.
 *  @param  variable    to be filled
 *  @param  line    to be parsed;
 *          must match the regular expression: "(0)|([+-]?[1-9][0-9]*)"
 *  @return {@code false} if the parsing fails (see {@code line} parameter),
 *          otherwise {@code true} with filling the {@code variable} by the parsed value
 */
bool parse_int(int &variable, const char *line);

/**
 *  Parses the {@code line} to fill the {@code type}.
 *  @param  type    to be filled
 *  @param  line    to be parsed;
 *          must be equal to the name of one of the {@code AccountType} variables
 *  @return {@code false} if the parsing fails (see {@code line} parameter),
 *          otherwise {@code true} with filling the {@code type} by the parsed data
 */
bool parse_account_type(AccountType &type, const char *line);

/**
 *  Parses the {@code line} to fill the {@code type}.
 *  @param  type    to be filled
 *  @param  line    to be parsed;
 *          must be equal to the name of one of the {@code BusType} variables
 *  @return {@code false} if the parsing fails (see {@code line} parameter),
 *          otherwise {@code true} with filling the {@code type} by the parsed data
 */
bool parse_bus_type(BusType &type, const char *line);

/**
 *  Parses the {@code line} to fill the {@code date_time}.
 *  @param  date_time   to be filled
 *  @param  line    to be parsed;
 *          must match the format of the {@code DateTime#as_string} method
 *  @return {@code false} if the parsing fails (see {@code line} parameter),
 *          otherwise {@code true} with filling the {@code date_time} by the parsed data
 */
bool parse_date_time(DateTime &date_time, const char *line);

/**
 *  Parses the {@code line} to fill the {@code account}.
 *  @param  account to be filled
 *  @param  line    to be parsed;
 *          must match the format which is set by the {@code write_account_to_file} method
 *  @return {@code false} if the parsing fails (see {@code line} parameter),
 *          otherwise {@code true} with filling the {@code account} by the parsed data
 */
bool parse_account(Account &account, const char *line);

/**
 *  Parses the {@code line} to fill the {@code route}.
 *  @param  route   to be filled
 *  @param  line    to be parsed;
 *          must match the format which is set by the {@code write_route_to_file} method
 *  @return {@code false} if the parsing fails (see {@code line} parameter),
 *          otherwise {@code true} with filling the {@code route} by the parsed data
 */
bool parse_route(BusRoute &route, const char *line);

//-WRITERS------------------------------------------------------------------------------------------

/**
 *  Writes the {@code account} in a .csv friendly format
 *  into the {@code fout}; does NOT change the {@code accounts}.
 *  @param  account to write
 *  @param  fout    to be written
 */
inline void write_account_to_file(const Account &account, ofstream &fout)
{
    fout << account.login << DELIMITER
        << account_type_as_string(account.type) << DELIMITER
        << account.password << '\n';
}

/**
 *  Writes the {@code account} in a .csv friendly format
 *  into the {@code FILE_OF_ACCOUNTS}; does NOT change the {@code accounts}.
 *  @param  account to write
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool write_account_to_file(const Account &account);

/**
 *  Writes the {@code route} in a .csv friendly format
 *  into the {@code fout}; does NOT change the {@code routes}.
 *  @param  route   to write
 *  @param  fout    to be written
 */
inline void write_route_to_file(const BusRoute &route, ofstream &fout)
{
    fout << route.route_number << DELIMITER
        << bus_type_as_string(route.type) << DELIMITER
        << route.destination << DELIMITER
        << route.departure.as_string() << DELIMITER
        << route.arrival.as_string() << DELIMITER
        << route.ticket_cost_BYN << DELIMITER
        << route.n_tickets << DELIMITER
        << route.tickets_left << '\n';
}

/**
 *  Writes the {@code route} in a .csv friendly format
 *  into the {@code FILE_OF_ROUTES}; does NOT change the {@code routes}.
 *  @param  route   to write
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool write_route_to_file(const BusRoute &route);

//-SHOWERS------------------------------------------------------------------------------------------

/** Iterably prints each element of the {@code accounts} to the system-out. */
inline void show_accounts()
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

/** Iterably prints each element of the {@code routes} to the system-out. */
inline void show_routes()
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

//-ALGORITHMS---------------------------------------------------------------------------------------

/**
 *  An implementation of the
 *  <a href="https://en.wikipedia.org/wiki/Binary_search_algorithm">
 *  binary search algorithm
 *  </a>.
 *  @param  sorted_arr  sorted array to look for
 *  @param  key value of an element to look for
 *  @param  fst_ind   first index of the array for the searching
 *  @param  lst_ind   last index of the array for the searching
 *  @return an index of the found element in the {@code sorted_arr}
 *          or {@code -1} if it hasn't been found.
 */
template<typename T> int bin_search(T sorted_arr[], const T &key, int fst_ind, int lst_ind)
{
    int medium;
    while (fst_ind <= lst_ind)
    {
        medium = fst_ind + (lst_ind - fst_ind) / 2;
        if (sorted_arr[medium] == key)
            return medium;
        if (sorted_arr[medium] < key)
            fst_ind = medium + 1;
        else
            lst_ind = medium - 1;
    }
    return -1; // not found
}

/**
 *  An auxiliary function for the {@code partition}; simply swaps 2 elements.
 *  @param  el1 first element to be swapped
 *  @param  el2 second element to be swapped
 */
template<typename T> inline void swap_elems(T &el1, T&el2)
{
    T temp = el1;
    el1 = el2;
    el2 = temp;
}

/**
 *  An auxiliary function for the {@code quick_sort};
 *  returns the exact position of the swapped pivot-element;
 *  also swaps smaller or equal elements into the back
 *  and bigger elements into the beginning.
 *  @param  arr array to be sorted
 *  @param  fst_ind first index of the {@code arr} to apply the partition
 *  @param  lst_ind last index of the {@code arr} to apply the partition
 *  @return the exact position of the swapped pivot-element;
 *          also swaps smaller or equal elements into the back
 *          and bigger elements into the beginning.
 */
template<typename T> int partition(T arr[], int fst_ind, int lst_ind)
{
    T pivot = arr[fst_ind];
    int count = 0; // count of smaller or equal elements
    for (int i = fst_ind + 1; i <= lst_ind; ++i)
    {
        if (arr[i] <= pivot)
            ++count;
    }
    int pivot_ind = fst_ind + count;
    swap_elems(arr[fst_ind], arr[pivot_ind]);
    for (int low = fst_ind, high = lst_ind; low < pivot_ind && pivot_ind < high;)
    {
        while (arr[low] <= pivot)
            ++low;
        while (pivot < arr[high])
            --high;
        if (low < pivot_ind && pivot_ind < high)
            swap_elems(arr[low++], arr[high--]);
    }
    return pivot_ind;
}

/**
 *  An implementation of the
 *  <a href="https://en.wikipedia.org/wiki/Quicksort">
 *  quicksort algorithm
 *  </a>.
 *  @param  arr  array to be sorted
 *  @param  fst_ind first index of the {@code arr} to apply the sorting
 *  @param  lst_ind last index of the {@code arr} to apply the sorting
 */
template<typename T> void quick_sort(T arr[], int fst_ind, int lst_ind)
{
    if (lst_ind <= fst_ind)
        return;
    int pivot_ind = partition(arr, fst_ind, lst_ind);
    quick_sort(arr, fst_ind, pivot_ind - 1); // sort left part
    quick_sort(arr, pivot_ind + 1, lst_ind); // sort right part
}

/**
 *  An auxiliary function for the {@code quick_sort};
 *  returns the exact position of the swapped pivot-element;
 *  also swaps smaller or equal elements into the back
 *  and bigger elements into the beginning.
 *  @param  arr array to be sorted
 *  @param  fst_ind first index of the {@code arr} to apply the partition
 *  @param  lst_ind last index of the {@code arr} to apply the partition
 *  @param  compare comparator to compare 2 elements of the {@code arr}
 *  @return the exact position of the swapped pivot-element;
 *          also swaps smaller or equal elements into the back
 *          and bigger elements into the beginning.
 */
template<typename T> int partition(T arr[], int fst_ind, int lst_ind,
                                   int (*compare)(const T &, const T &))
{
    T pivot = arr[fst_ind];
    int count = 0; // count of smaller or equal elements
    for (int i = fst_ind + 1; i <= lst_ind; ++i)
    {
        int compare_result = compare(arr[i], pivot);
        if (compare_result < 0 || compare_result == 0)
            ++count;
    }
    int pivot_ind = fst_ind + count;
    swap_elems(arr[fst_ind], arr[pivot_ind]);
    for (int low = fst_ind, high = lst_ind; low < pivot_ind && pivot_ind < high;)
    {
        int compare_result;
        while ((compare_result = compare(arr[low], pivot)) < 0 || compare_result == 0)
            ++low;
        while (compare(pivot, arr[high]) < 0)
            --high;
        if (low < pivot_ind && pivot_ind < high)
            swap_elems(arr[low++], arr[high--]);
    }
    return pivot_ind;
}

/**
 *  An implementation of the
 *  <a href="https://en.wikipedia.org/wiki/Quicksort">
 *  quicksort algorithm
 *  </a>.
 *  @param  arr  array to be sorted
 *  @param  fst_ind first index of the {@code arr} to apply the sorting
 *  @param  lst_ind last index of the {@code arr} to apply the sorting
 *  @param  compare comparator to compare 2 elements of the {@code arr}
 */
template<typename T> void quick_sort(T arr[], int fst_ind, int lst_ind,
                                     int (*compare)(const T &, const T &))
{
    if (lst_ind <= fst_ind)
        return;
    int pivot_ind = partition(arr, fst_ind, lst_ind, compare);
    quick_sort(arr, fst_ind, pivot_ind - 1, compare); // sort left part
    quick_sort(arr, pivot_ind + 1, lst_ind, compare); // sort right part
}

//-INPUT-FUNCTIONS----------------------------------------------------------------------------------

/**
 *  Requests an input
 *  to return a digit choice in the range [{@code from}, {@code to}]
 *  according to the {@code prompt_menu}
 *  or {@code -1} if the choice making fails.
 *  @param  from    a digit representing the first menu item
 *  @param  to  a digit representing the last menu item
 *  @return a digit choice in the range [{@code from}, {@code to}] according to
 *          the {@code prompt_menu} or {@code -1} if the {@code cin} fails
 */
int make_choice(const char &from, const char &to, const string &prompt_menu);

/**
 *  Requests a login input with searching it in the {@code accounts}.
 *  @param  login   to be filled by the inputted instance
 *  @return {@code EMPTY}, {@code NOT_FOUND}
 *          or the {@code found index} in the {@code accounts}
 */
int input_login(string &login);

/**
 *  Requests a route number input with searching it in the {@code routes}.
 *  @param  route_number    to be filled by the inputted value
 *  @return {@code EMPTY}, {@code NOT_POSITIVE}, {@code NOT_FOUND}
 *          or the {@code found index} in the {@code routes}
 */
int input_route_number(int &route_number);

/**
 *  Requests an input of all other fields of the {@code Account}
 *  with printing invalid input messages.
 *  @param  login   identifier of the {@code account}
 *  @param  account to be filled by the inputted data
 *  @return {@code true} if the account is filled, otherwise {@code false}
 */
bool input_non_login(const string &login, Account &account);

/**
 *  Requests an input of all other fields of the {@code BusRoute}
 *  with printing invalid input messages.
 *  @param  route_number    identifier of the {@code route}
 *  @param  route   to be filled by the inputted data
 *  @return {@code true} if the route is filled, otherwise {@code false}
 */
bool input_non_route_number(const int &route_number, BusRoute &route);

#endif /* Utils_h */
