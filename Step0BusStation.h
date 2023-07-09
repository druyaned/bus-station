// step#0: definitions
#ifndef Step0BusStation_h
#define Step0BusStation_h

#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;
using std::to_string;

//-CONSTANTS----------------------------------------------------------------------------------------

const char DELIMITER = ';';                             // .csv delimiter
const int MAX_INPUT_SIZE = (1 << 14) + ((1 << 14) - 1); // 32767 = 0x7FFF
const int MAX_N_ACCOUNTS = MAX_INPUT_SIZE;              // max number of accounts
const int MAX_N_ROUTES = MAX_INPUT_SIZE;                // max number of routes
const string FILE_OF_ACCOUNTS = "accounts.csv";
const string FILE_OF_ROUTES = "bus_routes.csv";

//-ENUMS--------------------------------------------------------------------------------------------

enum StructureType { ACCOUNTS, BUS_ROUTES };
enum AccountType { USER, ADMIN };
enum BusType { SMALL, MEDIUM, LARGE };

//-STRUCTURES---------------------------------------------------------------------------------------

struct DateTime // a simple structure of date and time
{
    
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    
    inline string as_string() const
    {
        return to_string(year) + "-" + to_string(month) + "-" + to_string(day) + "t" +
            to_string(hour) + "-" + to_string(minute);
    }
    
};

struct Account // USER or an ADMIN
{
    
    string login {}; // uniq identifier
    AccountType type {};
    string password {};
    
    inline bool operator== (const Account &acc) const
    {
        return login == acc.login;
    }
    
    inline bool operator< (const Account &acc) const
    {
        return login < acc.login;
    }
    
    inline bool operator<= (const Account &acc) const
    {
        return login <= acc.login;
    }
    
    inline string as_string() const
    {
        return string("[login=") + login + ", type=" +
            (type == AccountType::USER ? "USER" :
             (type == AccountType::ADMIN ? "ADMIN" : "")) +
            ", password=" + password + "]";
    }
    
};

struct BusRoute // bus route structure according to the task
{
    
    int route_number = 0;       // uniq identifier
    BusType type {};
    string destination {};
    DateTime departure {};
    DateTime arrival {};
    int ticket_cost_BYN = 0;    // in Belarusian rubles
    int n_tickets = 0;
    int tickets_left = 0;
    
    inline bool operator== (const BusRoute &acc) const
    {
        return route_number == acc.route_number;
    }
    
    inline bool operator< (const BusRoute &acc) const
    {
        return route_number < acc.route_number;
    }
    
    inline bool operator<= (const BusRoute &acc) const
    {
        return route_number <= acc.route_number;
    }
    
    inline string as_string() const
    {
        return "[route_number=" + to_string(route_number) + ", type=" +
                (type == BusType::SMALL ? "SMALL" :
                (type == BusType::MEDIUM ? "MEDIUM" :
                (type == BusType::LARGE ? "LARGE" : ""))) +
                ", desination=" + destination + ", departure=" + departure.as_string() +
                ", arrival=" + arrival.as_string() +
                ", ticket_cost_BYN=" + to_string(ticket_cost_BYN) +
                ", n_tickets=" + to_string(n_tickets) +
                ", tickets_left=" + to_string(tickets_left) + "]";
    }
    
};

//-FUNCTIONS----------------------------------------------------------------------------------------

/**
 *  Step#1 of the program to read or generate
 *  the accounts and the routes.
 *  @return false if an I/O error occurs, otherwise true
 */
bool preparation();

/**
 *  Step#2 of the program to define the current_account};
 *  provides registering or authorizing of an account.
 *  @param  quit    an indicator to stop the program
 *  @return false if an I/O error occurs, otherwise true
 */
bool account_enter(bool &quit);

/**
 *  Step#3 of the program to perform account acctions
 *  by a loop until the quit indicator is not true;
 *  USER-AND-ADMIN-ACTOINS: view, search, sort;
 *  ADMIN-ONLY-ACTIONS: add, edit, remove.
 *  @return false if an I/O error occurs, otherwise true
 */
bool account_actions();

#endif /* Step0BusStation_h */
