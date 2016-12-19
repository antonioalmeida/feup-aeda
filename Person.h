#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Date.h"
#include "Unit.h"

#define MAX_ECTS 75

/*! \file Person.h
 \brief Person and its derived classes Student and Teacher
 */

class Person {
protected:
	std::string name;
	std::string email;
public:
	//! Default constructor (does nothing)
	/*!
	*/
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
	float ectsTaking;
	unsigned int curricularYear;
	double average;
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsDone;
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsToDo;
	std::vector<Unit*> unitsTaking;
	bool registrationComplete;
	Date registrationDate;

public:
	//! Sequential code used for freshmen
	/*!
	*/
	static unsigned long int nextCode;

	//! Default constructor (does nothing)
	/*!
	*/
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
	 \param code int that holds the students code (automatically assigned if curricularYear is 1)
	 */
	Student(std::string name, std::string status, unsigned int curricularYear, std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsDone, std::vector<std::vector<std::pair<Unit*, unsigned int>>> unitsToDo, unsigned long int code = nextCode++);

	//! Gets a copy of the student's unique code
	/*!
	\return copy of unsigned long it data member code
	*/
	unsigned long int getCode() const;

	//! Gets a copy of the student's status
	/*!
	\return copy of string data member status
	*/
	std::string getStatus() const;

	//! Gets a copy of the amount of ECTS the student is currently taking
	/*!
	\return copy of float data member ectsTaking
	*/
	float getECTSTaking() const;

	//! Gets a copy of the student's current curricular year
	/*!
	\return copy of unsigned int data member curricularYear
	*/
	unsigned int getCurricularYear() const;

	//! Gets a copy of the value of the student's current average
	/*!
	\return copy of float data member average
	*/
	double getAverage() const;

	//! Gets a copy of the matrix that holds the information about units the student has taken and completed (pairs consisting of a pointer to the unit and the final grade)
	/*!
	\return copy of data member pair vector vectors of type <Unit*, unsigned int> unitsDone
	*/
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> getUnitsDone() const;

	//! Gets a copy of the matrix that holds the information about units the student has taken but not completed (pairs consisting of a pointer to the unit and the final grade)
	/*!
	\return copy of data member pair vector vectors of type <Unit*, unsigned int> unitsToDo
	*/
	std::vector<std::vector<std::pair<Unit*, unsigned int>>> getUnitsToDo() const;

	//! Gets a copy of the vector that holds pointers to the units the student's taking
	/*!
	\return copy of data member vector of type Unit* unitsTaking
	*/
	std::vector<Unit*> getUnitsTaking() const;

	//! Gets a copy of the student's registration date
	/*!
	\return copy of data member registrationDate, an object of custom class Date
	*/
	Date getRegistrationDate() const;

	//! Adds a pair consisting of a unit the student has taken and the (positive) grade he obtained at it to the unitsDone matrix
	/*!
	\param p pair whose left side is a pointer to the unit and the right side is the final grade obtained
	*/
	void addUnitDone(std::pair<Unit*, unsigned int> p);

	//! Adds a pair consisting of a unit the student has taken and the (negative) grade he obtained at it to the unitsToDo matrix
	/*!
	\param p pair whose left side is a pointer to the unit and the right side is the final grade obtained
	*/
	void addUnitToDo(std::pair<Unit*, unsigned int> p);

	//! Removes given unit of the unitsToDo matrix. Called during registration process which means student is now taking this unit (again)
	/*!
	\param u pointer to the unit to be removed
	*/
	void removeUnitToDo(Unit* u);

	//! Adds a unit that the student is taking to the unitsTaking vector. Throws exception if adding the unit would cause an ECTS overflow
	/*!
	\param u pointer to the unit to be added
	*/
	void addUnitTaking(Unit* u);

	//! Calculates the student's current average. Is left at 0 if it's a freshman
	/*!
	*/
	void calculateAverage();

	//! Checks if given student has completed the registration process
	/*!
	\return current value of data member isRegistered: true if student has completed registration, false otherwise
	*/
	bool isRegistered() const;

