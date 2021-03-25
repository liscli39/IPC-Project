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
  struct Message messages[20];
};

#endif
