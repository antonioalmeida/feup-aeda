#pragma once

#include <iostream>
#include <string>

/*! Unit Class */

class Unit {
protected:
    std::string name;
    std::string abbreviation;
	std::string scientificArea;
    float ECTS;
    unsigned int curricularYear;
public:
	Unit() {}; // Default constructor
	Unit(std::ifstream &in); //!< Constructor that gets Unit information out of input file
      
    std::string getName() const; //!< Returns name
    std::string getAbbreviation() const; //!< Returns abbreviation
	std::string getScientificArea() const; //!< Returns scientificArea
    float getECTS() const; //!< Returns ECTS
    unsigned int getCurricularYear() const; //!< Returns curicularYear
    
	virtual bool isFull() const {}; //!< Checks if curricular unit has a place for the student (always false in MandatoryUnit)
    
    void setName(std::string newName); //!< Sets unit's name to newName
    void setAbbreviation(std::string newAbbreviation); //!< Sets unit's abbreviation to newAbbreviation
	void setScientificArea(std::string newScientificArea); //!< Sets unit's scientificArea to newScientificArea
    
	virtual void print(std::ostream &out) const {}; //!< Auxiliar funciton for indirect polymorphism. Will be called in operator << overload
	virtual void save(std::ostream &out) const {}; //!< Writes object to file

    friend bool operator<(const Unit &u1, const Unit &u2); //!< Overload of < operator to compare units. Returns true if curricularYear(u1) < curricularYear(u2) or if curricularYear is equal and abbreviation(u1) < abbreviation(u2)
	friend std::ostream& operator<<(std::ostream &out, const Unit &u1); //!< Overload of << operator so it can be sent to cout
};

class MandatoryUnit : public Unit {
public:
	MandatoryUnit() {}; // Default constructor
	MandatoryUnit(std::ifstream &in);
    
    virtual bool isFull() const;
	virtual void print(std::ostream &out) const;
	virtual void save(std::ostream &out) const;

};

class OptionalUnit : public Unit {
protected:
	unsigned int fixedVacancies; //!< To keep track of unit's original vacancies value (so we can save it to the file when exiting)
	unsigned int vacancies;
public:
	OptionalUnit() {}; // Default constructor
	OptionalUnit(std::ifstream &in);

	unsigned int getVacancies() const; //!< Returns vacancies
	unsigned int getFixedVacancies() const; //!< Returns fixedVacancies
    
	void updateVacancies(); //!< Decrements vacancies. Only run if isFull() returns false
   
	virtual bool isFull() const; //!< Checks if curricular unit has a place for the student
	virtual void print(std::ostream &out) const;
	virtual void save(std::ostream &out) const;
};
