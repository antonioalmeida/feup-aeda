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
    
    /* 'set' member-functions (are they necessary though? maybe implement later on)*/
    void setBirthDate(Date newDate);
    void setEmail(std::string newEmail); //Unecessary? Since e-mail depends directly on the person's code
    void setName(std::string newName); //Useful?

	virtual void displayInfo() = 0;
	
};

class Student : public Person {
    bool specialStatus; // Differentiate between athlete and worker?
    int ECTSNumber;
	//vector<Unit> units; //Unit class needs to be defined
	std::string year; // class date??

public:
	Student() {}; //default constructor
    Student(std::string name, std::string code, Date birthDate, bool specialStatus);
        
    /* 'get' member-functions */
    bool getSpecialStatus();
    int getECTSNumber();
	// vector<Unit> getUnits();
    
     /* 'set' member-functions */
    void setSpecialStatus(bool newStatus);

	    
    friend std::ostream& operator<<(std::ostream& out, const Student& s);
    friend std::istream& operator>>(std::istream& in, const Student& s);
};

class Teacher : public Person {
	//vector<Unit> units; //Unit class needs to be defined
	//vector<Student> pupils; //Another solution may be adopted (each Student has a Teacher* to their mentor)
public:
	Teacher() {}; //default constructor
    //Teacher(std::string name, std::string code, Date birthDate, vector<Unit> units); //Unit class needs to be defined
    
    friend std::ostream& operator<<(std::ostream& out, const Teacher& s);
    friend std::istream& operator>>(std::istream& in, const Teacher& s);
};
