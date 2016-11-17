#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Date.h"
#include "Unit.h"

#define MAX_ECTS 75

//Header file for class Person and its derived classes Student and Teacher

class Person {
protected:
	std::string name;
	std::string email; //created directly from code ("up"+code+"@fe.up.pt" for Student, code+"@fe.up.pt" for Teacher)
public:
    //! Default constructor
	Person() {};
    
    //! Class constructor used for persons read from text files
    /*!
     \param in text file from where the person's information will be read
     */
	Person(std::istream &in);
    
    //! Class constructor used for persons created during program execution
    /*!
     \param name the created person's name
     */
	Person(std::string name);
    
    //! Get function to acess person's name
    /*!
     \return string with person's name
     \sa getEmail()
     */
	std::string getName() const;
    
    //! Get function to acess person's email
    /*!
     \return string with person's email
     \sa getName()
     */
	std::string getEmail() const;
    
    //! Sets the person's name to newName
    /*!
     \param newName string with person's new name
     \sa getName()
     */
	void setName(std::string newName);
    
    //! Prints person to out, used for writing to files. Virtual function, only used in derivated classed Student and Teacher
    /*!
     \param out stream the person will be printed to.
     */
	virtual void save(std::ostream &out) const {};
};

class Student : public Person {
protected:
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
    //! Sequential code used for 1st timers (unsigned int may not have enough memory, unsigned long should hold easily)
	static unsigned long int nextCode;
    
    //! Default constructor
	Student() {};
    
    //! Class constructor used for students read from text files
    /*!
     \param in text file from where the student's information will be read
     */
	Student(std::istream &in);
    
    //! Class constructor used for studens created during program execution
    /*!
     \param name string that holds the students's name
     \param status string that holds the student's status
     \param curricularYear unsigned int that holds the student's curricylar year
     \param unitsDone vector that holds the student's completed units
     \param unitsToDo vector that hold the student's uncompleted unites
     \param code int that holds the students code (automatically created if curricularYear == 1)
     */
	Student(std::string name, std::string status, unsigned int curricularYear, std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsDone, std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsToDo, unsigned long int code = nextCode++);

	unsigned long int getCode() const;
	std::string getStatus() const;
	float getECTSTaking() const;
	unsigned int getCurricularYear() const;
	double getAverage() const;
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> getUnitsDone() const;
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> getUnitsToDo() const;
	std::vector<Unit*> getUnitsTaking() const;
	Date getRegistrationDate() const; //If registrationComplete = false, do what?

	void addUnitDone(std::pair<Unit*, unsigned int> p);
	void addUnitToDo(std::pair<Unit*, unsigned int> p);
	void addUnitTaking(Unit* u);
	void calculateAverage();
	bool isRegistered() const; //Check if student is already registered, if so he'll be ignored in the registration process
	
	void setRegistration(); //The only state possible is to go from false to true so keeping it simple
	void setStatus(std::string newStatus);
	
	virtual void save(std::ostream &out) const;
	bool operator==(const Student &s1); //!< Students are equal if they have the same code (= same person)
	friend std::ostream& operator<<(std::ostream& out, const Student& s);

};

class Teacher : public Person {
protected:
	std::string code;
	std::vector<Unit*> unitsTaught;
	std::vector<Student*> pupils;
public:
    //! One (or more) teacher(s) will have the least amount of students as pupils. It is to those that should be assigned students first. This variable holds that minimum
	static unsigned int lessStudents;
    
    //! Default constructor (does nothing)
    Teacher() {};
    
    //! Class constructor used for teachers read from text files
    /*!
     \param in text file from where the teacher's information will be read
     */
	Teacher(std::istream &in);
    
    //! Class constructor used for teachers created during program execution
    /*!
     \param name string that holds the new teacher's name
     \param code string that holds the new teacher's code
     \param unitsTaught vector of type Unit* that holds the units taught by the new teacher
     */
	Teacher(std::string name, std::string code, std::vector<Unit*> unitsTaught);
    
    //! Gets a copy of the teacher's code
    /*!
     \return copy of string data member code
     */
	std::string getCode() const;
    
    //! Gets a copy of vector that holds the units taught by the teacher
    /*!
     \return copy of Unit* data member unitsTaught
     */
	std::vector<Unit*> getUnitsTaught() const;
    
    //! Gets a copy of vector that holds the teacher's pupils
    /*!
     \return copy of Student* data member pupils
     */
	std::vector<Student*> getPupils() const;

    //! Changes teacher's code to newCode
    /*!
     \param newCode string that represents the teacher's new code
     */
    void setCode(std::string newCode);

    //! Adds units newUnit to the teachers unitsTaught vector.
    /*!
     \param newUnit pointer to unit to be added.
     \sa addStudent(Student* newStudent);
     */
	void addUnitTaught(Unit* newUnit);
    
    //! Adds newStudent to the teachers pupils vector.
    /*!
     \param newStudent pointer to student to be added.
     \sa removeStudent(Student newStudent);
     */
	void addStudent(Student* newStudent);
    
    //! Removes oldStudent from the teachers pupils vector.
    /*!
     \param oldStudent student to be removed.
     \sa addStudent(Student* newStudent);
     */
	void removeStudent(Student oldStudent);

    //! Prints teacher to out, used for writing to files.
    /*!
     \param out stream the teacher will be printed to.
     \sa std::ostream& operator<<(std::ostream& out, const Teacher& s);
     */
	virtual void save(std::ostream &out) const;
    
    //! Overload of << operator
    /*!
     \param out stream the teacher will be printed to.
     \param s the teacher that will be printed.
     */
	friend std::ostream& operator<<(std::ostream& out, const Teacher& s);
};

bool sortByName(Student s1, Student s2); //!< Returns true if s1.name < s2.name
bool sortByAverage(Student s1, Student s2); //!< Returns true if s1.average < s2.average
bool sortByCurricularYear(Student s1, Student s2); //!< Returns true if s1.curricularYear < s2.curricularYear

bool sortTByName(Teacher t1, Teacher t2); //!< Returns true if t1.name < t2.name
