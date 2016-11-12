#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Person.h"
#include "Unit.h"

#define MAX_ECTS 75

//Header file for class Course, a class to handle a specific studies course

class Course {
private:
    std::vector<Student> students;
    std::vector<Teacher> teachers;
    std::map<std::string,Unit*> abbreviationToUnit; //Map whose key is a unit abbreviation, which is associated with its respective Unit pointer
public:
	Course() {}; //Default constructor
	Course(std::string studentsFile, std::string teachersFile, std::string manUnitsFile, std::string optUnitsFile);
	~Course() {}; //Deconstructor (NOT EMPTY, IMPLEMENT LATER!)

    std::vector<Student> getStudents() const; //!< Returns students vector
    std::vector<Teacher> getTeachers() const; //!< Returns teachers vector
    
	/* Different kinds of get to work with units throughout program */
	std::vector<Unit*> getAllUnits() const; //!< Returns vector with all units
	std::vector<Unit*> getAllMandatoryUnits() const; //!< Returns vector with all mandatory units
	std::vector<Unit*> getAllOptionalUnits() const; //!< Returns vector with all optional units
	std::vector<Unit*> getUnitsFromYear(unsigned int curricularYear) const; //!< Returns vector with all units from curricular year specified
	std::vector<Unit*> getOptUnitsFromYear(unsigned int curricularYear) const; //!< Returns vector with all optional units from curricular year specified (which can only be 4 or 5!)
	std::vector<Unit*> getManUnitsFromYear(unsigned int curricularYear) const; //!< Returns vector with all mandatory units from curricular year specified
	std::vector<Unit*> getUnitsFromSameScientificArea(Unit* u1) const; //!< Returns vector with all (optional) units with all optional units (not full!!) whose scientific area is the same as u1
    
    void showStudent(std::string studentName); //!< Finds a student by name and prints its information
    void showStudent(unsigned long int studentCode); //!< Finds a student by code and prints its information
	void save() const; //!< Saves all information to respective files
   
    bool verifyUnit(std::string unitAbbreviation) const; //!< Returns true if unit with unitAbbreviation as abbreviation exists
};
