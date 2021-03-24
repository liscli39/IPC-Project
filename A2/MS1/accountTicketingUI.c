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
#include <stdlib.h>
#include <string.h>
#include "account.h"

// User-Defined Libraries
#include "accountTicketingUI.h"
#include "commonHelpers.h"


void displayAccountSummaryHeader(void) {
  printf("Acct# Acct.Type Birth\n");
  printf("----- --------- -----\n");
}

void displayAccountDetailHeader(void) {
  printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
  printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account* account) {
  printf(
    "%05d %-9s %5d\n", 
    account->accountNumber,
    account->accountType == 'A' ? "AGENT" : "CUSTOMER",
    account->demographic.birthYear
  );
}

void displayAccountDetailRecord(const struct Account* account) {
  // Hide password
  int id, length;
  length = strlen(account->login.password)  + 1;
  char* password = malloc(length);

  for (id = 0; id < length; id ++) {
    if (id % 2 == 0) {
      password[id] = account->login.password[id];
    } else {
      password[id] = '*';
    }
  }

  printf(
    "%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", 
    account->accountNumber,
    account->accountType == 'A' ? "AGENT" : "CUSTOMER",
    account->demographic.birthYear,
    account->demographic.household,
    account->demographic.country,
    account->login.displayName,
    account->login.username,
    password
  );
}

void applicationStartup(struct Account accounts[], int arrSize) {
  int index;

  do {
    index = menuLogin(accounts, arrSize);
    
    if (index != -1) {
      if (accounts[index].accountType == 'C') {
        printf("CUSTOMER: home menu currently unavailable...\n\n");
        pauseExecution();

      } else {
        menuAgent(accounts, arrSize, &accounts[index]);
      }
    }

  } while (index != -1);

  printf("==============================================\n");
  printf("Account Ticketing System - Terminated\n");
  printf("==============================================\n");
}

int menuLogin(const struct Account accounts[], int arrSize) {
  int index, choose;

  do {
    printf("==============================================\n");
    printf("Account Ticketing System - Login\n");
    printf("==============================================\n");
    printf("1) Login to the system\n");
    printf("0) Exit application\n");
    printf("----------------------------------------------\n\n");
    printf("Selection: ");

    choose = getIntFromRange(0, 1);
    printf("\n");

    if (choose == 1) {
      printf("Enter your account#: ");
      index = findAccountIndexByAcctNum(getInteger(), accounts, arrSize, 0);
      printf("\n");

      if (index == -1) {
        printf("ERROR:  Access Denied.\n\n");
        pauseExecution();
      } else {
        choose = 0;
      }

    } else if (choose == 0) {
      printf("Are you sure you want to exit? ([Y]es|[N]o): ");

      char select = getCharOption("yYnN");
      printf("\n");
      
      if (select == 'N' || select == 'n') {
        choose = 1;
      } else {
        index = -1;
      }
    }
  
  } while (choose != 0);

  return index;
}

void menuAgent(struct Account accounts[], int arrSize, const struct Account* account) {
  int index, choose;

  do {
    printf("AGENT: %s (%05d)\n", account->login.displayName, account->accountNumber);
    printf("==============================================\n");
    printf("Account Ticketing System - Agent Menu\n");
    printf("==============================================\n");
    printf("1) Add a new account\n");
    printf("2) Modify an existing account\n");
    printf("3) Remove an account\n");
    printf("4) List accounts: summary view\n");
    printf("5) List accounts: detailed view\n");
    printf("----------------------------------------------\n");
    printf("0) Logout\n\n");
    printf("Selection: ");

    choose = getIntFromRange(0, 5);
    printf("\n");
    
    switch (choose) {
      case 1: {
        index = findAccountIndexByAcctNum(0, accounts, arrSize, 0);
        
        if (index == -1) {
          printf("ERROR: Account listing is FULL, call ITS Support!\n\n");
        } else {
          getAccount(&accounts[index]);
          getUserLogin(&accounts[index].login);
          getDemographic(&accounts[index].demographic);
          printf("*** New account added! ***\n\n");
        }

        pauseExecution();
        break;
      }
      
      case 2: {
        index = findAccountIndexByAcctNum(0, accounts, arrSize, 1);
        printf("\n");

        if (index == -1) {
          printf("ERROR: Account is not exist!");
        } else {
          updateAccount(&accounts[index]);
        }

        break;
      }

      case 3: {
        index = findAccountIndexByAcctNum(0, accounts, arrSize, 1);

        if (index == -1) {
          printf("ERROR: Account is not exist!\n\n");
          
        } else {
          if (accounts[index].accountNumber == account->accountNumber){
            printf("\n");
            printf("ERROR: You can't remove your own account!\n\n");

          } else {
            displayAccountDetailHeader();
            displayAccountDetailRecord(&accounts[index]);
            printf("\n");
            printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");

            char select = getCharOption("YN");
            printf("\n");

            if (select == 'Y') {
              struct Account empty = { 0 }; 
              accounts[index] = empty;
              printf("*** Account Removed! ***\n\n");
            } else {
              printf("*** No changes made! ***\n\n");
            }
          }
        }

        pauseExecution();
        break;
      }

      case 4: {
        displayAllAccountSummaryRecords(accounts, arrSize);
        pauseExecution();        
        break;
      }

      case 5: {
        displayAllAccountDetailRecords(accounts, arrSize);
        pauseExecution();
        break;
      }

      case 0: {
        printf("### LOGGED OUT ###\n\n");
      }

      default:
        break;
    }

  } while (choose != 0);
}

