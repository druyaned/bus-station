#ifndef Utils_h
#define Utils_h

#include "Step1Preparation.h"
#include "Step2AccountEnter.h"
#include "Step3AccountActions.h" // includes "BusStation.h"
#include <utility>

extern Account accounts[MAX_N_ACCOUNTS];
extern int n_accounts;
extern BusRoute routes[MAX_N_ROUTES];
extern int n_routes;

//-CONSTANTS----------------------------------------------------------------------------------------

int const EMPTY = -3;
int const NOT_POSITIVE = -2;
int const NOT_FOUND = -1;

//-STRING-REPRESENTATIONS---------------------------------------------------------------------------

/**
 *  Returns a string representation of the type or an empty line ("").
 *  @param  type    to represent
 *  @return a string representation of the type or an empty line ("")
 */
inline string account_type_as_string(AccountType const& type)
{
    return type == AccountType::USER ? "USER" :
        (type == AccountType::ADMIN ? "ADMIN" : "");
}

/**
 *  Returns a string representation of the type or an empty line ("").
 *  @param  type    to represent
 *  @return a string representation of the type or an empty line ("")
 */
inline string bus_type_as_string(BusType const& type)
{
    return type == BusType::SMALL ? "SMALL" :
        (type == BusType::MEDIUM ? "MEDIUM" :
         (type == BusType::LARGE ? "LARGE" : ""));
}

//-PARSERS------------------------------------------------------------------------------------------

/**
 *  Parses the line to fill the variable.
 *  @param  variable    to be filled
 *  @param  line    to be parsed;
 *          must match the regular expression: "(0)|([+-]?[1-9][0-9]*)"
 *  @return false if the parsing fails (see line parameter),
 *          otherwise true with filling the variable by the parsed value
 */
bool parse_int(int& variable, char const* line);

/**
 *  Parses the line to fill the type.
 *  @param  type    to be filled
 *  @param  line    to be parsed;
 *          must be equal to the name of one of the AccountType variables
 *  @return false if the parsing fails (see line parameter),
 *          otherwise true with filling the type by the parsed data
 */
bool parse_account_type(AccountType& type, char const* line);

/**
 *  Parses the line to fill the type.
 *  @param  type    to be filled
 *  @param  line    to be parsed;
 *          must be equal to the name of one of the BusType variables
 *  @return false if the parsing fails (see line parameter),
 *          otherwise true with filling the type by the parsed data
 */
bool parse_bus_type(BusType& type, char const* line);

/**
 *  Parses the line to fill the date_time.
 *  @param  date_time   to be filled
 *  @param  line    to be parsed;
 *          must match the format of the DateTime#as_string method
 *  @return false if the parsing fails (see line parameter),
 *          otherwise true with filling the date_time by the parsed data
 */
bool parse_date_time(DateTime& date_time, char const* line);

/**
 *  Parses the line to fill the account.
 *  @param  account to be filled
 *  @param  line    to be parsed;
 *          must match the format which is set by the write_account_to_file method
 *  @return false if the parsing fails (see line parameter),
 *          otherwise true with filling the account by the parsed data
 */
bool parse_account(Account& account, char const* line);

/**
 *  Parses the line to fill the route.
 *  @param  route   to be filled
 *  @param  line    to be parsed;
 *          must match the format which is set by the write_route_to_file method
 *  @return false if the parsing fails (see line parameter),
 *          otherwise true with filling the route by the parsed data
 */
bool parse_route(BusRoute& route, char const* line);

//-WRITERS------------------------------------------------------------------------------------------

/**
 *  Writes the account in a .csv friendly format
 *  into the fout; does NOT change the accounts.
 *  @param  account to write
 *  @param  fout    to be written
 */
inline void write_account_to_file(Account const& account, ofstream& fout)
{
    fout << account.login << DELIMITER
        << account_type_as_string(account.type) << DELIMITER
        << account.password << '\n';
}

