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

// ----------------------------------------------------------------------------
// structures
struct Message {
  char accountType;
  char displayName[31];
  char message[151];
};

struct Ticket {
  int ticketNumber;
  int accountNumber;
  int status;
  char subject[31];
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
