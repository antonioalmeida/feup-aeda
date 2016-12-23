#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include "Person.h"
#include "Unit.h"
#include "Utils.h"
#include "StudentsClass.h"

/*! \file Course.h
 \brief Course, a class to handle a specific studies course
 */


struct studentOutHash
{
	int operator() (const Student &s1) const
	{
		int v = 0;
		for (unsigned int i = 0; i < s1.getName().size(); i++)
			v = 37 * v + s1.getName()[i];
		return v;
	}

	bool operator() (const Student &s1, const Student &s2) const
	{
		return s1.getCode() == s2.getCode();
	}
};

typedef std::unordered_set <Student, studentOutHash, studentOutHash> studentsHash;

class Course {
private:
	std::vector<Student> students;
	std::vector<Teacher> teachers;
	std::map<std::string, Unit*> abbreviationToUnit; //Map whose key is a unit abbreviation, which is associated with its respective Unit pointer
	std::vector<std::priority_queue<StudentsClass>> studentsClasses;
	studentsHash studentsOut;

public:
	//! Default constructor (does nothing)
	/*!
	*/
	Course() {};

	//! Class constructor that takes names of files that hold the structures' informations
	/*!
	\param studentsFile string corresponding to name of file that holds all students' information
	\param teachersFile string corresponding to name of file that holds all teachers' information
	\param manUnitsFile string corresponding to name of file that holds all mandatory units' information
	\param optUnitsFile string corresponding to name of file that holds all optional units' information
	*/
	Course(std::string studentsFile, std::string teachersFile, std::string manUnitsFile, std::string optUnitsFile);

	//! Deconstructor. Destroys object
	/*!
	*/
	~Course() {};

	//! Gets a copy of vector that holds all the students
	/*!
	\return copy of Student vector data member students
	*/
	std::vector<Student> getStudents() const;

	//! Gets a copy of vector that holds all the teachers
	/*!
	\return copy of Teacher vector data member teachers
	*/
	std::vector<Teacher> getTeachers() const;

	//! Gets a copy of map that holds association between a unit's abbreviation and its pointer
	/*!
	\return copy of string to Unit* map data member abbreviationToUnit
	*/
	std::map<std::string, Unit*> getMap() const;

	//! Gets a vector that holds pointers to all units
	/*!
	\return vector of Unit* containing pointers to all units
	*/
	std::vector<Unit*> getAllUnits() const;

	//! Gets a vector that holds pointers to all mandatory units
	/*!
	\return vector of Unit* containing pointers to all mandatory units
	*/
	std::vector<Unit*> getAllMandatoryUnits() const;

	//! Gets a vector that holds pointers to all optional units
	/*!
	\return vector of Unit* containing pointers to all optional units
	*/
	std::vector<Unit*> getAllOptionalUnits() const;

	//! Gets vector that holds pointers to all units from a specific curricular year
	/*!
	\param curricularYear unsigned int corresponding to the curricular year desired to get units from
	\return vector of Unit* containing pointers to all units from curricular year given as argument
	*/
	std::vector<Unit*> getUnitsFromYear(unsigned int curricularYear) const;

	//! Gets vector that holds pointers to all optional units from a specific curricular year (if < 4, returns empty vector)
	/*!
	\param curricularYear unsigned int corresponding to the curricular year desired to get units from
	\return vector of Unit* containing pointers to all optional units from curricular year given as argument
	*/
	std::vector<Unit*> getOptUnitsFromYear(unsigned int curricularYear) const;

	//! Gets vector that holds pointers to all mandatory units from a specific curricular year
	/*!
	\param curricularYear unsigned int corresponding to the curricular year desired to get units from
	\return vector of Unit* containing pointers to all mandatory units from curricular year given as argument
	*/
	std::vector<Unit*> getManUnitsFromYear(unsigned int curricularYear) const;

	//! Gets vector that holds pointers to all not-full optional units from the same scientific area as unit pointed in argument
	/*!
	\param u1 pointer to unit that determines which is the scientific area to be searched
	\return vector of Unit* containing pointers to all not-full optional units whose scientific area matches the specified
	*/
	std::vector<Unit*> getUnitsFromSameScientificArea(Unit* u1) const;

