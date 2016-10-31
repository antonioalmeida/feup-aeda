#include "Person.h"

using namespace std;

/*Person*/

Person::Person(){}

Person::Person(string name, string code, Date birthDate)
{
	this->name = name;
	this->code = code;
	this->birthDate = birthDate;
	email = "up" + code + "@fe.up.pt";
}

Date Person::getBirthDate() const
{
	return birthDate;
}
string Person::getName() const 
{
	return name;
}
string Person::getCode() const 
{
	return code;
}
string Person::getEmail() const 
{
	return email;
}

void Person::setBirthDate(Date newDate)
{
	birthDate = newDate;
}
void Person::setEmail(string newEmail)
{
	email = newEmail;
}
void Person::setName(string newName)
{
	name = newName;
}

/*Student*/

Student::Student() {}

Student::Student(string name, string code, Date birthDate, bool specialStatus) : Person(name, code, birthDate)
{
	this->specialStatus = specialStatus;
	year = code.substr(0, 4); 
	
}

//vector<Unit> units; //Unit class needs to be defined


bool Student::getSpecialStatus()
{
	return specialStatus;
}

int Student::getECTSNumber()
{
	return ECTSNumber;
}

void Student::setSpecialStatus(bool newStatus)
{
	specialStatus = newStatus;
}

/*
ostream& Student::operator<<(std::ostream& out, const Student& s) 
{

}
istream& Student::operator>>(std::istream& out, const Student& s)
{

}

*/

/*Teacher*/
Teacher::Teacher() {}

/*
Teacher::Teacher(string name, string code, Date birthDate, vector<Unit> units) : Person(name,code,birthDate)
{
	this->units = units;
}

vector<Unit>Teacher:: getUnits
{
	return units;
}

vector<Student>Teacher:: getPupils
{
	return pupils;
}

ostream& Teacher::operator<<(std::ostream& out, const Teacher& s)
{
	return out;
}

istream& Teacher::operator>>(std::istream& in, const Teacher& s)
{
	return in;
}
*/