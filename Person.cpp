#include "Person.h"

using namespace std;

unsigned long int Student::nextCode = 201600000; //ID of first 1st timer to come! (Who wouldn't like to have this number?)
unsigned int Teacher::lessStudents = 0;

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
	else
		code = Student::nextCode++;
	in.ignore(1000, '\n');
	getline(in, status);
	unitsDone = vector<vector<pair<Unit*, unsigned int>>>(5);
	unitsToDo = vector<vector<pair<Unit*, unsigned int>>>(5);
	email = "up" + to_string(code) + "@fe.up.pt";
	ectsTaking = 0;
	registrationComplete = false;
	/* Units are read when read-from-files function is called! */
}

Student::Student(string name, string status, unsigned int curricularYear, vector<vector<pair<Unit*, unsigned int>>> unitsDone, vector<vector<pair<Unit*, unsigned int>>> unitsToDo, unsigned long int code) : Person(name) {
	this->status = status; //Can be anything
	this->curricularYear = curricularYear;
	this->code = code;
   
	email = "up" + to_string(code) + "@fe.up.pt";    
	ectsTaking = 0;
	this->unitsDone = unitsDone;
	this->unitsToDo = unitsToDo;
	calculateAverage();
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

unsigned int Student::getCurricularYear() const {
	return curricularYear;
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

void Student::addUnitDone(std::pair<Unit*, unsigned int> p) {
	int index = p.first->getCurricularYear();
	unitsDone.at(index-1).push_back(p);
	calculateAverage();
}

void Student::addUnitToDo(std::pair<Unit*, unsigned int> p) {
	int index = p.first->getCurricularYear();
	unitsToDo.at(index - 1).push_back(p);
	calculateAverage();
}

void Student::addUnitTaking(Unit* u) {
	if (ectsTaking + u->getECTS() > MAX_ECTS)
		throw tooManyECTS();
	unitsTaking.push_back(u);
}

void Student::calculateAverage() {
	average = 0.0;
	if(curricularYear != 1){
		double number_of_ects = 0.0;
		for (int i = 0; i < unitsDone.size(); i++) {
			for (int j = 0; j < unitsDone.at(i).size(); j++) {
				number_of_ects += unitsDone.at(i).at(j).first->getECTS();
				average += (unitsDone.at(i).at(j).second*unitsDone.at(i).at(j).first->getECTS());
			}
		}
		for (int i = 0; i < unitsToDo.size(); i++) {
			for (int j = 0; j < unitsToDo.at(i).size(); j++) {
				number_of_ects += unitsToDo.at(i).at(j).first->getECTS();
				average += (unitsToDo.at(i).at(j).second*unitsToDo.at(i).at(j).first->getECTS());
			}
		}
		average /= number_of_ects;
	}
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
			out << unitsDone.at(i).at(j).first->getAbbreviation() << " " << unitsDone.at(i).at(j).second << " ";
		}
		if (i < unitsToDo.size()) { //unitsToDo.size() is always lower or equal than unitsDone.size() so it's a safe parallel test/loop
			for (int k = 0; k < unitsToDo.at(i).size(); k++)
				out << unitsToDo.at(i).at(k).first->getAbbreviation() << " " << unitsDone.at(i).at(k).second << " ";
		}
	}
	out << "|";
}

bool Student::operator==(const Student &s1) {
	return code == s1.getCode();
}

ostream& operator<<(ostream& out, const Student& s) {
	out << s.getName() << " | " << s.getCode() << " | Current Average: " << s.getAverage();
	if (s.getUnitsTaking().size() != 0) {
		out << " | Taking: ";
		for (int i = 0; i < s.getUnitsTaking().size(); i++)
			out << s.getUnitsTaking().at(i)->getAbbreviation() << " ";
	}
	out << endl;
	return out;
}

bool sortByName(Student s1, Student s2) {
	return s1.name < s2.name;
}

bool sortByAverage(Student s1, Student s2) {
	return s1.average < s2.average;
}

bool sortByCurricularYear(Student s1, Student s2) {
	return s1.curricularYear < s2.curricularYear;
}

/*Teacher*/

Teacher::Teacher(istream &in):Person(in) {
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

void Teacher::setCode(std::string newCode) {
	code = newCode;
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

void Teacher::removeStudent(Student oldStudent) {
	for (vector<Student*>::iterator it = pupils.begin(); it != pupils.end(); it++) {
		if (**it == oldStudent) {
			pupils.erase(it);
			break;
		}
	}
	if (pupils.size() < Teacher::lessStudents)
		Teacher::lessStudents = pupils.size();
}

vector<Student*> Teacher::getPupils() const {
	return pupils;
}

void Teacher::save(ostream &out) const{
	out << name << endl << code << endl;
	for (unsigned int i = 0; i < unitsTaught.size(); i++)
		out << unitsTaught.at(i)->getAbbreviation() << " ";
	out << "|";
}

ostream& operator<<(ostream& out, const Teacher& s) { //Subject to change
	out << s.getName() << "(" << s.getCode() << ")" << "| Teaches:";
	for (int i = 0; i < s.getUnitsTaught().size(); i++)
		out << s.getUnitsTaught().at(i)->getAbbreviation() << " ";
	out << endl;
	return out;
}

bool sortTByName(Teacher t1, Teacher t2) {
	return t1.name < t2.name;
}