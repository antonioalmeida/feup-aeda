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
	bool leapYear = (year % 400) || (year % 100 != 0 && year % 4 == 0);
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

void clearScreen() {
	for (unsigned int i = 0; i < WINDOW_SIZE; i++)
		cout << endl;
}

void PressToContinue() {
	string trash;
	cout << "Press any key followed by ENTER to continue.";
	getline(cin, trash);
	cout << endl;
}

void deleteWhitespace(string &s){
    while (s.find("  ") != string::npos)
        s.erase(s.find("  "), 1);
    if (s[0] == ' ')
        s.erase(0, 1);
    if (s[s.length() - 1] == ' ')
        s.erase(s.length() -1, 1);
}

unsigned short int readOp(unsigned short int minValue, unsigned short int  maxValue){
    unsigned short int number;
    do{
        cin >> number;
        if(number < minValue || number > maxValue)
            cout << "ERROR: Out of range value, please insert a value between " << minValue << "-" << maxValue << ": ";
    }while(number < minValue || number > maxValue);
    
    return number;
}
