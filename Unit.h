#pragma once

#include <string>
#include <vector>
//Header file for class Unit and its derived classes (MandatoryUnit and OptionalUnit, for now; to be implemented)

class Unit {
    std::string name;
    std::string code;
    int ECTS;
    int year;
public:
    Unit(); //default constructor
    Unit(std::string name, std::string code, int ects, int year); //complete constructor
    std::vector<Teacher> teachers;
    std::vector<Student> students;
    
   /* 'get'-methods */
    std::string getName();
    std::string getCode();
    int getECTS();
    int getYear();
    std::vector<Teacher> getTeachers();
    std::vector<Student> getStudents();
    virtual bool isVacant() = 0;
    
    /* 'set'-methods */
    void setName(std::string newName);
    void setCode(std::string newCode);
    void setECTS(int newECTS);
    
    void addStudent(Student newStudent);
    void removeStudent(Student removedStudent); //Create a version that takes an iterator as argument?
    void addTeacher(Teacher newTeacher);
    void removeTeacher(Teacher removedTeacher); //"YOU'RE FIRED!" Create a version that takes an iterator as argument?

	friend bool operator<(const Unit &u1, const Unit &u2); //To compare 2 units (important because units in a larger scale may be used in a big map - easier to work with; CRITERIA!!!! u1<u2 IF curricularYear(u1) < curricularYear(u2) OR same curricularYear and acronym(u1)<acronym(u2))
    
};

class MandatoryUnit : public Unit {
    int vacancies;
public:
    MandatoryUnit(); //default constructor
    MandatoryUnit(std::string name, std::string code, int ects, int year);//complete constructor
    
    /* 'get'-methods */
    int getVacancies();
    
    bool isVacant();
};

class OptionalUnit : public Unit {
    std::string scientificArea;
    //std::string institution; //Needed?
    //std::string course; //Needed?
public:
    OptionalUnit(); //default constructor
    /* add complete constructor */
    
    /* 'get'-methods */
    std::string getScientificArea();
    //std::string getInstitution();
    //std::string getCourse();
    
    bool isVacant(); //In this class, should always return true
};
