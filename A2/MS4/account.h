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

#define COUNTRY_SIZE 31
#define DISPLAY_NAME_SIZE 31
#define USERNAME_SIZE 11
#define PASSWORD_SIZE 9

// ----------------------------------------------------------------------------
// structures
struct Demographic {
	int birthYear;
  double household;
  char country[COUNTRY_SIZE];
};

struct UserLogin {
	char displayName[DISPLAY_NAME_SIZE];
  char username[USERNAME_SIZE];
  char password[PASSWORD_SIZE];
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

// ---------------------------------------------------------
// UserLogin Data: get username
// ---------------------------------------------------------
void getUsername(char* username);

// ---------------------------------------------------------
// UserLogin Data: get password
// ---------------------------------------------------------
void getPassword(char* password);

#endif
