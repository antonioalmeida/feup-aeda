#pragma once
#include <string>
#include "Date.h"

//Header file for class Person and its derived classes (Student and Teacher, for now; to be implemented)

class Person {
protected:
    std::string name;
    Date birthDate;
    std::string code;
    std::string email; //created directly from code
public:
	Person() {}; //default constructor
    Person(std::string name, std::string code, Date birthDate); //basic constructor
    
    /* 'get' member-functions */
    Date getBirthDate() const;
    std::string getName() const;
    std::string getCode() const;
    std::string getEmail() const;
    
    /* 'set' member-functions (are they necessary though? maybe implement later on)
    void setBirthDate(Date newDate);
    void setEmail(string newEmail); //Unecessary? Since e-mail depends directly on the person's code
    void setName(string newName); //Useful?
	*/    
};

class Student : public Person {
    bool specialStatus; // Differentiate between athlete and worker?
    int ECTSNumber;
public:
	Student() {}; //default constructor
    Student(std::string name, Date birthDate, bool specialStatus);
    //vector<Unit> units; //Unit class needs to be defined
        
    /* 'get' member-functions */
    bool getSpecialStatus();
    int getECTSNumber();
    
     /* 'set' member-functions */
    void setSpecialStatus(bool newStatus);
    
    friend ostream& operator<<(ostream& out, const Student& s);
    friend istream& operator>>(istream& out, const Student& s);
};

class Teacher : public Person {
public:
	Teacher() {}; //default constructor
    //Teacher(string name, Date birthDate, vector<Unit> units); //Unit class needs to be defined
    //vector<Unit> units; //Unit class needs to be defined
    //vector<Student> pupils; //Another solution may be adopted (each Student has a Teacher* to their mentor)
    
    friend ostream& operator<<(ostream& out, const Teacher& s);
    friend istream& operator>>(istream& out, const Teacher& s);
};
