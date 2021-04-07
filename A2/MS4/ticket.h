// ===================================================================================
//  Assignment: 1 
//  Milestone : 2
// ===================================================================================
//  Student Name  : 
//  Student ID    : 
//  Student Email :
//  Course Section: 
// ===================================================================================
#ifndef TICKET_H_
#define TICKET_H_

// -----------------------------------------------------------------------------------
// System Data Array sizes
// -----------------------------------------------------------------------------------
#define TICKET_MESSAGE_SIZE 20
#define DISPLAY_NAME_SIZE 31
#define MESSAGE_SIZE 151
#define SUBJECT_SIZE 31

// ----------------------------------------------------------------------------
// structures
struct Message {
  char accountType;
  char displayName[DISPLAY_NAME_SIZE];
  char message[MESSAGE_SIZE];
};

struct Ticket {
  int ticketNumber;
  int accountNumber;
  int status;
  char subject[SUBJECT_SIZE];
  int messageCount;
  struct Message messages[TICKET_MESSAGE_SIZE];
};

// ----------------------------------------------------------------------------
// function prototypes

// ---------------------------------------------------------
// Ticket Data: get user input
// ---------------------------------------------------------
void getTicket(struct Ticket* ticket);

// ---------------------------------------------------------
// Ticket Data: get message input
// ---------------------------------------------------------
void getTicketMessage(char * message);

#endif
