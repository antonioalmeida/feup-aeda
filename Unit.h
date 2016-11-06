#pragma once

#include <iostream>
#include <string>

//Header file for class Unit and its derived classes (MandatoryUnit and OptionalUnit, for now; to be implemented)

class Unit {
protected:
    std::string name;
    std::string abbreviation;
	std::string scientificArea;
    float ECTS;
    unsigned int curricularYear;
public:
	Unit() {}; //default constructor
    Unit(std::string name, std::string abbreviation, std::string scientificArea, float ects, unsigned int curricularYear);
      
    std::string getName() const;
    std::string getAbbreviation() const;
	std::string getScientificArea() const;
    float getECTS() const;
    unsigned int getCurricularYear() const;
    virtual bool notFull() const = 0; //Checks if curricular unit has a place for the student (always true in mandatory units)
    void setName(std::string newName);
    void setAbbreviation(std::string newAbbreviation);
	void setScientificArea(std::string newScientificArea);
    /*void setECTS(float newECTS); //Does it make sense? Considering we're using pointers in the Student/Teacher class, if we change the ECTS Value it may fuck up the amount of ECTS the student is taking*/
	virtual void print(std::ostream &out) const = 0; //Will be called in operator<< overload (kinda "forcing" polymorphism)
	virtual void save(std::ostream &out) const = 0;

    friend bool operator<(const Unit &u1, const Unit &u2); //u1 < u2 if curricularYear(u1) < curricularYear(u2) or if curricularYear is equal and abbreviation(u1) < abbreviation(u2)
	friend std::ostream& operator<<(std::ostream &out, const Unit &u1);
};

class MandatoryUnit : public Unit {
public:
	MandatoryUnit() {}; //default constructor
    MandatoryUnit(std::string name, std::string abbreviation, std::string scientificArea, float ects, unsigned int curricularYear);
    
    virtual bool notFull() const;
	virtual void print(std::ostream &out) const;
	virtual void save(std::ostream &out) const;

	friend std::istream& operator>>(std::istream &in, MandatoryUnit &u1);
};

class OptionalUnit : public Unit {
protected:
	const unsigned int fixedVacancies; //To keep track of original value and to not lose it (so we can save it to the file when exiting)
	unsigned int vacancies;
public:
	OptionalUnit() {};
	OptionalUnit(std::string name, std::string abbreviation, std::string scientificArea, float ects, unsigned int curricularYear, unsigned int fixedVacancies);

	unsigned int getVacancies() const;
	unsigned int getFixedVacancies() const;
	void updateVacancies();
	virtual bool notFull() const;
	virtual void print(std::ostream &out) const;
	virtual void save(std::ostream &out) const;

	friend std::istream& operator>>(std::istream &in, OptionalUnit &u1);
};
