#include "Unit.h"

//Source file for class Unit and its derived classes (MandatoryUnit and OptionalUnit, for now; to be implemented)

using namespace std;

/* Base class Unit methods */

Unit::Unit(string name, string abbreviation, string scientificArea, unsigned int ects, unsigned int curricularYear) {
	this->name = name;
	this->abbreviation = abbreviation;
	this->scientificArea = scientificArea;
	ECTS = ects;
	this->curricularYear = curricularYear;
	/*MISSING: Exception handling*/
}

string Unit::getName() const {
	return name;
}

string Unit::getAbbreviation() const {
	return abbreviation;
}

string Unit::getScientificArea() const {
	return scientificArea;
}

float Unit::getECTS() const {
	return ECTS;
}

unsigned int Unit::getCurricularYear() const {
	return curricularYear;
}

void Unit::setName(string newName) {
	name = newName;
}

void Unit::setAbbreviation(string newAbbreviation) {
	abbreviation = newAbbreviation;
}

void Unit::setScientificArea(string newScientificArea) {
	scientificArea = newScientificArea;
}

bool operator<(const Unit &u1, const Unit &u2) {
	return (u1.getCurricularYear() < u2.getCurricularYear() || (u1.getCurricularYear() == u2.getCurricularYear() && u1.getAbbreviation() < u2.getAbbreviation()));
}

ostream& operator<<(ostream &out, const Unit &u1) {
	u1.print(out);
	return out;
}

/* Derived class MandatoryUnit methods */

MandatoryUnit::MandatoryUnit(string name, string abbreviation, string scientificArea, float ects, unsigned int curricularYear): Unit(name,abbreviation,scientificArea,ects,curricularYear) {
}

bool MandatoryUnit::isFull() const {
	return false;
}

void MandatoryUnit::print(ostream &out) const { //May change display format later
	out << name << "(" << abbreviation << ")" << endl << curricularYear;
	switch (curricularYear) {
	case 1:
		out << "st ";
		break;
	case 2:
		out << "nd ";
		break;
	case 3:
		out << "rd ";
		break;
	default:
		out << "th ";
		break;
	}
	out << " year unit, worth " << ECTS << "ECTS" << endl << "Scientific area - " << scientificArea;
}

void MandatoryUnit::save(ostream &out) const {
	out << abbreviation << " " << name << endl << curricularYear << " " << ECTS << endl << scientificArea;
}

istream& operator >> (istream &in, MandatoryUnit &u1) {
	in >> u1.abbreviation;
	getline(in, u1.name);
	in >> u1.curricularYear >> u1.ECTS;
	in.ignore(1000, '\n'); //Ignore any elements left in current line (should only be newline)
	getline(in, u1.scientificArea);
	return in;
}

/* Derived class OptionUnit methods */

OptionalUnit::OptionalUnit(string name, string abbreviation, string scientificArea, float ects, unsigned int curricularYear, unsigned int fixedVacancies) : Unit(name, abbreviation, scientificArea, ects, curricularYear), fixedVacancies(fixedVacancies) {
	//No exception handling needed (about the new member, (fixed)Vacancies), I think...
}

unsigned int OptionalUnit::getVacancies() const {
	return vacancies;
}

unsigned int OptionalUnit::getFixedVacancies() const {
	return fixedVacancies;
}

void OptionalUnit::updateVacancies() {
	vacancies--; //No need to check if it is already 0 if we make sure it isn't called unless isFull() returns false
}

bool OptionalUnit::isFull() const {
	return vacancies == 0;
}

void OptionalUnit::print(ostream &out) const {
	out << name << "(" << abbreviation << ")" << endl << curricularYear;
	switch (curricularYear) {
	case 1:
		out << "st ";
		break;
	case 2:
		out << "nd ";
		break;
	case 3:
		out << "rd ";
		break;
	default:
		out << "th ";
		break;
	}
	out << " year unit, worth " << ECTS << "ECTS" << endl << "Scientific area - " << scientificArea << endl << "Total of " << fixedVacancies << "vacancies, currently has place for " << vacancies << " students" << endl;
}

void OptionalUnit::save(ostream &out) const {
	out << abbreviation << " " << name << endl << curricularYear << " " << ECTS << endl << scientificArea << endl << vacancies;
}

istream& operator>>(istream &in, OptionalUnit &u1) {
	in >> u1.abbreviation;
	getline(in, u1.name);
	in >> u1.curricularYear >> u1.ECTS;
	in.ignore(1000, '\n'); //Ignore any elements left in current line (should only be newline)
	getline(in, u1.scientificArea);
	in >> u1.vacancies;
	in.ignore(1000, '\n');
	return in;
}
