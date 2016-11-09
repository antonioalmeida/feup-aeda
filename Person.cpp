#include "Person.h"

using namespace std;

unsigned long int Student::nextCode = 201600000; //ID of first 1st timer to come! (Who wouldn't like to have this number?)

/*Person*/

Person::Person(istream &in) {
	getline(in, name);
}

Person::Person(string name) {
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

Student::Student(istream &in):Person(in) {
	in >> curricularYear;
	if (curricularYear > 1)
		in >> code;
	in.ignore(1000, '\n');
	getline(in, status);
	/* Units are read when read-from-files function is called! */
}

Student::Student(string name, string status, unsigned int curricularYear, vector<vector<pair<Unit*, unsigned int>>> unitsDone, vector<vector<pair<Unit*, unsigned int>>> unitsToDo, unsigned long int code = nextCode++) : Person(name) {
	this->status = status; //Can be anything
	this->curricularYear = curricularYear; //Use function readInteger from utils to guarantee valid curricularYear!
	this->code = code;
	/*
	if (curricularYear != 1) {
		//Check if code given as parameter already exists and throw exception if it does
	}
	Instead of this being here ^
	Verifications done in Course class respective function (where we have access to all data to compare)
	We test in a different way: parameter code is only inserted if curricularYear != 1 and if it already exists, throw exception using repeatedIdentification<unsigned long>*/
    
	email = "up" + to_string(code) + "@fe.up.pt";    
	ectsTaking = 0;
	this->unitsDone = unitsDone;
	this->unitsToDo = unitsToDo;
	if(curricularYear == 1)
		average = 0.0;
	else {
		double number_of_ects = 0.0;
		for (int i = 0; i < unitsDone.size(); i++) {
			for (int j = 0; j < unitsDone.at(i).size(); j++) {
				number_of_ects += unitsDone.at(i).at(j)->first->getECTS();
				average += unitsDone.at(i).at(j)->second;
			}
		}
		for (int i = 0; i < unitsToDo.size(); i++) {
			for (int j = 0; j < unitsToDo.at(i).size(); j++) {
				number_of_ects += unitsToDo.at(i).at(j)->first->getECTS();
				average += unitsToDo.at(i).at(j)->second;
			}
		}
		average /= number_of_ects;
	}
    registrationComplete = false;
}

string Student::getStatus() const {
	return status;
}

float Student::getECTSTaking() const {
	return ectsTaking;
}

unsigned long int Student::getCode() const {
	return code;
}

double Student::getAverage() const {
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

void Student::save(std::ostream &out) const{
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

ostream& operator<<(ostream& out, const Student& s) {
	/* To decide when implementing Course/Menus */
	return out;
}

/*Teacher*/

Teacher::Teacher(istream &in) {
	getline(in, name);
	getline(in, code);
	email = code + "@fe.up.pt";
	//Reads units after creating object (goes to the line and searches map for unit, adding it to the vector)
}

Teacher::Teacher(string name, string code, vector<Unit*> unitsTaught) : Person(name) {
	this->code = code;
	email = code + "@fe.up.pt";
	this->unitsTaught = unitsTaught;
}

string Teacher::getCode() const {
	return code;
}

void Teacher::addUnitTaught(Unit* newUnit) {
	unitsTaught.push_back(newUnit);
}

vector<Unit*> Teacher::getUnitsTaught() const{
	return unitsTaught;
}

void Teacher::addStudent(Student* newStudent) {
	pupils.push_back(newStudent);
}

vector<Student*> Teacher::getPupils() const {
	return pupils;
}

void Teacher::save(ostream &out) const{
	out << name << endl << code << endl;
	for (unsigned int i = 0; i < unitsTaught.size(); i++)
		out << unitsTaught.at(i)->getAbbreviation() << " ";
}

ostream& operator<<(ostream& out, const Teacher& s) { //Subject to change
	out << s.getName() << endl << "Teaches:" << endl;
	for (int i = 0; i < s.getUnitsTaught().size(); i++)
		cout << "- " << *(s.getUnitsTaught().at(i)) << endl;
	return out;
}
