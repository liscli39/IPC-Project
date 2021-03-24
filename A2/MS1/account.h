// ===================================================================================
//  Assignment: 1 
//  Milestone : 2
// ===================================================================================
//  Student Name  : Vy Le
//  Student ID    : 126487206
//  Student Email : tpvle@myseneca.ca
//  Course Section: NHH
// ===================================================================================
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

// ----------------------------------------------------------------------------
// structures
struct Demographic {
	int birthYear;
  double household;
  char country[31];
};

struct UserLogin {
	char displayName[31];
  char username[11];
  char password[9];
};

struct Account {
	int accountNumber;
  char accountType;
  struct UserLogin login;
  struct Demographic demographic;
};

// ----------------------------------------------------------------------------
// function prototypes

// ---------------------------------------------------------
// Account Data: get user input
// ---------------------------------------------------------
void getAccount(struct Account* account);

// ---------------------------------------------------------
// UserLogin Data: get user input
// ---------------------------------------------------------
void getUserLogin(struct UserLogin*login);

// ---------------------------------------------------------
// Demographic Data: get user input
// ---------------------------------------------------------
void getDemographic(struct Demographic* demographic);

#endif
