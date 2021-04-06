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

#include "account.h"
#include "ticket.h"

struct AccountTicketingData {
  struct Account* accounts;
  const int ACCOUNT_MAX_SIZE; 
  struct Ticket* tickets;
  const int TICKET_MAX_SIZE;
};

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
void applicationStartup(struct AccountTicketingData* data);

// ---------------------------------------------------------
// Menu Login: will return the index number of the account array for the user that is logged in
// ---------------------------------------------------------
int menuLogin(const struct Account accounts[], int arrSize);

// ---------------------------------------------------------
// Menu Agent: This is the main menu for an agent who has authorization to manage the accounts for the system.
// ---------------------------------------------------------
void menuAgent(struct AccountTicketingData* data, const struct Account* account);

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

// ---------------------------------------------------------
// Menu Custormer: This is the main menu for a customer login.
// ---------------------------------------------------------
void menuCustomer(struct AccountTicketingData* data, const struct Account account);

// ---------------------------------------------------------
// Auto generate account number
// ---------------------------------------------------------
int autoGenAcctNum(const struct Account accounts[], int arrSize);

// ---------------------------------------------------------
// Find ticket index by ticket number
// ---------------------------------------------------------
int findTicketIndexByTicketNum(int ticketNumber, const struct Ticket tickets[], int arrSize);

// ---------------------------------------------------------
// Display ticket detail
// ---------------------------------------------------------
void displayTicketDetail(const struct Ticket ticket);

// ---------------------------------------------------------
// Display account list ticket
// ---------------------------------------------------------
void displayAccountTicketList(const struct Account account, const struct Ticket tickets[], int arrSize);

// ---------------------------------------------------------
// Display list active ticket
// ---------------------------------------------------------
void displayTicketList(const struct Ticket tickets[], int arrSize, int new);

// ---------------------------------------------------------
// Auto generate ticket number
// ---------------------------------------------------------
int autoGenTicketNum(const struct Ticket tickets[], int arrSize);

// ---------------------------------------------------------
// Remove tickets by account number
// ---------------------------------------------------------
void removeTicketsByAcctNum(int accountNumber, struct Ticket tickets[], int arrSize);

// ---------------------------------------------------------
// Ticket Data: update from user input
// ---------------------------------------------------------
void updateTicket(struct Ticket* ticket);

// ---------------------------------------------------------
// Manage a ticket
// ---------------------------------------------------------
void manageTicket(struct Ticket* ticket);

#endif
