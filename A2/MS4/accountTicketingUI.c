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

#define TICKET_LIST_NEW 1
#define TICKET_LIST_ACTIVE 2
#define TICKET_LIST_CLOSED 0

// System Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void applicationStartup(struct AccountTicketingData* data) {
  int index, arrSize;
  struct Account* accounts = data->accounts;
  arrSize = data->ACCOUNT_MAX_SIZE;
  
  do {
    index = menuLogin(accounts, arrSize);
    
    if (index != -1) {
      if (accounts[index].accountType == 'C') {
        menuCustomer(data, accounts[index]);
      } else {
        menuAgent(data, &accounts[index]);
      }
    }

  } while (index != -1);

  printf("==============================================\n");
  printf("Account Ticketing System - Terminated\n");
  printf("==============================================\n");
}

int menuLogin(const struct Account accounts[], int arrSize) {
  int index, choose, remaining, flag;
  char username[30], password[30];
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
      remaining = 3;
      flag = 0;

      do {
        printf("Enter your account#: ");
        index = findAccountIndexByAcctNum(getInteger(), accounts, arrSize, 0);
        printf("User Login    : ");
        getCString(username, 1, 30);
        printf("Password      : ");
        getCString(password, 1, 30);
        
        flag = index != -1 
          && strcmp(accounts[index].login.username, username) == 0 
          && strcmp(accounts[index].login.password, password) == 0;

        if (flag == 0) {
          printf("INVALID user login/password combination! [attempts remaining:%d]\n", -- remaining);
        }

        printf("\n");
      } while (remaining != 0 && flag == 0);

      if (flag == 0) {
        printf("ERROR:  Login failed!.\n\n");
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

void menuAgent(struct AccountTicketingData* data, const struct Account* account) {
  int index, choose, arrSize;
  
  struct Account* accounts = data->accounts;
  arrSize = data->ACCOUNT_MAX_SIZE;

  do {
    printf("AGENT: %s (%05d)\n", account->login.displayName, account->accountNumber);
    printf("==============================================\n");
    printf("Account Ticketing System - Agent Menu\n");
    printf("==============================================\n");
    printf(" 1) Add a new account\n");
    printf(" 2) Modify an existing account\n");
    printf(" 3) Remove an account\n");
    printf(" 4) List accounts: summary view\n");
    printf(" 5) List accounts: detailed view\n");
    printf("----------------------------------------------\n");
    printf(" 6) List new tickets\n");
    printf(" 7) List active tickets\n");
    printf(" 8) List closed tickets\n");
    printf(" 9) Manage a ticket\n");
    printf("10) Archive closed tickets\n");
    printf("----------------------------------------------\n");
    printf("0) Logout\n\n");
    printf("Selection: ");

    choose = getIntFromRange(0, 9);
    printf("\n");
    
    switch (choose) {
      case 1: {
        index = findAccountIndexByAcctNum(0, accounts, arrSize, 0);

        if (index == -1) {
          printf("ERROR: Account listing is FULL, call ITS Support!\n\n");
        } else {
          accounts[index].accountNumber = autoGenAcctNum(accounts, arrSize);
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
              removeTicketsByAcctNum(account->accountNumber, data->tickets, data->TICKET_MAX_SIZE);
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

      case 6: {
        displayTicketList(data->tickets, data->TICKET_MAX_SIZE, TICKET_LIST_NEW);
        break;
      }

      case 7: {
        displayTicketList(data->tickets, data->TICKET_MAX_SIZE, TICKET_LIST_ACTIVE);
        break;
      }

      case 8: {
        displayTicketList(data->tickets, data->TICKET_MAX_SIZE, TICKET_LIST_CLOSED);
        break;
      }

      case 9: {
        printf("Enter ticket number: ");
        index = findTicketIndexByTicketNum(getPositiveInteger(), data->tickets, data->TICKET_MAX_SIZE);        
        printf("\n");

        if (index == -1) {
          printf("ERROR: Ticket is not exist!\n\n");
          pauseExecution();
        } else {
          manageTicket(&data->tickets[index]);
        }
        
        break;
      }

      case 10: {
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
      getCString(login->displayName, 1, DISPLAY_NAME_SIZE - 1);
      printf("\n");

    } else if (choose == 2) {
      getPassword(login->password);
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
      getCString(demographic->country, 1, COUNTRY_SIZE - 1);
      printf("\n");
    }

  } while (choose != 0);
}

void menuCustomer(struct AccountTicketingData* data, const struct Account account) {
  int choose, index;

  do {
    printf("CUSTOMER: %s (%d)\n", account.login.displayName, account.accountNumber);
    printf("==============================================\n");
    printf("Customer Main Menu\n");
    printf("==============================================\n");
    printf("1) View your account detail\n");
    printf("2) Create a new ticket\n");
    printf("3) Modify an active ticket\n");
    printf("4) List my tickets\n");
    printf("----------------------------------------------\n");
    printf("0) Logout\n\n");
    printf("Selection: ");

    choose = getIntFromRange(0, 4);
    printf("\n");

    switch (choose) {
      case 1: {
        displayAccountDetailHeader();
        displayAccountDetailRecord(&account);
        printf("\n");
        pauseExecution();
        break;
      }

      case 2: {
        index = findTicketIndexByTicketNum(0, data->tickets, data->TICKET_MAX_SIZE);

        if (index == -1) {
          printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");
        } else {
          data->tickets[index].ticketNumber = autoGenTicketNum(data->tickets, data->TICKET_MAX_SIZE);
          data->tickets[index].accountNumber = account.accountNumber;
          data->tickets[index].messageCount = 1;
          data->tickets[index].status = 1;
          data->tickets[index].messages[0].accountType = account.accountType;
          strcpy(data->tickets[index].messages[0].displayName, account.login.displayName);
          getTicket(&data->tickets[index]);
          printf("*** New ticket created! ***\n\n");
        }

        pauseExecution();
        break;
      }

      case 3: {
        printf("Enter ticket number: ");
        index = findTicketIndexByTicketNum(getPositiveInteger(), data->tickets, data->TICKET_MAX_SIZE);        
        printf("\n");

        if (index == -1) {
          printf("ERROR: Ticket is not exist!\n\n");
          pauseExecution();
        } else if (data->tickets[index].accountNumber != account.accountNumber) {
          printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
          pauseExecution();
        } else {
          updateTicket(&data->tickets[index]);
        }

        break;
      }

      case 4: {
        displayAccountTicketList(account, data->tickets, data->TICKET_MAX_SIZE);
        break;
      }

      case 0: {
        printf("### LOGGED OUT ###\n\n");
        break;
      }

      default:
        break;
    }
  } while (choose != 0);
}

int autoGenAcctNum(const struct Account accounts[], int arrSize) {
  int id, max;
  max = 1;
  for (id = 0; id < arrSize; id++) {
    if (accounts[id].accountNumber > max) {
      max = accounts[id].accountNumber;
    }
  }

  return max + 1;
}

int findTicketIndexByTicketNum(int ticketNumber, const struct Ticket tickets[], int arrSize) {
  int index, id;

  index = -1;
  for (id = 0; id < arrSize; id++) {
    if (tickets[id].ticketNumber == ticketNumber) {
      index = id;
      break;
    }
  }

  return index;
}

void displayTicketDetail(const struct Ticket ticket) {
  printf("================================================================================\n");
  printf("%06d (%s) Re: %s\n", ticket.ticketNumber, ticket.status ? "ACTIVE" : "CLOSED", ticket.subject);
  printf("================================================================================\n");

  int id, count = 5;
  for (id = 0; id < ticket.messageCount; id++) {
    printf("%s (%s):\n", ticket.messages[id].accountType == 'A' ? "AGENT" : "CUSTOMER", ticket.messages[id].displayName);
    printf("   %s\n\n", ticket.messages[id].message);

    if (--count == 0) {
      pauseExecution();
      count = 5;
    }
  }
}

void displayAccountTicketList(const struct Account account, const struct Ticket tickets[], int arrSize) {
  int index, number;

  do {
    printf("------ ------ ------------------------------ --------\n");
    printf("Ticket Status Subject                        Messages\n");
    printf("------ ------ ------------------------------ --------\n");
    
    int id;
    for (id = 0; id < arrSize; id ++) {
      if (tickets[id].ticketNumber != 0 && tickets[id].accountNumber == account.accountNumber) {
        printf(
          "%06d %-6s %-30s     %d\n", 
          tickets[id].ticketNumber, 
          tickets[id].status ? "ACTIVE" : "CLOSED",
          tickets[id].subject,
          tickets[id].messageCount
        );
      }
    }

    printf("------ ------ ------------------------------ --------\n\n");
    printf("Enter the ticket number to view the messages or\n");
    printf("0 to return to previous menu: ");
    
    do {
      number = getInteger();
      if (number < 0) {
        printf("ERROR: Value must be positive or zero: ");
      }
    } while (number < 0);
    printf("\n");

    if (number != 0) {
      index = findTicketIndexByTicketNum(number, tickets, arrSize);

      if (index == -1) {
        printf("ERROR: Invalid ticket number.\n\n");
      } else {
        displayTicketDetail(tickets[index]);
      }

      pauseExecution();
    }
  } while (number != 0);
}

void displayTicketList(const struct Ticket tickets[], int arrSize, int type) {
  int index, id, condition, number;

  do {
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
    printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
    
    for (id = 0; id < arrSize; id ++) {
      condition = tickets[id].ticketNumber != 0;

      if (type == TICKET_LIST_CLOSED) {
        condition = condition && tickets[id].status == 0;
      } else if (type == TICKET_LIST_ACTIVE) {
        condition = condition && tickets[id].status == 1;
      } else if (type == TICKET_LIST_CLOSED) {
        condition = condition && tickets[id].messageCount == 1 && tickets[id].status == 1;
      }
 
      if (condition) {
        printf( 
          "%06d %05d %-15s %-6s %-30s     %d\n", 
          tickets[id].ticketNumber, 
          tickets[id].accountNumber,
          tickets[id].messages[0].displayName,
          tickets[id].status ? "ACTIVE" : "CLOSED",
          tickets[id].subject,
          tickets[id].messageCount
        );
      }
    }

    printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
    printf("Enter the ticket number to view the messages or\n");
    printf("0 to return to previous menu: ");

    do {
      number = getInteger();
      if (number < 0) {
        printf("ERROR: Value must be positive or zero: ");
      }
    } while (number < 0);
    printf("\n");

    if (number != 0) {
      index = findTicketIndexByTicketNum(number, tickets, arrSize);

      if (index == -1) {
        printf("ERROR: Invalid ticket number.\n\n");
      } else {
        displayTicketDetail(tickets[index]);
      }

      pauseExecution();
    }
  } while (number != 0);
}

int autoGenTicketNum(const struct Ticket tickets[], int arrSize) {
  int id, max;
  max = 1;
  for (id = 0; id < arrSize; id++) {
    if (tickets[id].ticketNumber > max) {
      max = tickets[id].ticketNumber;
    }
  }

  return max + 1;
}

void removeTicketsByAcctNum(int accountNumber, struct Ticket tickets[], int arrSize) {
  int id, max;
  struct Ticket empty = { 0 }; 

  for (id = 0; id < arrSize; id++) {
    if (tickets[id].accountNumber == accountNumber && tickets[id].status == 1) {
      tickets[id] = empty;
    }
  }
}

void updateTicket(struct Ticket* ticket) {
  int choose;
  do {
    printf("----------------------------------------\n");
    printf("Ticket: %06d - Update Options\n", ticket->ticketNumber);
    printf("----------------------------------------\n");
    printf("Status  : %-6s\n", ticket->status ? "ACTIVE" : "CLOSED");
    printf("Subject : %-30s\n", ticket->subject);
    printf("----------------------------------------\n");
    printf("1) Modify the subject\n");
    printf("2) Add a message\n");
    printf("3) Close ticket\n");
    printf("0) Done\n");
    printf("Selection: ");
    
    choose = getIntFromRange(0, 3);
    printf("\n");

    if (choose == 1) {
      printf("Enter the revised ticket SUBJECT (30 chars. maximum): ");
      getCString(ticket->subject, 1, SUBJECT_SIZE - 1);
      
    } else if (choose == 2) {
      if (ticket->status == 0) {
        printf("ERROR: Ticket is closed - new messages are not permitted.\n");
      } else if (ticket->messageCount == TICKET_MESSAGE_SIZE) {
        printf("ERROR: Message limit has been reached, call ITS Support!\n");
      } else {
        getTicketMessage(ticket->messages[ticket->messageCount].message);
        ticket->messageCount ++;
      }
    } else if (choose == 3) {
      if (ticket->status == 0) {
        printf("ERROR: Ticket is already closed!\n\n");
      } else {
        printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");

        char select = getCharOption("YN");
        printf("\n");
        if (select == 'Y') {
          ticket->status = 0;

          printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
          select = getCharOption("YN");

          if (select == 'Y') {
            getTicketMessage(ticket->messages[ticket->messageCount].message);
            ticket->messageCount ++;
            choose = 0;
          }
        }
      }
    }

    printf("\n");
  } while (choose != 0);
}

void manageTicket(struct Ticket* ticket) {
  int choose;
  do {
    printf("----------------------------------------\n");
    printf("Ticket: %06d - Update Options\n", ticket->ticketNumber);
    printf("----------------------------------------\n");
    printf("Status  : %-6s\n", ticket->status ? "ACTIVE" : "CLOSED");
    printf("Subject : %-30s\n", ticket->subject);
    printf("Acct#   : %05d\n", ticket->accountNumber);
    printf("Customer: %-30s\n", ticket->messages[0].displayName);
    printf("----------------------------------------\n");
    printf("1) Add a message\n");
    printf("2) Close ticket\n");
    printf("3) Re-open ticket\n");
    printf("0) Done\n");
    printf("Selection: ");
    
    choose = getIntFromRange(0, 3);
    printf("\n");

    if (choose == 1) {
      if (ticket->status == 0) {
        printf("ERROR: Ticket is closed - new messages are not permitted.\n\n");
      } else if (ticket->messageCount == TICKET_MESSAGE_SIZE) {
        printf("ERROR: Message limit has been reached, call ITS Support!\n\n");
      } else {
        getTicketMessage(ticket->messages[ticket->messageCount].message);
        ticket->messageCount ++;
      }
    } else if (choose == 2) {
      if (ticket->status == 0) {
        printf("ERROR: Ticket is already closed!\n\n");
      } else {
        printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");

        char select = getCharOption("YN");
        printf("\n");
        if (select == 'Y') {
          ticket->status = 0;

          printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
          select = getCharOption("YN");

          if (select == 'Y') {
            getTicketMessage(ticket->messages[ticket->messageCount].message);
            ticket->messageCount ++;
            choose = 0;
          }
        }
      }
    } else if (choose == 3) {
      if (ticket->status == 1) {
        printf("ERROR: Ticket is already active!\n\n");
      } else {
        printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
        
        char select = getCharOption("YN");
        printf("\n");

        if (select == 'Y') {
          ticket->status = 1;
          printf("*** Ticket re-opened! ***\n\n");
        }        
      }
    }
  } while (choose != 0);
}

int loadAccounts(struct Account accounts[], int arrSize) {
  int id, count;
  FILE *fp;

  fp = fopen("accounts.txt", "r");
  count = 0;
  for (id = 0; id < arrSize; id ++) {
    fscanf(fp, "%d~%c~", 
      &accounts[id].accountNumber,
      &accounts[id].accountType
    );
    getFileCString(fp, accounts[id].login.displayName, DISPLAY_NAME_SIZE, '~');
    getFileCString(fp, accounts[id].login.username, USERNAME_SIZE, '~');
    getFileCString(fp, accounts[id].login.password, PASSWORD_SIZE, '~');
    fscanf(fp, "%d~",&accounts[id].demographic.birthYear); 
    fscanf(fp, "%lf~",&accounts[id].demographic.household);
    getFileCString(fp, accounts[id].demographic.country, COUNTRY_SIZE, '~');

    if (accounts[id].accountNumber != 0) {
      count ++;
    }
  }

  return count;
}

int loadTickets(struct Ticket tickets[], int arrSize) {
  int id, count, messageId, messageCount;
  char type;
  FILE *fp;

  fp = fopen("tickets.txt", "r");
  count = 0;
  for (id = 0; id < arrSize; id ++) {
    fscanf(fp, "%d|%d|%d|", 
      &tickets[id].ticketNumber,
      &tickets[id].accountNumber,
      &tickets[id].status
    );
    getFileCString(fp, tickets[id].subject, SUBJECT_SIZE, '|');
    fscanf(fp, "%d|", &messageCount);
    
    tickets[id].messageCount = messageCount > TICKET_MESSAGE_SIZE ? TICKET_MESSAGE_SIZE : messageCount;

    for (messageId = 0; messageId < tickets[id].messageCount; messageId ++) {
      fscanf(fp, "%c|", &tickets[id].messages[messageId].accountType);
      getFileCString(fp, tickets[id].messages[messageId].displayName, DISPLAY_NAME_SIZE, '|');
      getFileCString(fp, tickets[id].messages[messageId].message, MESSAGE_SIZE, '|');
    }

    if (tickets[id].ticketNumber != 0) {
      count ++;
    }

  }

  return count;
}