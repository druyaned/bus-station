// step#1: data I/O
#ifndef Step1Preparation_h
#define Step1Preparation_h

/** Fills the accounts by some number of generated instances. */
void generate_accounts();

/** Fills the routes by some number of generated instances. */
void generate_routes();

/**
 *  Writes the accounts to the FILE_OF_ACCOUNTS.
 *  @return false if an I/O error occurs, otherwise true
 */
bool write_accounts();

/**
 *  Writes the routes to the FILE_OF_ROUTES.
 *  @return false if an I/O error occurs, otherwise true
 */
bool write_routes();

/**
 *  Reads the FILE_OF_ACCOUNTS to fill the accounts
 *  until the first format mismatch.
 *  @return false if an I/O error occurs, otherwise true
 */
bool read_accounts();

/**
 *  Reads the FILE_OF_ROUTES to fill the routes
 *  until the first format mismatch.
 *  @return false if an I/O error occurs, otherwise true
 */
bool read_routes();

#endif /* Step1Preparation_h */
