#pragma once
#include <string>
#include "Date.h"
using namespace std;
//Header file for class Person and its derived classes (Student and Teacher, for now; to be implemented)

class Person {
    string name;
    Date birthDate;
    string code;
    string email; //created directly from email?
public:
    Person(); //default constructor
    Person(string name, Date birthDate); //basic constructor
    
    /* 'get' member-functions */
    int getBirthDate();
    int getName();
    string getCode();
    string getEmail();
    
    /* 'set' member-functions */
    void setBirthDate(Date newDate);
    void setEmail(string newEmail);
    void setName(string newName); //Useful?
    
    virtual void show() = 0; //Makes class purely virtual
    
};

class Student : public Person {
    bool specialStatus; // Differentiate between athlete and worker?
    int ECTSNumber;
public:
    Student(); //default constructor
    Student(string name, Date birthDate, bool specialStatus);
    //vector<Unit> units; //Unit class needs to be defined
    void show();
    
    /* 'get' member-functions */
    bool getSpecialStatus();
    int getECTSNumber();
    
     /* 'set' member-functions */
    void setSpcialStatus(bool newStatus);
    void setECTSNumber(int newECTSNumber);
    
    friend ostream& operator<<(ostream& out, const Student& s);
    friend istream& operator>>(istream& out, const Student& s);
};

class Teacher : public Person {
public:
    Teacher(); //default constructor
    //Teacher(string name, Date birthDate, vector<Unit> units); //Unit class needs to be defined
    //vector<Unit> units; //Unit class needs to be defined
    vector<Student> pupils;
    
    friend ostream& operator<<(ostream& out, const Student& s);
    friend istream& operator>>(istream& out, const Student& s);
};
