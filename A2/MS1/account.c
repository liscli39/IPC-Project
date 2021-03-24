// ===================================================================================
//  Assignment: 1 
//  Milestone : 2
// ===================================================================================
//  Student Name  : Vy Le
//  Student ID    : 126487206
//  Student Email : tpvle@myseneca.ca
//  Course Section: NHH
// ===================================================================================
#define _CRT_SECURE_NO_WARNINGS

// System Libraries
#include <stdio.h>

// User-Defined Libraries
#include "commonHelpers.h"
#include "account.h"

void getAccount(struct Account* account) {
  printf("Account Data: New Record\n");                  
  printf("----------------------------------------\n");

  printf("Enter the account number: ");
  account->accountNumber = getPositiveInteger();
  printf("\n");
  
  printf("Enter the account type (A=Agent | C=Customer): ");
  account->accountType = getCharOption("AC");
  printf("\n");
}

void getUserLogin(struct UserLogin* login) {
  printf("User Login Data Input\n");                
  printf("----------------------------------------\n");

  printf("Enter user login (10 chars max): ");
  getCString(login->username, 1, 10);

  printf("Enter the display name (30 chars max): ");
  getCString(login->displayName, 1, 30);

  printf("Enter the password (must be 8 chars in length): ");
  getCString(login->password, 8, 8);
  printf("\n");
}

void getDemographic(struct Demographic* demographic) {
  printf("Demographic Data Input\n");               
  printf("----------------------------------------\n");
  printf("Enter birth year (current age must be between 18 and 110): ");
  
  int year = currentYear();
  demographic->birthYear = getIntFromRange(year - 110, year - 18);
  
  printf("Enter the household Income: $");
  demographic->household = getPositiveDouble();

  printf("Enter the country (30 chars max.): ");
  getCString(demographic->country, 1, 30); 
  printf("\n");
}
