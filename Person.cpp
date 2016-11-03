#include "Person.h"

using namespace std;

unsigned long int Student::nextCode = 201600000; //ID of first 1st timer to come! (Who wouldn't like to have this number?)

/*Person*/

Person::Person(std::string name, Date birthDate) {
	this->name = name;
	this->birthDate = birthDate;
}

Date Person::getBirthDate() const {
	return birthDate;
}

string Person::getName() const {
	return name;
}

string Person::getEmail() const {
	return email;
}

void Person::setBirthDate(Date newDate) {
	birthDate = newDate;
}

void Person::setName(string newName) {
	name = newName;
}

/*Student*/

Student::Student(string name, Date birthDate,string specialStatus, unsigned int curricularYear, unsigned long int code = nextCode++) : Person(name, birthDate) {
    
	status = specialStatus;
	this->curricularYear = curricularYear;
    
    if(code != nextCode) {
        /*
         if(curricularYear < 2)
            throw InvalidCurricularYear(curricularYear);
         */
        this->code = code;
    }
    
    email = "up";
    email.append(to_string(code));
    email.append("@fe.up.pt");
    
	ectsTaking = 0;
	average = 0.0;
	mentor = NULL;
    
    registrationComplete = false;
}

string Student::getStatus() const {
	return status;
}

unsigned int Student::getECTSTaking() const {
	return ectsTaking;
}

unsigned long int Student::getCode() const {
	return code;
}

vector<vector<pair<Unit*, unsigned int>>> Student::getUnitsDone() const {
	return unitsDone;
}

vector<vector<pair<Unit*, unsigned int>>> Student::getUnitsToDo() const {
	return unitsToDo;
}

vector<Unit*> Student::getUnitsTaking() const {
	return unitsTaking;
}

Teacher* Student::getMentor() const {
	return mentor;
}

Date Student::getRegistrationDate() const {
	return registrationDate;
}

bool Student::isRegistered() const {
	return registrationComplete;
}

void Student::setRegistration() {
	registrationComplete = !registrationComplete;
}

void Student::setStatus(string newStatus) {
	status = newStatus;
}

void Student::setMentor(Teacher* newMentor) {
	mentor = newMentor;
}

void Student::save(std::ostream &out) {

}

ostream& Student::operator<<(ostream& out, const Student& s) {
	return out;
}

istream&Student:: operator>>(istream& in, Student& s) {
	return in;
}

/*Teacher*/

Teacher::Teacher(string name, string code, Date birthDate) : Person(name, birthDate) {
	email = code + "@fe.up.pt";
	//Units same as Students
}

string Teacher::getCode() const {
	return code;
}

vector<Unit> Teacher::getUnitsTaught const{
return unitsTaught;
}

void Teacher::save(ostream &out) {

}

ostream& Teacher::operator<<(ostream& out, const Teacher& s) {
	return out;
}

istream& Teacher::operator>>(istream& in, const Teacher& s) {
	return in;
}
