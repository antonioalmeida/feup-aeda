#pragma once

#include <iostream>
#include <string>
#include <iomanip>

/*! \file Class that represents units taught in course */

class Unit {
protected:
	std::string name;
	std::string abbreviation;
	std::string scientificArea;
	float ECTS;
	unsigned int curricularYear;
public:
	//! Default class constructor (does nothing)
	/*!
	*/
	Unit() {};

	//! Class constructor used when reading units from file
	/*!
	\param in file where the unit will be read from
	*/
	Unit(std::istream &in);

	//! Gets a copy of the unit's name
	/*!
	\return copy of string data member name
	*/
	std::string getName() const;

	//! Gets a copy of the unit's abbreviation
	/*!
	\return copy of string data member abbreviation
	*/
	std::string getAbbreviation() const;

	//! Gets a copy of the unit's scientific area
	/*!
	\return copy of string data member scientific area
	*/
	std::string getScientificArea() const;

	//! Gets a copy of the unit's value, in ECTS
	/*!
	\return copy of float data member ECTS
	*/
	float getECTS() const;

	//! Gets a copy of the curricular year the unit is taught in
	/*!
	\return copy of unsigned int data member curricularYear
	*/
	unsigned int getCurricularYear() const;

	//! Determines if unit is full or not. Refer to derived classes reimplementations for more information
	/*!
	*/
	virtual bool isFull() const { return false; };

	//! Changes a unit's name
	/*!
	\param newName string corresponding to the unit's new name
	*/
	void setName(std::string newName);

	//! Changes a unit's abbreviation
	/*!
	\param newAbbreviation string corresponding to the unit's new abbreviation
	*/
	void setAbbreviation(std::string newAbbreviation);

	//! Changes a unit's scientific area
	/*!
	\param newScientificArea string corresponding to the unit's new scientific area
	*/
	void setScientificArea(std::string newScientificArea);

	//! Updates a unit's number of vacancies. Refer to derived classes reimplementations for more information
	/*!
	*/
	virtual void updateVacancies() {};

	//! Updates a unit's number of vacancies. Refer to derived classes reimplementations for more information
	/*!
	*/
	virtual void incrementVacancies() {};

	//! Auxiliar function used to print unit (called in operator<< overload)
	/*!
	\param out out stream where the unit will be printed to
	*/
	virtual void print(std::ostream &out) const {};

	//! Saves a unit to a text file
	/*!
	\param out file where the unit will be saved to
	*/
	virtual void save(std::ostream &out) const {};

	//! Overload of operator< to test inequalty between two units
	/*!
	\param u1 first of two units to be compared
	\param u2 second of two units to be compared
	\return true if u1 is from an inferior curricular year than u2 or, being from the same year, u1's abbreviation is alphabetically inferior, false otherwise
	*/
	friend bool operator<(const Unit &u1, const Unit &u2);

	//! Overload of operator<< to print unit on screen
	/*!
	\param out out stream where the unit will be printed to
	\param u1 unit that will be printed
	\return reference to out stream where the unit will be printed to
	*/
	friend std::ostream& operator<<(std::ostream &out, const Unit &u1);
};

/*! MandatoryUnit class (derived publicly from Unit)*/

class MandatoryUnit : public Unit {
public:
	//! Default constructor (does nothing)
	/*!
	*/
	MandatoryUnit() {};

	//! Class constructor used when reading units from file
	/*!
	\param in file where the unit will be read from
	*/
	MandatoryUnit(std::istream &in);

	//! Determines if the unit is full or not. Since it's a mandatory unit, it's never full (only here so polymorphism can be used)
	/*!
	\return false
	*/
	virtual bool isFull() const;

	//! Auxiliar function used to print unit (called in operator<< overload)
	/*!
	\param out out stream where the unit will be printed to
	*/
	virtual void print(std::ostream &out) const;

	//! Saves a unit to a text file
	/*!
	\param out file where the unit will be saved to
	*/
	virtual void save(std::ostream &out) const;

};

class OptionalUnit : public Unit {
protected:
	unsigned int fixedVacancies; //To keep track of unit's original vacancies value (so we can save it to the file when exiting)
	unsigned int vacancies;
public:
	//! Default constructor (does nothing)
	/*!
	*/
	OptionalUnit() {};

	//! Class constructor used when reading units from file
	/*!
	\param in file where the unit will be read from
	*/
	OptionalUnit(std::istream &in);

	//! Gets copy of unit's number of vacancies left
	/*!
	\return copy of unsigned int data member vacancies
	*/
	unsigned int getVacancies() const;

	//! Gets copy of unit's number of vacancies (fixed value)
	/*!
	\return copy of unsigned int data member fixedVacancies
	*/
	unsigned int getFixedVacancies() const;

	//! Decrements number of vacancies by one
	/*!
	*/
	virtual void updateVacancies();

	//! Increments number of vacancies by one
	/*!
	*/
	virtual void incrementVacancies();

	//! Determines if unit has vacancies left or not
	/*!
	\return true if unsigned int data member vacancies > 0, false otherwise
	*/
	virtual bool isFull() const;

	//! Auxiliar function used to print unit (called in operator<< overload)
	/*!
	\param out out stream where the unit will be printed to
	*/
	virtual void print(std::ostream &out) const;

	//! Saves a unit to a text file
	/*!
	\param out file where the unit will be saved to
	*/
	virtual void save(std::ostream &out) const;
};

//! Tests inequalty between pointers to units
/*!
\param u1 pointer to first of two units to be compared
\param u2 pointer to second of two units to be compared
\return true if unit pointed by u1 is from an inferior curricular year than unit pointed by u2 or, being from the same year, unit pointed by u1's abbreviation is alphabetically inferior, false otherwise
*/
bool compareUnitPointers(Unit* u1, Unit* u2);