int findAccountIndexByAcctNum(int accountNumber, const struct Account accounts[], int arrSize, int fromInput) {
  int index, number, id;

  if (fromInput != 0) {
    printf("Enter the account#: ");
    number = getInteger();
  
  } else {
    number = accountNumber;
  }

  index = -1;
  for (id = 0; id < arrSize; id++) {
    if (accounts[id].accountNumber == number) {
      index = id;
      break;
    }
  }

  return index;
}

void displayAllAccountSummaryRecords(const struct Account accounts[], int arrSize) {
  displayAccountSummaryHeader();
  int id;
  for (id = 0; id < arrSize; id++) {
    if (accounts[id].accountNumber != 0) {
      displayAccountSummaryRecord(&accounts[id]);
    }
  }

  printf("\n");
}

void displayAllAccountDetailRecords(const struct Account accounts[], int arrSize) {
  displayAccountDetailHeader();

  int id;
  for (id = 0; id < arrSize; id++) {
    if (accounts[id].accountNumber != 0) {
      displayAccountDetailRecord(&accounts[id]);
    }
  }

  printf("\n");
}

void pauseExecution(void) {
  printf("<< ENTER key to Continue... >>");
  clearStandardInputBuffer();
  putchar('\n');
}

void updateAccount(struct Account* account) {
  int choose;
  do {
    printf("Account: %05d - Update Options\n", account->accountNumber);
    printf("----------------------------------------\n");
    printf("1) Update account type (current value: %c)\n", account->accountType);
    printf("2) Login\n");
    printf("3) Demographics\n");
    printf("0) Done\n");
    printf("Selection: ");
    
    choose = getIntFromRange(0, 3);
    printf("\n");

    if (choose == 1) {
      printf("Enter the account type (A=Agent | C=Customer): ");
      account->accountType = getCharOption("AC");
      printf("\n");
      
    } else if (choose == 2) {
      updateUserLogin(&account->login);

    } else if (choose == 3) {
      updateDemographic(&account->demographic);
    }

  } while (choose != 0);
}

void updateUserLogin(struct UserLogin* login) {
  int choose;
  do {
    printf("User Login: %s - Update Options\n", login->username);
    printf("----------------------------------------\n");
    printf("1) Display name (current value: %s)\n", login->displayName);
    printf("2) Password\n");
    printf("0) Done\n");
    printf("Selection: ");

    choose = getIntFromRange(0, 2);
    printf("\n");

    if (choose == 1) {
      printf("Enter the display name (30 chars max): ");
      getCString(login->displayName, 1, 30);
      printf("\n");

    } else if (choose == 2) {
      printf("Enter the password (must be 8 chars in length): ");
      getCString(login->password, 8, 8);
      printf("\n");
    }

  } while (choose != 0);
}

void updateDemographic(struct Demographic* demographic) {
  int choose;
  do {
    printf("Demographic Update Options\n");
    printf("----------------------------------------\n");
    printf("1) Household Income (current value: $%.2lf)\n", demographic->household);
    printf("2) Country (current value: %s)\n", demographic->country);
    printf("0) Done\n");
    printf("Selection: ");

    choose = getIntFromRange(0, 2);
    printf("\n");

    if (choose == 1) {
      printf("Enter the household Income: $");
      demographic->household = getPositiveDouble();
      printf("\n");

    } else if (choose == 2) {
      printf("Enter the country (30 chars max.): ");
      getCString(demographic->country, 1, 30);
      printf("\n");
    }

  } while (choose != 0);
}
