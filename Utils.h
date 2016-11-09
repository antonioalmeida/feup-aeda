#pragma once

#include <iostream>
#include <string>

#define WINDOW_SIZE 24
#define TAB_BIG 24
#define TAB	5
//Header file for Utils, a file with useful functions to use throughout the program

unsigned int readInteger(unsigned int minValue, unsigned int maxValue); //Reads integer value in range [minValue, maxValue]

bool validDate(unsigned int day, unsigned int month, unsigned int year); //Checks if date is OK according to Gregorian Calendar (no need to test if day > 31 or month > 12)

void clearScreen();

void PressToContinue();