#include "Utils.h"

//Source file for Utils, a file with useful functions to use throughout the program

using namespace std;

unsigned int readInteger(unsigned int minValue, unsigned int maxValue) {
	int number;
	do {
		cin >> number;
		if (number < minValue || number > maxValue)
			cout << "ERROR: Out of range value, please insert a value between " << minValue << "-" << maxValue << ":";
	} while (number < minValue || number > maxValue);

	return number;
}

bool validDate(unsigned int day, unsigned int month, unsigned int year) {
	bool leapYear = (year % 400) || (year % 100 == 0 && year % 4 != 0);
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return true;
	case 4:
	case 6:
	case 9:
	case 11:
		return day != 31;
	case 2:
		if (leapYear)
			return day < 29;
		else
			return day < 28;
	}
}