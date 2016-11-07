#include "Utils.h"

//Source file for Utils, a file with useful functions to use throughout the program that really don't fit on any other file (may be deleted if not necessary; to be implemented)

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