	//! Creates a new student and adds it to students vector. Throws exceptions if new student's name or code already identifies another student
	/*!
	*/
	void addStudent();

	//! Removes student specified by his code (also removed from his mentor's pupils vector if the case). Throws exception if code does not identify any student
	/*!
	\param studentCode unsigned long corresponding to the code of student to be removed
	*/
	void removeStudent(unsigned long studentCode);

	//! Removes student specified by his name (also removed from his mentor's pupils vector if the case). Throws exception if name does not identify any student
	/*!
	\param studentName string corresponding to the name of student to be removed
	*/
	void removeStudent(std::string studentName);

	//! Shows a specific student specified by his name. Throws exception if name does not identify any student
	/*!
	\param studentName string corresponding to the name of student to be printed
	*/
	void showStudent(std::string studentName) const;

	//! Shows a specific student specified by his code. Throws exception if code does not identify any student
	/*!
	\param studentCode unsigned long corresponding to the code of student to be printed
	*/
	void showStudent(unsigned long int studentCode) const;

	//! Shows all students. Print order depends on function given as argument
	/*!
	\param comparisonFunction boolean function that compares two students. Will be used to sort students vector
	*/
	void showStudents(bool(*comparisonFunction)(Student, Student)) const;

	//! Shows all students whose status matches the one given as argument, alphabetically
	/*!
	\param status string corresponding to the status that will filter which students to show
	*/
	void showStudentsStatus(std::string status) const;

	//! Shows all students that have completed the registration process
	/*!
	*/
	void showRegisteredStudents() const;

	//! Shows all students that have not completed the registration process
	/*!
	*/
	void showUnregisteredStudents() const;

	//! Shows all students that are taking a specific unit (identified inside the function). Throws exception if specified unit does not exist
	/*!
	*/
	void showUnitRegistrations() const;

	//! Shows all units a specific student is registered to. Throws exception if argument does not identify any student
	/*!
	\param studentName string corresponding to the name of student whose registration information will be shown
	*/
	void showStudentUnits(std::string studentName) const;

	//! Shows all units a specific student is registered to. Throws exception if argument does not identify any student
	/*!
	\param studentCode unsigned long corresponding to the code of student whose registration information will be shown
	*/
	void showStudentUnits(unsigned long studentCode) const;

	//! Shows all students from a specific curricular year given as argument
	/*!
	\param curricularYear unsigned short int corresponding to the curricular year to filter students to be shown
	*/
	void showStudentsYear(unsigned short int curricularYear) const;

	//! Shows registration information of all students from specified curricular year
	/*!
	\param yearToShow unsigned int corresponding to the curricular year registration information will be shown
	*/
	void showYearRegistrations(unsigned int yearToShow) const;

	//! Shows registration information of all students
	/*!
	*/
	void showAllStudentsRegistrations() const;

	//! Edits a specific student's name (identification asked inside function). Throws exception if specified student does not exist or new name is already taken
	/*!
	*/
	void editStudentName();

	//! Edits a specific student's status (identification asked inside function). Throws exception if specified student does not exist
	/*!
	*/
	void editStudentStatus();

	//! Registers a 'random' student (in reality, the first one in students vector that has not done the registration process yet). Throws exception if there's no one left to register
	/*!
	*/

	void registerRandomStudent();

	//! Registers a specific student identified by his name. Throws exception if student does not exist or has already completed the registration process
	/*!
	*/
	void registerSpecificStudentByName();

	//! Registers a specific student identified by his code. Throws exception if student does not exist or has already completed the registration process
	/*!
	*/
	void registerSpecificStudentByCode();

	//! Creates a new teacher and adds its to the teachers vector. Throws exception if new teacher's name or code has already been taken
	/*!
	*/
	void addTeacher();

	//! Edits a specific teacher's name (teacher identified inside the function). Throws exception if specified teachers does not exist or new name has already been taken
	/*!
	*/
	void editTeacherName();

