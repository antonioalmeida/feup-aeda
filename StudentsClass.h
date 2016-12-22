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
    StudentsClass(unsigned int newCurricularYear, std::vector<Unit*> unitsFromYear);
    std::priority_queue<std::pair<unsigned long,Unit*>> getVacanciesToUnits() const;
    unsigned int getCurricularYear() const;
    std::string getCode() const;
    bool operator<(const StudentsClass &sc1) const;
    friend std::ostream& operator<<(std::ostream &out, const StudentsClass &sc1);

    static std::vector<unsigned int> classesNumeration;
    void incClassesNumeration(unsigned int curricularYear);
};

bool operator<(const std::pair<unsigned long, Unit*> &p1, const std::pair<unsigned long,Unit*> &p2);
std::ostream& operator<<(std::ostream &out, const std::pair<unsigned long,Unit*> &p1);
