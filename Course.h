#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Person.h"
#include "Unit.h"

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
    std::vector<Student> getStudents(); //!< Returns students vector
    std::vector<Teacher> getTeachers(); //!< Returns teachers vector
    
    void addStudent(Student s1); //!< Adds a student to the students vector. Not the same as registering him/her
    void removeStudent(Student s1); //!< Removes a student from the students vector
    
    void showStudents(int curricularYear); //!< Show students from a specific curricular year
    void showStudents(Unit* unit); //!< Show a specific unit's students
    void showAllStudents(); //!< Show all students alphabetically
    
    void showRegistrations(Student s1); //!< Show unit(s) a specific student is registered in
};