	//! Edits a specific teacher's code (teacher identified inside the function). Throws exception if specified teachers does not exist or new code has already been taken
	/*!
	*/
	void editTeacherCode();

	//! Edits a specific unit's name (unit identified inside the function). Throws exception if specified unit does not exist or new name has already been taken
	/*!
	*/
	void editUnitName();

	//! Edits a specific unit's abbreviation (unit identified inside the function). Throws exception if specified unit does not exist or new abbreviation has already been taken
	/*!
	*/
	void editUnitAbbreviation();

	//! Edits a specific unit's scientific area (unit identified inside the function). Throws exception if specified unit does not exist
	/*!
	*/
	void editUnitScientificArea();

	//! Adds a unit taught to a specific teacher (teacher identified inside the function). Throws exception if specified teacher does not exist
	/*!
	*/
	void teacherAddUnitTaught();

	//! Removes a teacher specified by his name. Throws exception if argument does not identify any teacher
	/*!
	\param teacherName string corresponding to the name of teacher to be removed
	*/
	void removeTeacher(std::string teacherName);

	//! Shows all teachers. Print order depends on comparison function given as argument
	/*!
	\param comparisonFunction boolean function that compares two teachers
	*/
	void showTeachers(bool(*comparisonFunction)(Teacher, Teacher)) const;

	//! Shows a specific teacher identified by his name or code. Throws exception if argument does not identify any teacher
	/*!
	\param teacherID string corresponding to either the name or code of teacher to be shown
	*/
	void showTeacher(std::string teacherID) const;

	//! Shows a specific teacher responsible for unit pointed as argument
	/*!
	\param u1 pointer to unit whose responsible teacher will be printed
	*/
	void showTeacher(Unit* u1) const;

	//! Shows a specific teacher that mentors student identified as argument. Throws exception in case teacher not found (which can mean the student does not exist or does not have a mentor yet)
	/*!
	\param pupilName string corresponding to the name of a student mentored by the wanted teacher
	*/
	void showTeacherPupilByName(std::string pupilName) const;

	//! Shows a specific teacher that mentors student identified as argument. Throws exception in case teacher not found (which can mean the student does not exist or does not have a mentor yet)
	/*!
	\param pupilCode unsigned long corresponding to the code of a student mentored by the wanted teacher
	*/
	void showTeacherPupilByCode(unsigned long int pupilCode) const;

	//! Shows all units alphabetically
	/*!
	*/
	void showUnits() const;

	//! Shows a specific unit (identified inside the function). Throws exception if specified unit does not exist
	/*!
	*/
	void showSpecificUnit() const;

	//! Shows all units from a curricular year passed as argument
	/*!
	\param year unsigned short corresponding to the curricular year whose units will be shown
	*/
	void showYearUnit(unsigned short int year) const;

	//! Shows all mandatory units
	/*!
	*/
	void showMandatoryUnit() const;

	//! Shows all optional units
	/*!
	*/
	void showOptionalUnit() const;

	//! Shows all units of scientific area passed as argument
	/*!
	\param scientificArea string corresponding to the scientific area whose units will be shown
	*/
	void showUnitsofScientificArea(std::string scientificArea) const;

	//! Saves all course information (students, teachers, mandatory units, optional units) to text files specified by user
	/*!
	*/
	void save() const;

	//! Checks if abbreviation passeda as argument corresponds to an existent unit
	/*!
	\param unitAbbreviation string corresponding to abbreviation of unit that will be verified
	*/
	bool verifyUnit(std::string unitAbbreviation) const;

	void teacherAddReunion();
	void teacherCancelReunion();
	void teacherEditReunionConclusions();
	void teacherMarkReunionAsDone();
	void showTeacherReunions();
	void showTeacherReunionsDone();
	void showTeacherReunionsInPeriod();

	std::vector<std::priority_queue<StudentsClass>> getStudentsClasses();
	void addStudentsClass(unsigned int curricularYear);
	void removeStudentsClass(unsigned int curricularYear, unsigned int classNumber);
	void listStudentsClassVacancies(unsigned int curricularYear);

	void editStudentCourseStatus();
};
