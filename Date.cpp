#include <sstream>
#include "Date.h"
#include "Exceptions.h"

using namespace std;

Date::Date(std::string date) {
	istringstream dateTemp;
	dateTemp.str(date);
	dateTemp >> day;
	dateTemp.ignore();
	dateTemp >> month;
	dateTemp.ignore();
	dateTemp >> year;
	/*To add: Exception handling (if day is bigger than 31, month bigger than 12 or date is not valid according to Gregorian calendar standars; exception classes need to be created*/
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	this->day = day;
	this->month = month;
	this->year = year;
	/*To add: Exception handling (if day is bigger than 31, month bigger than 12 or date is not valid according to Gregorian calendar standars; exception classes need to be created*/
}

unsigned int Date::getDay() const {
	return day;
}

unsigned int Date::getMonth() const {
	return month;
}

unsigned int Date::getYear() const {
	return year;
}

ostream& operator<<(ostream& out, const Date &date) {
	out << date.getDay() << "/" << date.getMonth() << "/" << date.getYear();
	return out;
}

bool operator<(const Date &date1, const Date &date2) {
	return (date1.year < date2.year) || (date1.year == date2.year && date1.month < date2.month) || (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day);
}