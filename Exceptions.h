#pragma once

//Header file for custom made exceptions to be caught and treated throughout program execution (to be implemented)

class invalidDay{ //Invalid day regardless of other date specifications (day == 0 or day > 31)
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

class invalidMonth{ //Invalid month regardless of other date specifications (month == 0 or month > 12)
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
    
class invalidDate { //When day and month are in a valid range but are wrongly used (ex: 30th February, 29th February on a non-leap year, 31st November, ...)
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

template <class T> class invalidIdentification { //When search for specific person goes wrong (may search by code - which can be string or unsigned long it, name... whatever)
private:
	T identification;
public:
	invalidIdentification(T id) {
		identification = id;
	}
	T getInvIdentification() const {
		return identification;
	}
};

template <class T> class repeatedIdentification { //When trying to change an identification member of an object, it may already exist. That would cause conflict if searches are made based on it, so can't allow it
private:
	T identification;
public:
	repeatedIdentification(T id) {
		identification = id;
	}
	T getRepIdentification() const {
		return identification;
	}
};

class inexistentFile { //When trying to open a file whose name is 'filename' and it does not exist
private:
	std::string filename;
public:
	inexistentFile(std::string file) {
		filename = file;
	}
	std::string getInexistentFileName() const {
		return filename;
	}
};

class tooManyECTS { //When user is trying to make student take more than 75 ECTS
public:
	tooManyECTS() {};
};