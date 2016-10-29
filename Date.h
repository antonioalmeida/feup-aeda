#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Date {
private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	Date(){}; //Default constructor (does nothing; just here because since there are other constructors, default one isn't automatically created)
	Date(std::string date); //Date is given in a string in the format DD/MM/YYYY (to use when reading information from files)
	Date(unsigned int day, unsigned int month, unsigned int year); //Date elements given in separate (to use with run-time created objects)
	unsigned int getDay() const; //Returns date day
	unsigned int getMonth() const; //Returns date month
	unsigned int getYear() const; //Returns date year
	/* Not sure if these will be useful yet
	void setDay(unsigned int newDay); //Sets date's day to newDay
	void setMonth(unsigned int newMonth); //Sets date's month to newMonth
	void setYear(unsigned int newYear); //Sets date's year to newYear
	*/

	friend ostream& operator<<(ostream& out, const Date &date); //Overload of << operator so it can be send to cout like objects
	friend bool operator<(const Date &date1, const Date &date2); //Overload of < operator to compare two dates
};