#include "Date.h"
#include "Exceptions.h"

using namespace std;

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	this->day = day;
	this->month = month;
	this->year = year;
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

string Date::getDate() const {
	ostringstream oss;
	string date;
	oss << day << "/" << month << "/" << year;
	date = oss.str();

	return date;
}

void Date::setDay(unsigned int newDay) {
	day = newDay;
}

void Date::setMonth(unsigned int newMonth) {
	month = newMonth;
}

void Date::setYear(unsigned int newYear) {
	year = newYear;
}

istream& operator >>(istream &in, Date &date) {
	in >> date.day;
	return in;
}
ostream& operator<<(ostream& out, const Date &date) {
	out << date.day << '/' << date.month << '/' << date.year;
	return out;
}

bool operator<(const Date &date1, const Date &date2) {
	return (date1.year < date2.year) || (date1.year == date2.year && date1.month < date2.month) || (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day);
}

bool operator==(const Date &dat1, const Date &dat2) {
	return (dat1.getYear() == dat2.getYear() && dat1.getMonth() == dat2.getMonth() && dat1.getDay() == dat2.getDay());
}




