//  describes the basic logic of the programm
#ifndef BusStation_h
#define BusStation_h

#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <string.h>

using std::string;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::endl;
using std::to_string;
using std::set;
using std::iterator;
using std::pair;

//-Constants----------------------------------------------------------------------------------------

const char DELIMITER = ';';
const int MAX_INPUT_SIZE = (1 << 14) + ((1 << 14) - 1);
const int MAX_N_ACCOUNTS = 128; // max number of accounts; 128 = 0x80
const int MAX_N_ROUTES = 128; // max number of routes
const string FILE_OF_ACCOUNTS = "accounts.csv";
const string FILE_OF_ROUTES = "bus_routes.csv";

//-ENUMS--------------------------------------------------------------------------------------------

enum StructureType { ACCOUNTS, BUS_ROUTES };
enum AccountType { USER, ADMIN };
enum BusType { SMALL, MEDIUM, LARGE };

//-STRUCTURES---------------------------------------------------------------------------------------

/** A simple structure of date and time. */
struct DateTime
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    inline string as_string() const
    {
        return to_string(year) + "-" + to_string(month) + "-" + to_string(day) + "t" +
            to_string(hour) + "-" + to_string(minute);
    }
};

/** An account for a USER or an ADMIN. */
struct Account
{
    string login; // identifier
    AccountType type;
    string password;
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

/** A bus route structure according to the task. */
struct BusRoute {
    int route_number; // identifier
    BusType type;
    string destination;
    DateTime departure;
    DateTime arrival;
    int ticket_cost_BYN; // Belarusian rubles
    int n_tickets;
    int tickets_left;
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

void preparation();
void account_enter(); // menu
void account_actions();

#endif /* BusStation_h */
