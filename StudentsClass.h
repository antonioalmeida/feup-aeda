#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <queue>
#include "Date.h"
#include "Unit.h"

#define VACANCIES_VARIATION 10
#define MINIMUM_VACANCIES 20

/*! \file StudentsClass.h
 \brief StudentsClass class
 */

class StudentsClass {

    std::priority_queue<std::pair<unsigned long,Unit*>> vacanciesToUnits;
    unsigned int curricularYear;
    std::string code;
public:

    //! Class constructor used when adding a new StudentsClass to the course structure. Generates the code automatically based on curricular year and classesNumeration
    /*!
    \param newCurricularYear the class' curricular year
    \param unitsFromYear the units the class will have
    */
    StudentsClass(unsigned int newCurricularYear, std::vector<Unit*> unitsFromYear);

    //! Class constructor used when creating a StudentsClass whose code was already used before. Useful in auxiliary methods to create temporary objects.
    /*!
    \param newCurricularYear the class' curricular year
    \param code the class' code
    */
    StudentsClass(unsigned int newCurricularYear, std::string code);

    //! Gets a copy of the class' vacanciesToUnits queue
    /*!
    \return copy of vacanciestoUnits
    */
    std::priority_queue<std::pair<unsigned long,Unit*>> getVacanciesToUnits() const;

    //! Gets a copy of a unit's vacancies in the class' vacanciesToUnits queue
    /*!
    \return the unit's vacancies. returns -1 if the unit is not in vacanciesToUnits
    */
    int getVacanciesFromUnit(Unit* unit);

    //! Gets a copy of the class' curricularYear
    /*!
    \return int with a copy of the class' curricularYear
    */
    unsigned int getCurricularYear() const;

    //! Gets a copy of the class' code
    /*!
    \return string with a copy the class' code
    */
    std::string getCode() const;

    //! Inserts a pair in the class' vacanciesToUnits queue
    /*!
    \param pair pair to be inserted in vacanciesToUnits
    */
    void addPairToQueue(std::pair<unsigned long, Unit*> pair);

    //! Overload of operator< to determine relative position in the course's priority queue
	/*!
	\param sc1 rhs of the operation
	\return true if the top pair in vacanciesToUnits has more vacancies than sc1's top pair, false otherwise
	*/
    bool operator<(const StudentsClass &sc1) const;

    //! Overload of operator<< to print StudentsClass on screen
    /*!
    \param out out stream where the class will be printed to
    \param sc1 StudentsClass that will be printed
    \return reference to out stream where the StudentsClass will be printed to
    */
    friend std::ostream& operator<<(std::ostream &out, const StudentsClass &sc1);

    //! Vector whose elements correspond to the last created class' numerical part of the code. Off by one value - example classesNumeration[0] is the numerical part of the last created class' code of curricularYear == 1
    /*!
    */
    static std::vector<unsigned int> classesNumeration;

    //! Increments classesNumeration at curricular-1;
    /*!
    \param curricularYear curricular year that determines which index is incremented
    */
    void incClassesNumeration(unsigned int curricularYear);
};

//! Overload of operator< to determine relative positions of pairs in the vacanciesToUnits priority queue
/*!
\param sc1 rhs of the operation
\return true if the this.first (vacancies) > sc1.first
*/
bool operator<(const std::pair<unsigned long, Unit*> &p1, const std::pair<unsigned long,Unit*> &p2);

//! Overload of operator<< to print <vacancies,Unit*> pairs on screen. Prints the unit's abbreviation followed by its vacancies
/*!
\param out out stream where the pair will be printed to
\param p1 pair that will be printed
\return reference to out stream where the pair will be printed to
*/
std::ostream& operator<<(std::ostream &out, const std::pair<unsigned long,Unit*> &p1);
