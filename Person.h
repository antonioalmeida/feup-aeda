#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Date.h"
#include "Unit.h"

#define MAX_ECTS 75

//Header file for class Person and its derived classes (Student and Teacher, for now; to be implemented)

class Person {
protected:
	std::string name;
	std::string email; //created directly from code ("up"+code+"@fe.up.pt" for Student, code+"@fe.up.pt" for Teacher)
public:
	Person() {}; //default constructor
	Person(std::istream &in);
	Person(std::string name);

	std::string getName() const;
	std::string getEmail() const;
	void setName(std::string newName);
	virtual void save(std::ostream &out) const {}; //Save object to file (can't use overloaded operator<< because it'll be used to show object information in a more user-friendly way)
};

class Student : public Person {
protected:
	static unsigned long int nextCode; //Sequential code used for 1st timers (unsigned int may not have enough memory, unsigned long should hold easily)
	unsigned long int code;
	std::string status;
	float ectsTaking; //Automatically 0 when object is created
	unsigned int curricularYear;
	double average; //Automatically 0.0 for freshmen, calculated after unitsDone and unitsTodo have all the information otherwise
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsDone; //When reading from file, curricularYear-1 iterations will be done, each line corresponding to the grades to subjects of a curricular year (only save the ones where grade >= 10!)
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsToDo; //Same as above but only save units with final grade < 10 (grade saved because it also counts for the average; to use later in the registration process to guarantee units left behind are picked first)
	std::vector<Unit*> unitsTaking; //Units chosen during registration (+ units left behind - do not add automatically, user must do it himself)
	bool registrationComplete; //Automatically false when object is created, true after student is registered
	Date registrationDate; //Not sure how it'll be handled, but needs to be here since it's stated in the paper...

public:
	Student() {}; //default constructor
	Student(std::istream &in);
    Student(std::string name, std::string status, unsigned int curricularYear, std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsDone, std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsToDo, unsigned long int code = nextCode++);
    
	std::string getStatus() const;
	float getECTSTaking() const;
	unsigned long int getCode() const;
	unsigned int getCurricularYear() const;
	double getAverage() const;
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> getUnitsDone() const;
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> getUnitsToDo() const;
	std::vector<Unit*> getUnitsTaking() const;
	Date getRegistrationDate() const; //If registrationComplete = false, do what?
	void addUnitDone(std::pair<Unit*, unsigned int> p);
	void addUnitToDo(std::pair<Unit*, unsigned int> p);
	void addUnitTaking(Unit* u);
	bool isRegistered() const; //Check if student is already registered, if so he'll be ignored in the registration process
	void setRegistration(); //The only state possible is to go from false to true so keeping it simple
	void setStatus(std::string newStatus);
	virtual void save(std::ostream &out) const;
	bool operator==(const Student &s1); //!< Students are equal if they have the same code (= same person)

	friend std::ostream& operator<<(std::ostream& out, const Student& s);
    friend bool sortByName(Student s1, Student s2); //!< Returns true if s1.name < s2.name
    friend bool sortByAverage(Student s1, Student s2); //!< Returns true if s1.average < s2.average
    friend bool sortByCurricularYear(Student s1, Student s2); //!< Returns true if s1.curricularYear < s2.curricularYear
};

class Teacher : public Person {
protected:
	static unsigned int lessStudents; //One (or more) teacher(s) will have the least amount of students as pupils. It is to those that should be assigned students first. This variable holds that minimum
	std::string code;
	std::vector<Unit*> unitsTaught;
	std::vector<Student*> pupils;
public:
	Teacher() {}; //default constructor
	Teacher(std::istream &in);
	Teacher(std::string name, std::string code, std::vector<Unit*> unitsTaught);

	std::string getCode() const;
	std::vector<Student*> getPupils() const;
	void addUnitTaught(Unit* newUnit);
	void addStudent(Student* newStudent);
	void removeStudent(Student oldStudent); //!< Removes student from pupils vector if he exists, otherwise does nothing
	std::vector<Unit*> getUnitsTaught() const;
	virtual void save(std::ostream &out) const;

	friend std::ostream& operator<<(std::ostream& out, const Teacher& s);
	friend bool sortTByName(Teacher t1, Teacher t2); //!< Returns true if t1.name < t2.name
};
