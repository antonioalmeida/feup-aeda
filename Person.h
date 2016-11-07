#pragma once

#include <iostream>
#include <string>
#include "Date.h"
#include "Unit.h"


//Header file for class Person and its derived classes (Student and Teacher, for now; to be implemented)

class Person {
protected:
	std::string name;
	std::string email; //created directly from code ("up"+code+"@fe.up.pt" for Student, code+"@fe.up.pt" for Teacher)
public:
	Person() {}; //default constructor
	Person(std::string name);

	std::string getName() const;
	std::string getEmail() const;
	void setName(std::string newName);
	virtual void save(std::ostream &out) const = 0; //Save object to file (can't use overloaded operator<< because it'll be used to show object information in a more user-friendly way) - guarantees this class can't be instatiated (exactly what wanted)
};

class Student : public Person {
protected:
	static unsigned long int nextCode; //Sequential code used for 1st timers (unsigned int may not have enough memory, unsigned long should hold easily)
	unsigned long int code;
	std::string status;
	unsigned int ectsTaking; //Automatically 0 when object is created
	unsigned int curricularYear;
	double average; //Automatically 0.0 for freshmen, calculated after unitsDone and unitsTodo have all the information otherwise
	Teacher* mentor; //Automatically NULL pointer when object is createad (is changed in registration process)
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsDone; //When reading from file, curricularYear-1 iterations will be done, each line corresponding to the grades to subjects of a curricular year (only save the ones where grade >= 10!)
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsToDo; //Same as above but only save units with final grade < 10 (grade saved because it also counts for the average; to use later in the registration process to guarantee units left behind are picked first)
	std::vector<Unit*> unitsTaking; //Units chosen during registration (+ units left behind - do not add automatically, user must do it himself)
	bool registrationComplete; //Automatically false when object is created, true after student is registered
	Date registrationDate; //Not sure how it'll be handled, but needs to be here since it's stated in the paper...

public:
	Student() {}; //default constructor
	Student(ifstream &in);
    Student(std::string name, std::string status, unsigned int curricularYear, unsigned long int code = nextCode++);
	std::string getStatus() const;
	unsigned int getECTSTaking() const;
	unsigned long int getCode() const;
	double getAverage() const;
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> getUnitsDone() const;
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> getUnitsToDo() const;
	std::vector<Unit*> getUnitsTaking() const;
	Teacher* getMentor() const;
	Date getRegistrationDate() const; //If registrationComplete = false, do what?
	bool isRegistered() const; //Check if student is already registered, if so he'll be ignored in the registration process
	void setRegistration(); //The only state possible is to go from false to true so keeping it simple
	void setStatus(std::string newStatus);
	void setMentor(Teacher* newMentor);
	virtual void save(std::ostream &out) const;

	friend std::ostream& operator<<(std::ostream& out, const Student& s);
};

class Teacher : public Person {
protected:
	std::string code;
	std::vector<Unit*> unitsTaught;
public:
	Teacher() {}; //default constructor
	Teacher(ifstream &in);
	Teacher(std::string name, std::string code); //Ask for units taught inside the method

	std::string getCode() const;
	void addUnitTaught(Unit* newUnit);
	std::vector<Unit*> getUnitsTaught() const;
	virtual void save(std::ostream &out) const;

	friend std::ostream& operator<<(std::ostream& out, const Teacher& s);
};
