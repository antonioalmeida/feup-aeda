#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>


class Date {
private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	Date(){}; //Default constructor (does nothing; just here because since there are other constructors, default one isn't automatically created)
	Date(unsigned int day, unsigned int month, unsigned int year); //Date elements given in separate (to use with run-time created objects)
	Date(std::string DateStr); //constructor for a date with a string (DD/MM/YYYY)

	unsigned int getDay() const; //Returns date day
	unsigned int getMonth() const; //Returns date month
	unsigned int getYear() const; //Returns date year
	std::string Date::getDate() const; //Returns date in form (DD/MM/YYYY)
	int getCompDate() const; //get date in form of integer to compare
	
	void setDay(unsigned int newDay); //Sets date's day to newDay
	void setMonth(unsigned int newMonth); //Sets date's month to newMonth
	void setYear(unsigned int newYear); //Sets date's year to newYear
	
    
    friend std::istream& operator >>(std::istream& in, Date &date); //Overload of >> to read from files
    friend std::ostream& operator<<(std::ostream& out, const Date &date); //Overload of << operator so it can be send to cout like objects
	friend bool operator<(const Date &date1, const Date &date2); //Overload of < operator to compare two dates
	friend bool operator==(const Date &dat1, const Date &dat2); //Overload of == operator to compare if two dates are equal
};
