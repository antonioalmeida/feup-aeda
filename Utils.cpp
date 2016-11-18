#include "Utils.h"

//Source file for Utils, a file with useful functions to use throughout the program

using namespace std;

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

void pressToContinue() {
	string trash;
	cout << "Press any key followed by ENTER to continue.";
	if (cin.peek() != cin.eof()) //If there are no characters to be ignored, don't call it, otherwise might have to input ENTER 2 times
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, trash);
	cout << endl;
}

void deleteWhitespace(string &s) {
	while (s.find("  ") != string::npos)
		s.erase(s.find("  "), 1);
	if (s[0] == ' ')
		s.erase(0, 1);
	if (s[s.length() - 1] == ' ')
		s.erase(s.length() - 1, 1);
}

unsigned short int readOp(unsigned short int minValue, unsigned short int  maxValue) {
	unsigned short int number;
	do {
		cin >> number;
		if (number < minValue || number > maxValue)
			cout << "ERROR: Out of range value, please insert a value between " << minValue << "-" << maxValue << ": ";
	} while (number < minValue || number > maxValue);

	return number;
}

void unitsPrintHeader() {
    cout << "Abbreviation";
    cout << setw(51) << "Name";
    cout << setw(7) << "Year";
    cout << setw(7) << "ECTS";
    cout << setw(27) << "Scientific Area";
    cout << setw(12) << "Vacancies" << endl << endl;
}

void studentsPrintHeader() {
    cout << "Code";
    cout << setw(37) << "Name";
    cout << setw(9) << "Average";
    cout << setw(15) << "Units Taking" << endl << endl;
}

void teachersPrintHeader() {
    cout << setw(8) << "Code";
    cout << setw(50) << "Name";
    cout << "   Units Taught" << endl << endl;
}
