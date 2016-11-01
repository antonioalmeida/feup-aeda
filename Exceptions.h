#pragma once

//Header file for custom made exceptions to be caught and treated throughout program execution (to be implemented)

/* Date class exceptions */
class invalidDay{
private:
	unsigned int day;
public:
	invalidDay(unsigned int invDay) {
		day = invDay;
	}
	unsigned int getInvDay() const {
		return day;
	}
};

class invalidMonth{
private:
	unsigned int month;
public:
	invalidMonth(unsigned int invMonth) {
		month = invMonth;
	}
	unsigned int getInvMonth() const {
		return month;
	}
};
    
class invalidDate { //When day and month are in a valid range but are wrongly used (ex: 30th February, 31st November, ...)
private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	invalidDate(unsigned int invDay, unsigned int invMonth, unsigned int invYear) {
		day = invDay;
		month = invMonth;
		year = invYear;
	}
	unsigned int getInvDay() const {
		return day;
	}
	unsigned int getInvMonth() const {
		return month;
	}
	unsigned int getInvYear() const {
		return year;
	}
};

