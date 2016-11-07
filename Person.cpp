#include "Person.h"

using namespace std;

unsigned long int Student::nextCode = 201600000; //ID of first 1st timer to come! (Who wouldn't like to have this number?)

/*Person*/

Person::Person(std::string name) {
	this->name = name;
}

string Person::getName() const {
	return name;
}

string Person::getEmail() const {
	return email;
}

void Person::setName(string newName) {
	name = newName;
}

/*Student*/

Student::Student(ifstream &in) {

}

Student::Student(string name, string status, unsigned int curricularYear, unsigned long int code = nextCode++) : Person(name) {
	this->status = status;
	this->curricularYear = curricularYear;
	if (curricularYear != 1) {
		/* Check if code given as parameter already exists and throw exception if it does */
	}
    
	email = "up" + to_string(code) + "@fe.up.pt";    
	ectsTaking = 0;
	if(curricularYear == 1)
		average = 0.0;
	else {
		/* Ask for units of previous years (acronyms only?) and respective grades */
	}
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

double getAverage() const {
	return average;
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
	out << name << endl << curricularYear;
	if (curricularYear > 1)
		out << " " << code;
	out << endl;
	for (int i = 0; i < unitsDone.size(); i++) {
		for (int j = 0; j < unitsDone.at(i).size(); j++) {
			out << unitsDone.at(i).at(j)->first->getAcronym() << " " << unitsDone.at(i).at(j)->second << " ";
		}
		if (i < unitsToDo.size()) { //unitsToDo.size() is always lower or equal than unitsDone.size() so it's a safe parallel test/loop
			for (int k = 0; k < unitsToDo.at(i).size(); k++)
				out << unitsToDo.at(i).at(k)->first->getAcronym() << " " << unitsDone.at(i).at(k)->second << " ";
		}
	}
}

ostream& Student::operator<<(ostream& out, const Student& s) {
	return out;
}

/*Teacher*/

Teacher::Teacher(ifstream &in) {
	getline(in, name);
	getline(in, code);
	email = code + "@fe.up.pt";
	//Reads units after creating object (goes to the line and searches map for unit, adding it to the vector)
}

Teacher::Teacher(string name, string code) : Person(name) {
	email = code + "@fe.up.pt";
	//Units same as Students (ask for acronyms only?)
}

string Teacher::getCode() const {
	return code;
}

void addUnitTaught(Unit* newUnit) {
	unitsTaught.push_back(newUnit);
}

vector<Unit> Teacher::getUnitsTaught const{
	return unitsTaught;
}

void Teacher::save(ostream &out) {
	out << name << endl << code << endl;
	for (unsigned int i = 0; i < unitsTaught.size(); i++)
		out << unitsTaught.at(i)->acronym << " ";
}

ostream& Teacher::operator<<(ostream& out, const Teacher& s) {
	return out;
}

istream& Teacher::operator>>(istream& in, const Teacher& s) {
	return in;
}
