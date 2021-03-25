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
#include <time.h>

// User-Defined Libraries
#include "commonHelpers.h"

int currentYear(void)
{
  time_t currentTime = time(NULL);
  return localtime(&currentTime) -> tm_year + 1900;
}

void clearStandardInputBuffer(void)
{
  while (getchar() != '\n')
  {
    ; // On purpose: do nothing
  }
}

int getInteger(void) {
  int number;
  char term;

	do {
		if (scanf("%d%c", &number, &term) != 2 || term != '\n') {
			printf("ERROR: Value must be an integer: ");
      clearStandardInputBuffer();
      term = '\0';
		}
	} while (term != '\n');

  return number;
}

int getPositiveInteger(void) {
  int number;
  
	do {
    number = getInteger();
		if (number <= 0) {
      printf("ERROR: Value must be a positive integer greater than zero: ");
		}
	} while (number <= 0);

  return number;
}

int getIntFromRange(int min, int max) {
  int number;
  
	do {
    number = getInteger();
		if (number < min || number > max) {
      printf("ERROR: Value must be between %d and %d inclusive: ", min, max);
		}
	} while (number < min || number > max);
  
  return number;
}

double getDouble(void) {
  double number;
  char term;

	do {
		if (scanf("%lf%c", &number, &term) != 2 || term != '\n') {
			printf("ERROR: Value must be a double floating-point number: ");
      clearStandardInputBuffer();
      term = '\0';
		}
	} while (term != '\n');

  return number;
}

double getPositiveDouble(void) {
  double number;
  
	do {
    number = getDouble();
		if (number <= 0) {
      printf("ERROR: Value must be a positive double floating-point number: ");
		}
	} while (number <= 0);

  return number;
}

char getCharOption(char* string) {
  char value, tmp;
  char* input = NULL;
  do {
    int id;
    char c = '\n';

    for (id = 0; c != '\0'; id++) {
      c = getchar();
      if (c == '\n') {
        c = '\0';
      }

      input = realloc(input, sizeof(char) * (id + 1));
      input[id] = c;
    }

    value = input[0];
    id = 0;
    do {
      tmp = string[id++];
    } while (tmp != '\0' && value != tmp);

    if (tmp == '\0' || input[1] != '\0') {
      printf("ERROR: Character must be one of [%s]: ", string);
    }

  } while (value != tmp || input[1] != '\0');
  
  return value;
}

void getCString(char *string, int min, int max)
{
  int id, flag;
  do {
    char input = '\n';
    flag = 0;

    for (id = 0; id <= max && input != '\0'; id++) {
      input = getchar();

      if (input == '\n') {
        input = '\0';
      }

      string[id] = input;
    }

    if (id - 1 < min) {
      if (min == max) {
        printf("ERROR: String length must be exactly %d chars: ", min);
      }
      else {
        printf("ERROR: String length must be between %d and %d chars:", min, max);
      }

      flag = 1;
    }

    if (id - 1 == max && string[max] != '\0') {
      if (min == max) {
        printf("ERROR: String length must be exactly %d chars: ", min);
      }
      else {
        printf("ERROR: String length must be no more than %d chars: ", max);
      }

      clearStandardInputBuffer();
      flag = 1;
    }

  } while (flag);
}
