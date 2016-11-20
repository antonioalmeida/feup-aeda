#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "Exceptions.h"
#include "Utils.h"

/*! \file Date Class */

class Date {
private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	//! Default class constructor (does nothing)
	/*!
	*/
	Date() {};

	//! Creates a new (valid) date given by its three parameters
	/*!
	\param day unsigned int corresponding to the date's day
	\param month unsigned int corresponding to the date's month
	\param year unsigned int corresponding to the date's year
	*/
	Date(unsigned int day, unsigned int month, unsigned int year);

	//! Gets a copy of a date's day
	/*!
	\return copy of unsigned int data member day
	*/
	unsigned int getDay() const;

	//! Gets a copy of a date's month
	/*!
	\return copy of unsigned int data member month
	*/
	unsigned int getMonth() const;

	//! Gets a copy of a date's year
	/*!
	\return copy of unsigned int data member year
	*/
	unsigned int getYear() const;

	//! Gets a copy of a date in std::string format
	/*!
	\return date in std::string format in the form of DD/MM/YYYY
	*/
	std::string getDate() const;

	//! Changes a date's day
	/*!
	\param newDay unsigned int corresponding to the date's new day
	*/
	void setDay(unsigned int newDay);

	//! Changes a date's month
	/*!
	\param newMonth unsigned int corresponding to the date's new month
	*/
	void setMonth(unsigned int newMonth);

	//! Changes a date's year
	/*!
	\param newYear unsigned int corresponding to the date's new year
	*/
	void setYear(unsigned int newYear);

	//! Overload of operator<< to print out Date objects
	/*!
	\param out out stream where the object will be printed to
	\param date object that will be printed
	\return reference to out stream where the object will be printed to
	*/
	friend std::ostream& operator<<(std::ostream& out, const Date &date);

	//! Tests inferiority between two dates
	/*!
	\param date1 first of two dates to be compared
	\param date2 second of two dates to be compared
	\return true if date1 is before date2 in the Gregorian calendar standard, false otherwise
	*/
	friend bool operator<(const Date &date1, const Date &date2);

	//! Tests equalty between two dates
	/*!
	\param date1 first of two dates to be compared
	\param date2 second of two dates to be compared
	\return true if date1 is the same as date2 in the Gregorian calendar standard, false otherwise
	*/
	friend bool operator==(const Date &dat1, const Date &dat2);
};
