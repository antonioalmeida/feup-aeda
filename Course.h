#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include "Person.h"
#include "Unit.h"
#include "Utils.h"

//Header file for class Course, a class to handle a specific studies course

class Course {
private:
	std::vector<Student> students;
	std::vector<Teacher> teachers;
	std::map<std::string, Unit*> abbreviationToUnit; //Map whose key is a unit abbreviation, which is associated with its respective Unit pointer
public:
	Course() {}; //Default constructor
	Course(std::string studentsFile, std::string teachersFile, std::string manUnitsFile, std::string optUnitsFile);
	~Course() {}; //Deconstructor (NOT EMPTY, IMPLEMENT LATER!)

	std::vector<Student> getStudents() const; //!< Returns students vector
	std::vector<Teacher> getTeachers() const; //!< Returns teachers vector

	/* Different kinds of get to work with units throughout program */
	std::map<std::string, Unit*> getMap() const; //!< Returns map used
	std::vector<Unit*> getAllUnits() const; //!< Returns vector with all units
	std::vector<Unit*> getAllMandatoryUnits() const; //!< Returns vector with all mandatory units
	std::vector<Unit*> getAllOptionalUnits() const; //!< Returns vector with all optional units
	std::vector<Unit*> getUnitsFromYear(unsigned int curricularYear) const; //!< Returns vector with all units from curricular year specified
	std::vector<Unit*> getOptUnitsFromYear(unsigned int curricularYear) const; //!< Returns vector with all optional units from curricular year specified (which can only be 4 or 5!)
	std::vector<Unit*> getManUnitsFromYear(unsigned int curricularYear) const; //!< Returns vector with all mandatory units from curricular year specified
	std::vector<Unit*> getUnitsFromSameScientificArea(Unit* u1) const; //!< Returns vector with all (optional) units with all optional units (not full!!) whose scientific area is the same as u1

	void addStudent(); //!< Adds new student to students vector if all information provided is valid (if given code in case of student of curricularYear >= 2 already exists, exception is thrown)
	void removeStudent(unsigned long studentCode); //!< Removes student (also removed from his mentor's vector if it is the case). Exception thrown is student does not exist
	void removeStudent(std::string studentName); //!< Removes student (also removed from his mentor's vector if it is the case). Exception thrown is student does not exist

	void showStudent(std::string studentName) const; //!< Finds a student by name and prints its information
	void showStudent(unsigned long int studentCode) const; //!< Finds a student by code and prints its information
	void showStudents(bool(*comparisonFunction)(Student, Student)) const; //!< Prints all students information based on specific sort passed as argument
	void showStudentsStatus(std::string status) const; //!< Shows students whose status is 'status' alphabetically
	void showRegisteredStudents() const; //!< Shows registered students
	void showUnregisteredStudents() const; //!< Show unregistered students
	void showUnitRegistrations() const; //!< Shows students registered to a specific unit. Throws exception if unit specified does not exist
	void showStudentUnits(std::string studentName) const; //!< Show units a student is taking. Throws exception if student does not exist
	void showStudentUnits(unsigned long studentCode) const; //!< Show units a student is taking. Throws exception if student does not exist
	void showYearRegistrations(unsigned int yearToShow) const; //!< Show all students of a curricular year's registrations
	void showAllStudentsRegistrations() const; //!< Show all students' registrations
	void editStudentName(); //!< Edits a given student's name. Throws exception if specified student does not exist or new name is already taken
	void editStudentStatus(); //!< Edits a given student's name. Throws exception if specified student does not exist
	void registerRandomStudent();
	void registerSpecificStudentByName();
	void registerSpecificStudentByCode();

	void addTeacher();
	void editTeacherName();
	void editTeacherCode();
	void editUnitName();
	void editUnitAbbreviation();
	void editUnitScientificArea();
	void teacherAddUnitTaught();
	void removeTeacher(std::string teacherName);
	void showTeachers(bool(*comparisonFunction)(Teacher, Teacher)) const;
	void showTeacher(std::string teacherID) const;
	void showTeacher(Unit* u1) const;
	void showTeacherPupilByName(std::string pupilName) const;
	void showTeacherPupilByCode(unsigned long int pupilCode) const;

	void showUnits() const;
	void showSpecificUnit() const;
	void showYearUnit(unsigned short int year) const;
	void showMandatoryUnit() const;
	void showOptionalUnit() const;
	void showUnitsofScientificArea(std::string scientificArea) const;

	void save() const; //!< Saves all information to respective files

	bool verifyUnit(std::string unitAbbreviation) const; //!< Returns true if unit with unitAbbreviation as abbreviation exists
};
