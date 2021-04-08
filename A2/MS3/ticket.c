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
#include "ticket.h"

void getTicket(struct Ticket* ticket) {
  printf("New Ticket (Ticket#:%06d)\n", ticket->ticketNumber);                  
  printf("----------------------------------------\n");
  printf("Enter the ticket SUBJECT (30 chars. maximum): ");
  getCString(ticket->subject, 1, 30);
  getTicketMessage(ticket->messages[0].message);
  printf("\n");
}

void getTicketMessage(char * message) {
  printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit: ");
  getCString(message, 1, 150);
  printf("\n");
}