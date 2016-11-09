#pragma once
#include <string>
#include <vector>
#include <map>
#include "Person.h"
#include "Unit.h"

//Header file for class Course, a class to handle a specific studies course (may be renamed to MIEIC; to be implemented)

class Course {
private:
    /*vector<Student> students;
    vector<Teacher> teachers;
    
    map<string,Unit*> unitsYear;
    
    map<string,Unit*> unitsYear1;
    map<string,Unit*> unitsYear2;
    map<string,Unit*> unitsYear3;
    map<string,Unit*> unitsYear4;
    map<string,Unit*> unitsYear5;*/
    
public:
    std::vector<Student> getStudents(); //!< Returns students vector
    std::vector<Teacher> getTeachers(); //!< Returns teachers vector
    
    void addStudent(Student s1); //!< Adds a student to the students vector. Not the same as registering him/her
    void removeStudent(Student s1); //!< Removes a student from the students vector
    
    void showStudents(int curricularYear); //!< Show students from a specific curricular year
    void showStudents(Unit* unit); //!< Show a specific unit's students
    void showAllStudent(); //!< Show all students alphabetically
    
    void assignTutor(Student s1); //!< Assign a tutor to s1. The algorithm should define the teacher
    
    void showRegistrations(Student s1); //!< Show unit(s) a specific student is registered in
};