/**
 *  Writes the account in a .csv friendly format
 *  into the FILE_OF_ACCOUNTS; does NOT change the accounts.
 *  @param  account to write
 *  @return false if an I/O error occurs, otherwise true
 */
bool write_account_to_file(Account const& account);

/**
 *  Writes the route in a .csv friendly format
 *  into the fout; does NOT change the routes.
 *  @param  route   to write
 *  @param  fout    to be written
 */
inline void write_route_to_file(BusRoute const& route, ofstream& fout)
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
 *  Writes the route in a .csv friendly format
 *  into the FILE_OF_ROUTES; does NOT change the routes.
 *  @param  route   to write
 *  @return false if an I/O error occurs, otherwise true
 */
bool write_route_to_file(BusRoute const& route);

//-SHOWERS------------------------------------------------------------------------------------------

/** Iterably prints each element of the accounts to the system-out. */
void show_accounts();

/** Iterably prints each element of the routes to the system-out. */
void show_routes();

//-INPUT-FUNCTIONS----------------------------------------------------------------------------------

/**
 *  Requests an input
 *  to return a digit choice in the range [from, to]
 *  according to the prompt_menu
 *  or -1 if the choice making fails.
 *  @param  from    a digit representing the first menu item
 *  @param  to  a digit representing the last menu item
 *  @return a digit choice in the range [from, to] according to
 *          the prompt_menu or -1 if the cin fails
 */
int make_choice(char const& from, char const& to, string const& prompt_menu);

/**
 *  Requests a login input with searching it in the accounts.
 *  @param  login   to be filled by the inputted instance
 *  @return EMPTY, NOT_FOUND
 *          or the foundindex} in the accounts
 */
int input_login(string& login);

/**
 *  Requests a route number input with searching it in the routes.
 *  @param  route_number    to be filled by the inputted value
 *  @return EMPTY, NOT_POSITIVE, NOT_FOUND
 *          or the foundindex} in the routes
 */
int input_route_number(int& route_number);

/**
 *  Requests an input of all other fields of the Account
 *  with printing invalid input messages.
 *  @param  login   identifier of the account
 *  @param  account to be filled by the inputted data
 *  @return true if the account is filled, otherwise false
 */
bool input_non_login(string const& login, Account& account);

/**
 *  Requests an input of all other fields of the BusRoute
 *  with printing invalid input messages.
 *  @param  route_number    identifier of the route
 *  @param  route   to be filled by the inputted data
 *  @return true if the route is filled, otherwise false
 */
bool input_non_route_number(const int& route_number, BusRoute& route);

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
 *  @return an index of the found element in the sorted_arr
 *          or -1 if it hasn't been found.
 */
template<typename T> int bin_search(T sorted_arr[], T const& key, int fst_ind, int lst_ind)
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
 *  Exchanges the given values.
 *  @param  el1 first element to exchange
 *  @param  el2 second element to exchange
 */
template<typename T> void swap_elems(T& el1, T& el2)
{
    T buf = el1;
    el1 = el2;
    el2 = buf;
}

/**
 *  An implementation of the
 *  <a href="https://en.wikipedia.org/wiki/Quicksort">
 *  quicksort algorithm
 *  </a>.
 *  @param  arr  array to be sorted
 *  @param  fst_ind first index of the arr to apply the sorting
 *  @param  lst_ind last index of the arr to apply the sorting
 *  @param  compare comparator to compare 2 elements of the arr
 */
template<typename T> void quick_sort(T arr[], int fst_ind, int lst_ind,
    int (*compare)(T const& o1, T const& o2) =
        [](T const& o1, T const& o2) {return o1 < o2 ? -1 : (o1 == o2 ? 0 : 1);})
{
    if (lst_ind <= fst_ind)
        return;
    // partition
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
    // sort parts
    quick_sort(arr, fst_ind, pivot_ind - 1, compare); // sort left part
    quick_sort(arr, pivot_ind + 1, lst_ind, compare); // sort right part
}

#endif /* Utils_h */
