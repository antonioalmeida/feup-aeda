#include "StudentsClass.h"

using namespace std;

StudentsClass::StudentsClass(unsigned int newCurricularYear, vector<Unit*> unitsFromYear) {
    curricularYear = newCurricularYear;

    int i;
    for(i = 0; i < unitsFromYear.size(); i++) {
        vacanciesToUnits.push(pair<unsigned int,Unit*>(rand() % VACANCIES_VARIATION + MINIMUM_VACANCIES,unitsFromYear.at(i)));
    }

    code = to_string(curricularYear) + "MIEIC" + to_string(classesNumeration[curricularYear-1]);
    incClassesNumeration(curricularYear);
}

StudentsClass::StudentsClass(unsigned int newCurricularYear, string newCode) {
    curricularYear = newCurricularYear;
    code = newCode;
}

priority_queue<pair<unsigned long,Unit*>> StudentsClass::getVacanciesToUnits() const {
    return vacanciesToUnits;
}

int StudentsClass::getVacanciesFromUnit(Unit* unit) {
    priority_queue<pair<unsigned long,Unit*>> copy = vacanciesToUnits;

    while(!copy.empty()) {
        pair<unsigned long, Unit*> currentPair = copy.top();

        if(currentPair.second->getAbbreviation() == unit->getAbbreviation())
            return currentPair.first;

        copy.pop();
    }

    //Only reaches here is Unit is not in class
    return -1;
}

unsigned int StudentsClass::getCurricularYear() const {
    return curricularYear;
}

void StudentsClass::addPairToQueue(std::pair<unsigned long, Unit*> pair) {
    vacanciesToUnits.push(pair);
}

vector<unsigned int> StudentsClass::classesNumeration(5,1);

string StudentsClass::getCode() const {
    return code;
}

void StudentsClass::incClassesNumeration(unsigned int curricularYear) {
    classesNumeration.at(curricularYear-1)++;
}

bool StudentsClass::operator<(const StudentsClass &sc1) const {
    return this->vacanciesToUnits.top() > sc1.getVacanciesToUnits().top();
}

ostream& operator<<(std::ostream &out, const StudentsClass &sc1) {
    out << sc1.getCode() << " " << sc1.getCurricularYear() << "  " << sc1.getVacanciesToUnits().top().first << " " << sc1.getVacanciesToUnits().size();
    return out;
}

bool operator<(const pair<unsigned long, Unit*> &p1, const pair<unsigned long,Unit*> &p2) {
    return p1.first > p2.first;
}

std::ostream& operator<<(std::ostream &out, const pair<unsigned long,Unit*> &p1) {
    out << setw(7) << p1.second->getAbbreviation() << setw(5) << p1.first;
    return out;
}
