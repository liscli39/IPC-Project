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
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// User-Defined Libraries
#include "commonHelpers.h"
#include "account.h"

void getAccount(struct Account* account) {
  printf("New Account Data (Account#:%05d)\n", account->accountNumber);                  
  printf("----------------------------------------\n");
  printf("Enter the account type (A=Agent | C=Customer): ");
  account->accountType = getCharOption("AC");
  printf("\n");
}

void getUserLogin(struct UserLogin* login) {
  printf("User Login Data Input\n");                
  printf("----------------------------------------\n");

  getUsername(login->username);

  printf("Enter the display name (30 chars max): ");
  getCString(login->displayName, 1, 30);

  getPassword(login->password);

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

  int id;
  char c;
  for (id = 0; demographic->country[id] != '\0'; ++id){
    c = demographic->country[id];
    if (c >= 'a' && c <= 'z') {
      demographic->country[id] = toupper(c);
    }
  }

  printf("\n");
}

void getUsername(char* username) {
  int id, space;
  do {
    printf("Enter user login (10 chars max): ");
    getCString(username, 1, 10);
    space = 0;

    for (id = 0; username[id] != '\0'; ++id){
      if (username[id] == ' ') {
        ++ space;
        break;
      }
    }
    
    if (space != 0) {
      printf("ERROR: The user login must NOT contain whitespace characters.\n");
    }
  } while (space != 0);
}

void getPassword(char *password) {
  int id, digit, upper, lower, symbol, flag;
  char c;
  
  do {
    printf("Enter the password (must be 8 chars in length): ");
    getCString(password, 8, 8);
    digit = upper = lower = symbol = flag = 0;

    for (id = 0; password[id] != '\0'; ++id){
      c = password[id];
      if (c >= '0' && c <= '9') {
        ++ digit; 
      } else if (c >= 'A' && c <= 'Z') {
        ++ upper; 
      } else if (c >= 'a' && c <= 'z') {
        ++ lower; 
      } else if (c == '!' || c == '@' || c == '#' 
      || c == '$' || c == '%' || c == '^' 
      || c == '^' || c == '&' || c == '*') {
        ++ symbol; 
      }
    }

    flag = digit == upper && lower == symbol && digit == lower; 
    if (flag == 0) {
      printf("SECURITY: Password must contain 2 of each:\n");
      printf("          Digit: 0-9\n");
      printf("          UPPERCASE character\n");
      printf("          lowercase character\n");
      printf("          symbol character: !@#$%%^&*\n");
    }

  } while (flag == 0);
}