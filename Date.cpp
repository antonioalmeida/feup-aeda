#include "Date.h"
#include "Exceptions.h"

using namespace std;

Date::Date()
{
	//gives me the actual date
	string add_zero_to_month = "0";
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	if (timeinfo.tm_mon + 1 < 10)
	{
		add_zero_to_month += to_string(timeinfo.tm_mon + 1);
	}
	else
	{
		add_zero_to_month = to_string(timeinfo.tm_mon + 1);;
	}

	this->day = timeinfo.tm_mday;
	this->month = stoi(add_zero_to_month);
	this->year = timeinfo.tm_year + 1900;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	this->day = day;
	this->month = month;
	this->year = year;
	/*To add: Exception handling (if day is bigger than 31, month bigger than 12 or date is not valid according to Gregorian calendar standars; exception classes need to be created*/
}

Date::Date(string DateStr) { // Date na forma DD/MM/AAA

	istringstream instr(DateStr);
	char del;
	instr >> day >> del >> month >> del >> year;
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

string Date::getDate() const
{
	ostringstream oss;
	string date;
	oss << day << "/" << month << "/" << year;
	date = oss.str();

	return date;
}

int Date::getCompDate() const
{
	return year * 10000 + month * 100 + day;
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

istream& operator >>(istream &in, Date &date)
{
    in >> date.day;
    in.ignore();
    in >> date.month;
    in.ignore();
    in >> date.year;
    
    return in;
}

ostream& operator<<(ostream& out, const Date &date) {
	out << date.getDay() << "/" << date.getMonth() << "/" << date.getYear();
	return out;
}

bool operator<(const Date &date1, const Date &date2) {
	return date1.getCompDate() < date2.getCompDate();
}

bool operator==(const Date &dat1, const Date &dat2)
{
	return (dat1.getYear() == dat2.getYear() && dat1.getMonth() == dat2.getMonth() && dat1.getDay() == dat2.getDay());
}