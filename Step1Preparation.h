// step#1: data I/O
#ifndef Step1Preparation_h
#define Step1Preparation_h

/** Fills the {@code accounts} by some number of generated instances. */
void generate_accounts();

/** Fills the {@code routes} by some number of generated instances. */
void generate_routes();

/**
 *  Writes the {@code accounts} to the {@code FILE_OF_ACCOUNTS}.
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool write_accounts();

/**
 *  Writes the {@code routes} to the {@code FILE_OF_ROUTES}.
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool write_routes();

/**
 *  Reads the {@code FILE_OF_ACCOUNTS} to fill the {@code accounts}
 *  until the first format mismatch.
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool read_accounts();

/**
 *  Reads the {@code FILE_OF_ROUTES} to fill the {@code routes}
 *  until the first format mismatch.
 *  @return {@code false} if an I/O error occurs, otherwise {@code true}
 */
bool read_routes();

#endif /* Step1Preparation_h */