	//! Changes a student's registration status to its current opposite (true if false and vice-versa)
	/*!
	*/
	void setRegistration();

	//! Changes a student's status to a new one
	/*!
	\param newStatus string corresponding to the student's new status
	*/
	void setStatus(std::string newStatus);

	//! Changes a students registration date to newDate
	/*!
	 \param newDate Date corresponding to the student's new registration date
	 \sa getRegistrationDate();
	 */
	void setRegistrationDate(Date newDate);

	//! Changes a students ectsTaking value to newECTS
	/*!
	 \param newECTS float that holds the student's new ectsTaking value
	 \sa getECTSTaking()
	 */
	void setECTSTaking(float newECTS);

	//! Prints student to out (used when writing to file)
	/*!
	\param out outstream where the student will be printed to
	*/
	virtual void save(std::ostream &out) const;

	//! Overload of operator== to test equalty between students
	/*!
	\param s student that it will be compared to
	\return true if students have the same code, false otherwise
	*/
	bool operator==(const Student &s1);

	//! Overload of operator<< to print students to screen
	/*!
	\param out outstream where the student will be printed to
	\param s student that will be printed
	*/
	friend std::ostream& operator<<(std::ostream& out, const Student& s);

};

class Reunion {
private:
	Date date;
	std::string student;
	std::string agenda;
	std::string conclusions;
	bool hasTakenPlace; //to avoid using weird Windows functions to get time (could always use RTC though...)
public:
	Reunion() {};
	Reunion(Date date, std::string student, std::string agenda, std::string conclusions);
	Date getDate() const;
	std::string getStudent() const;
	std::string getAgenda() const;
	std::string getConclusions() const;
	bool reunionHasTakenPlace() const;
	void changeConclusions(std::string newConclusions);
	void setAsTaken();
	bool operator==(const Reunion &r1); //not sure if we'll need it
	friend std::ostream& operator<<(std::ostream& out, const Reunion &r1);
};

struct compareReunions {
	bool operator()(const Reunion &r1, const Reunion &r2) {
		return r1.getDate() < r2.getDate();
	}
};

class Teacher : public Person {
protected:
	std::string code;
	std::vector<Unit*> unitsTaught;
	std::vector<Student*> pupils;
	std::set<Reunion,compareReunions> reunions;
public:
	//! One (or more) teacher(s) will have the least amount of students as pupils. It is to those that should be assigned students first. This variable holds that minimum
	/*!
	*/
	static unsigned int lessStudents;

	//! Default constructor (does nothing)
	/*!
	*/
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

	std::set<Reunion,compareReunions> getReunions() const;
	void addReunion(Reunion r1);
	void cancelSpecificReunion(Reunion r1);
	void changeSpecificReunionConclusions(Reunion r1, std::string newConclusions);
	void setReunionAsTaken(Reunion r1);
};

//! Compares two students by their names (used as custom comparison function in STL sort)
/*!
\param s1 first student of the two to be compared
\param s2 second student of the two to be compared
\return true if student s1's name is alphabetically inferior to student s2's name, false otherwise
*/
bool sortByName(Student s1, Student s2);

//! Compares two students by their current course average (used as custom comparison function in STL sort)
/*!
\param s1 first student of the two to be compared
\param s2 second student of the two to be compared
\return true if s1's average is inferior to s2's average, false otherwise
*/
bool sortByAverage(Student s1, Student s2);

//! Compares two students by their current curricular year (used as custom comparison function in STL sort)
/*!
\param s1 first student of the two to be compared
\param s2 second student of the two to be compared
\return true if s1's curricular year is inferior to s2's curricular year, false otherwise
*/
bool sortByCurricularYear(Student s1, Student s2);

//! Compares two teachers by their names (used as custom comparison function in STL sort)
/*!
\param t1 first teacher of the two to be compared
\param t2 second teacher of the two to be compared
\return true if t1's name is alphabetically inferior to t2's name, false otherwise
*/
bool sortTByName(Teacher t1, Teacher t2);
