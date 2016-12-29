#include "Person.h"

using namespace std;

unsigned long int Student::nextCode = 201600000; //ID of first 1st timer to come! (Who wouldn't like to have this number?)
unsigned int Teacher::lessStudents = 0;

/*Person*/

Person::Person(istream &in) {
	getline(in, name);
	deleteWhitespace(name);
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

void Person::setEmail(string newEmail) {
	email = newEmail;
}


/*Student*/

Student::Student(istream &in) :Person(in) {
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
	interrupted = false;
	completed = false;
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
	completed = false;
	interrupted = false;
}

unsigned long int Student::getCode() const {
	return code;
}

string Student::getStatus() const {
	return status;
}

float Student::getECTSTaking() const {
	return ectsTaking;
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
	unitsDone.at(index - 1).push_back(p);
	calculateAverage();
}

void Student::addUnitToDo(std::pair<Unit*, unsigned int> p) {
	int index = p.first->getCurricularYear();
	unitsToDo.at(index - 1).push_back(p);
	calculateAverage();
}

void Student::removeUnitToDo(Unit* u) {
	for (unsigned int i = 0; i < unitsToDo.at(u->getCurricularYear() - 1).size(); i++) {
		if (compareUnitPointers(u, unitsToDo.at(u->getCurricularYear() - 1).at(i).first))
			unitsToDo.at(u->getCurricularYear() - 1).erase(unitsToDo.at(u->getCurricularYear() - 1).begin() + i);
	}
}

void Student::addUnitTaking(Unit* u) {
	unitsTaking.push_back(u);
}

void Student::calculateAverage() {
	average = 0.0;
	if (curricularYear != 1) {
		double number_of_ects = 0.0;
		for (unsigned int i = 0; i < unitsDone.size(); i++) {
			for (unsigned int j = 0; j < unitsDone.at(i).size(); j++) {
				number_of_ects += unitsDone.at(i).at(j).first->getECTS();
				average += (unitsDone.at(i).at(j).second*unitsDone.at(i).at(j).first->getECTS());
			}
		}
		for (unsigned int i = 0; i < unitsToDo.size(); i++) {
			for (unsigned int j = 0; j < unitsToDo.at(i).size(); j++) {
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

void Student::setRegistrationDate(Date newDate) {
	registrationDate = newDate;
}

void Student::setECTSTaking(float newECTS) {
	ectsTaking = newECTS;
}

void Student::save(std::ostream &out) const {
	out << name << endl << curricularYear;
	if (curricularYear > 1)
		out << " " << code;
	out << endl;
	for (unsigned int i = 0; i < unitsDone.size(); i++) {
		for (unsigned int j = 0; j < unitsDone.at(i).size(); j++) {
			out << unitsDone.at(i).at(j).first->getAbbreviation() << " " << unitsDone.at(i).at(j).second << " ";
		}
		if (i < unitsToDo.size()) { //unitsToDo.size() is always equal than unitsDone.size() so it's a safe parallel test/loop
			for (unsigned int k = 0; k < unitsToDo.at(i).size(); k++)
				out << unitsToDo.at(i).at(k).first->getAbbreviation() << " " << unitsDone.at(i).at(k).second << " ";
		}
	}
	out << "|";
}

bool Student::operator==(const Student &s1) {
	return code == s1.getCode();
}

ostream& operator<<(ostream& out, const Student& s) {
	out << s.getCode();
	out << setw(32) << s.getName();
	out << setw(9) << s.getAverage();
	out << setw(7) << s.getECTSTaking();
	if (s.getUnitsTaking().size() != 0) {
		out << "  ";
		for (unsigned int i = 0; i < s.getUnitsTaking().size(); i++)
			out << s.getUnitsTaking().at(i)->getAbbreviation() << " ";
	}
	out << setw(19) << (s.getCompleted() ? "Completed" : "") << (s.getInterrupted() ? 	"Interrupted" : "")<< ((!s.getCompleted() && !s.getInterrupted()) ? "Active":"");

	out << endl;
	return out;
}

bool sortByName(Student s1, Student s2) {
	return s1.getName() < s2.getName();
}

bool sortByAverage(Student s1, Student s2) {
	return s1.getAverage() > s2.getAverage();
}

bool sortByCurricularYear(Student s1, Student s2) {
	return s1.getCurricularYear() < s2.getCurricularYear();
}

/*Reunion*/

Reunion::Reunion(Date date, string student, string agenda, string conclusions) {
	this->date = date;
	this->student = student;
	this->agenda = agenda;
	this->conclusions = conclusions;
	this->hasTakenPlace = false;
}

Date Reunion::getDate() const {
	return date;
}

string Reunion::getStudent() const {
	return student;
}

std::string Reunion::getAgenda() const {
	return agenda;
}

std::string Reunion::getConclusions() const {
	return conclusions;
}

bool Reunion::reunionHasTakenPlace() const {
	return hasTakenPlace;
}

void Reunion::setAsTaken() {
	this->hasTakenPlace = true;
}

void Reunion::changeConclusions(std::string newConclusions) {
	conclusions = newConclusions;
}

bool Reunion::operator==(const Reunion &r1) {
	return date == r1.getDate() && student == r1.getStudent() && agenda == r1.getAgenda() && conclusions == r1.getConclusions();
}

std::ostream& operator<<(std::ostream& out, const Reunion &r1) {
	out << "Student: " << r1.getStudent() << " | On " << r1.getDate() << endl;
	out << "Agenda: " << r1.getAgenda() << endl;
	out << "Conclusions: " << r1.getConclusions() << endl;
	return out;
}

/*Teacher*/

Teacher::Teacher(istream &in) :Person(in) {
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

vector<Unit*> Teacher::getUnitsTaught() const {
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

void Teacher::save(ostream &out) const {
	out << name << endl << code << endl;
	for (unsigned int i = 0; i < unitsTaught.size(); i++)
		out << unitsTaught.at(i)->getAbbreviation() << " ";
	out << "|";
}

ostream& operator<<(ostream& out, const Teacher& s) {
	out << setw(8) << s.getCode();
	out << setw(50) << s.getName();
	out << " ";
	for (unsigned int i = 0; i < s.getUnitsTaught().size(); i++)
		out << setw(6) << s.getUnitsTaught().at(i)->getAbbreviation() << " ";
	out << endl;
	return out;
}

set<Reunion, compareReunions> Teacher::getReunions() const {
	return reunions;
}

void Teacher::addReunion(Reunion r1) {
	reunions.insert(r1);
}

void Teacher::cancelSpecificReunion(Reunion r1) {
	reunions.erase(r1);
}

void Teacher::changeSpecificReunionConclusions(Reunion r1, string newConclusions) {
	Reunion temp = *reunions.find(r1);
	reunions.erase(r1);
	temp.changeConclusions(newConclusions);
	reunions.insert(temp);
}

void Teacher::setReunionAsTaken(Reunion r1) {
	Reunion temp = *reunions.find(r1);
	reunions.erase(r1);
	temp.setAsTaken();
	reunions.insert(temp);
}

bool sortTByName(Teacher t1, Teacher t2) {
	return t1.getName() < t2.getName();
}

//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
bool Student::getInterrupted() const {
	return interrupted;
}
bool Student::getCompleted() const {
	return completed;
}

void Student::setInterrupted() {
	interrupted = !interrupted;
}
void Student:: setCompleted() {
	completed = !completed;
}

//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
