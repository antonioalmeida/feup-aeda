#include "Unit.h"

//Source file for class Unit and its derived classes (MandatoryUnit and OptionalUnit)

using namespace std;

/* Base class Unit methods */

Unit::Unit(istream &in) {
	in >> abbreviation;
	getline(in, name);
	in >> curricularYear >> ECTS;
	in.ignore(1000, '\n');
	getline(in, scientificArea);
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

MandatoryUnit::MandatoryUnit(istream &in): Unit(in) {
}

bool MandatoryUnit::isFull() const {
	return false;
}

void MandatoryUnit::print(ostream &out) const { //May change display format later
	out << name << "(" << abbreviation << ")" << " - " << curricularYear;
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
	out << " year unit, worth " << ECTS << "ECTS. Scientific area - " << scientificArea;
}

void MandatoryUnit::save(ostream &out) const {
	out << abbreviation << " " << name << endl << curricularYear << " " << ECTS << endl << scientificArea;
}

/* Derived class OptionUnit methods */

OptionalUnit::OptionalUnit(istream &in):Unit(in) {
	in >> fixedVacancies;
	vacancies = fixedVacancies;
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

void OptionalUnit::incrementVacancies() {
	vacancies++;
}

bool OptionalUnit::isFull() const {
	return vacancies == 0;
}

void OptionalUnit::print(ostream &out) const {
	out << name << "(" << abbreviation << ") | " << curricularYear;
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
	out << " year unit, worth " << ECTS << "ECTS | Scientific area - " << scientificArea << " | Currently has " << vacancies << " places left";
}

void OptionalUnit::save(ostream &out) const {
	out << abbreviation << " " << name << endl << curricularYear << " " << ECTS << endl << scientificArea << endl << fixedVacancies;
}
