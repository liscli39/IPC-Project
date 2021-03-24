// ===================================================================================
//  Assignment: 1 
//  Milestone : 2
// ===================================================================================
//  Student Name  : Vy Le
//  Student ID    : 126487206
//  Student Email : tpvle@myseneca.ca
//  Course Section: NHH
// ===================================================================================
#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

// ----------------------------------------------------------------------------
// function prototypes

// ---------------------------------------------------------
// Display formatted Account summary header
// ---------------------------------------------------------
void displayAccountSummaryHeader(void);

// ---------------------------------------------------------
// Display formatted Account details header
// ---------------------------------------------------------
void displayAccountDetailHeader(void);

// ---------------------------------------------------------
// Display formatted Account summary record
// ---------------------------------------------------------
void displayAccountSummaryRecord(const struct Account* account);

// ---------------------------------------------------------
// Display formatted Account details record
// ---------------------------------------------------------
void displayAccountDetailRecord(const struct Account* account);

// ---------------------------------------------------------
// Application Startup: the entry point to the application logic
// ---------------------------------------------------------
void applicationStartup(struct Account accounts[], int arrSize);

// ---------------------------------------------------------
// Menu Login: will return the index number of the account array for the user that is logged in
// ---------------------------------------------------------
int menuLogin(const struct Account accounts[], int arrSize);

// ---------------------------------------------------------
// Menu Agent: This is the main menu for an agent who has authorization to manage the accounts for the system.
// ---------------------------------------------------------
void menuAgent(struct Account accounts[], int arrSize, const struct Account* account);

// ---------------------------------------------------------
// Find account index by account number
// ---------------------------------------------------------
int findAccountIndexByAcctNum(int accountNumber, const struct Account accounts[], int arrSize, int bool);

// ---------------------------------------------------------
// Display all formatted Account summary record
// ---------------------------------------------------------
void displayAllAccountSummaryRecords(const struct Account accounts[], int arrSize);

// ---------------------------------------------------------
// Display all formatted Account details record
// ---------------------------------------------------------
void displayAllAccountDetailRecords(const struct Account accounts[], int arrSize);

// ---------------------------------------------------------
// Pause execution
// ---------------------------------------------------------
void pauseExecution(void);

// ---------------------------------------------------------
// Account Data: update from user input
// ---------------------------------------------------------
void updateAccount(struct Account* account);

// ---------------------------------------------------------
// UserLogin Data: update from user input
// ---------------------------------------------------------
void updateUserLogin(struct UserLogin*login);

// ---------------------------------------------------------
// Demographic Data: update from user input
// ---------------------------------------------------------
void updateDemographic(struct Demographic* demographic);

#endif