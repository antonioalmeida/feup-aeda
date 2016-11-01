#pragma once

#include <iostream>
#include <string>
#include "Date.h"
#include "Unit.h"


//Header file for class Person and its derived classes (Student and Teacher, for now; to be implemented)

class Person {
protected:
    std::string name;
    Date birthDate;
    std::string email; //created directly from code
public:
	Person() {}; //default constructor
    Person(std::string name, Date birthDate);

    Date getBirthDate() const;
    std::string getName() const;
    std::string getCode() const;
    std::string getEmail() const;
    void setBirthDate(Date newDate);
    void setName(std::string newName);	
};

class Student : public Person {
protected:
	static unsigned int nextCode; //Sequential code used for 1st timers
	unsigned int code;
    std::string status;
    unsigned int ectsTaking;
	unsigned int curricularYear;
	vector<vector<Unit*>> units;

public:
	Student() {}; //default constructor
    Student(std::string name, Date birthDate, std::string specialStatus, unsigned int curricularYear, unsigned int code = Student::nextCode);

    std::string getSpecialStatus() const;
	unsigned int getECTSTaking() const;
	unsigned int getCode() const;
	vector<vector<Unit*>> getUnits() const;
    void setSpecialStatus(std::string newStatus);

	    
    friend std::ostream& operator<<(std::ostream& out, const Student& s);
    friend std::istream& operator>>(std::istream& in, Student& s); //Check if curricular year is 1. If so, code is automatically given from static member. If not, code is read from file
};

class Teacher : public Person {
protected:
	std::string code;
	vector<Unit*> units;
public:
	Teacher() {}; //default constructor
    Teacher(std::string name, std::string code, Date birthDate, vector<Unit*> units);
    
    friend std::ostream& operator<<(std::ostream& out, const Teacher& s);
    friend std::istream& operator>>(std::istream& in, Teacher& s);
};
