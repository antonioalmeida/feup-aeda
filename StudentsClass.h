#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Date.h"
#include "Unit.h"


/*! \file StudentsClass.h
 \brief StudentsClass class
 */

class StudentsClass {
    std::map<std::string, unsigned int> abbreviationToVacancies;
    unsigned int curricularYear;
public:
    friend bool operator<(const StudentsClass &g1);
 }
