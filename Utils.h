#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <climits>

#define WINDOW_SIZE 24
#define TAB_BIG "                        "
#define TAB	"     "

/*! \file utils.h
 \brief Useful functions to use throughout the program.

 */


//! Ensures user's input is a number between two numbers given by arguments
/*!
\param minValue unsigned short int corresponding to the minimum value accepted
\param maxValue unsigned short int corresponding to the maximum value accepted
\return unsigned short int corresponding to the (valid) value read
*/
unsigned short int readOp(unsigned short int minValue, unsigned short int  maxValue);

//! Checks if date is valid
/*!
\param day unsigned int corresponding to the day of the date being tested
\param month unsigned int corresponding to the month of the date being tested
\param year unsigned int corresponding to the year of the date being tested
\return true if date is OK according to Gregorian calendar standard, false otherwise
*/
bool validDate(unsigned int day, unsigned int month, unsigned int year);

//! Prints a number of new line characters defined by macro WINDOW_SIZE to simulate system("cls")
/*!
*/
void clearScreen();

//! Deletes all whitespaces in beggining and end of a string and turns all consecutive whitespaces in the middle into a single whitespace
/*!
\param s string to be adjusted
*/
void deleteWhitespace(std::string &s);

//! Waits for user input (a random key, followed by ENTER), then clears screen using clearScreen(). Simulates system("pause")
/*!
*/
void pressToContinue();

//! Prints table header used when doing different types of units listings
/*!
*/
void unitsPrintHeader();

//! Prints table header used when doing different types of students listings
/*!
*/
void studentsPrintHeader();

//! Prints table header used when doing different types of teachers listings
/*!
*/
void teachersPrintHeader();

//! Prints table header used when listing the top 3 studentsClasses in the respective priority queue
/*!
*/
void classesPrintHeader();
