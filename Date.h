#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "Exceptions.h"
#include "Utils.h"

/*! Date Class */

class Date {
private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	Date() {}; // Default class constructor
	Date(unsigned int day, unsigned int month, unsigned int year); //!< Class constructor with parameters. Date elements given in separate (to use with run-time created objects)

	unsigned int getDay() const; //!< Returns date day
	unsigned int getMonth() const; //!< Returns date month
	unsigned int getYear() const; //!< Returns date year
	std::string getDate() const; //!< Returns date in form (DD/MM/YYYY)
	void setDay(unsigned int newDay); //!< Sets date's day to newDay
	void setMonth(unsigned int newMonth); //!< Sets date's month to newMonth
	void setYear(unsigned int newYear); //!< Sets date's year to newYear

	friend std::ostream& operator<<(std::ostream& out, const Date &date); //!< Overload of << operator so it can be sent to cout like objects
	friend bool operator<(const Date &date1, const Date &date2); //!< Overload of < operator to compare two dates
	friend bool operator==(const Date &dat1, const Date &dat2); //!< Overload of == operator to compare if two dates are equal
};
