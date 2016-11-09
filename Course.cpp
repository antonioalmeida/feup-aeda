#include "Course.h"

//Source file for class Course, a class to handle a specific studies course

using namespace std;

Course::Course(string studentsFile, string teachersFile, string manUnitsFile, string optUnitsFile) {
	ifstream studentsIn, teachersIn, manUnitsIn, optUnitsIn;
	unsigned int numberOfStudents, numberOfTeachers, numberOfManUnits, numberOfOptUnits;

	/* Read mandatory units from respective file */
	manUnitsIn.open(manUnitsFile);
	manUnitsIn >> numberOfManUnits;
	manUnitsIn.ignore(1000, '\n');
	for (numberOfManUnits; numberOfManUnits > 0; numberOfManUnits--) {
		Unit* mu1 = new MandatoryUnit(manUnitsIn);
		abbreviationToUnit.insert(pair<string, Unit*>(mu1->getAbbreviation(), mu1));
		manUnitsIn.ignore(1000, '\n'); //Not sure but I think Unit constructor does not skip blank line between units
	}
	manUnitsIn.close(); //To avoid conflict

	/* Read optional units from respective file */
	optUnitsIn.open(optUnitsFile);
	optUnitsIn >> numberOfOptUnits;
	optUnitsIn.ignore(1000, '\n');
	for (numberOfOptUnits; numberOfOptUnits > 0; numberOfOptUnits--) {
		Unit* mu1 = new OptionalUnit(optUnitsIn);
		abbreviationToUnit.insert(pair<string, Unit*>(mu1->getAbbreviation(), mu1));
		optUnitsIn.ignore(1000, '\n'); //Not sure but I think Unit constructor does not skip blank line between units
	}
	optUnitsIn.close(); //To avoid conflict

	/* Read teachers from respective file */
	teachersIn.open(teachersFile);
	teachersIn >> numberOfTeachers;
	teachersIn.ignore(1000, '\n');
	for (numberOfTeachers; numberOfTeachers > 0; numberOfTeachers--) {
		Teacher t1(teachersIn);
		string abbreviation;
		while (teachersIn >> abbreviation)
			t1.addUnitTaught(abbreviationToUnit.find(abbreviation)->second);
		teachers.push_back(t1);
		teachersIn.ignore(1000, '\n'); //Not sure but I think Teacher constructor does not skip blank line between teachers
	}
	teachersIn.close(); //To avoid conflict

	/* Read students from respective file */
	studentsIn.open(studentsFile);
	studentsIn >> numberOfStudents;
	studentsIn.ignore(1000, '\n');
	for (numberOfStudents; numberOfStudents > 0; numberOfStudents--) {
		Student s1(studentsIn);
		string abbreviation;
		unsigned int grade;
		for (unsigned int i = 0; i < s1.getCurricularYear() - 1; i++) {
			while (studentsIn >> abbreviation) {
				Unit* u1 = abbreviationToUnit.find(abbreviation)->second;
				studentsIn >> grade;
				if (grade >= 10)
					s1.addUnitDone(pair<Unit*, unsigned int>(u1, grade));
				else //grade < 10
					s1.addUnitToDo(pair<Unit*, unsigned int>(u1, grade));
			}
		}
		students.push_back(s1);
		studentsIn.ignore(1000, '\n'); //Not sure but I think Student constructor does not skip blank line between students
	}
	studentsIn.close(); //To avoid conflict
}

vector<Student> Course::getStudents() const{
	return students;
}

vector<Teacher> Course::getTeachers() const {
	return teachers;
}

vector<Unit*> Course::getAllUnits() const {
	vector<Unit*> result;
	for (map<string, Unit*>::const_iterator it = abbreviationToUnit.begin(); it != abbreviationToUnit.end(); it++)
		result.push_back(it->second);

	return result;
}

vector<Unit*> Course::getUnitsFromYear(unsigned int curricularYear) const {
	vector<Unit*> result;
	for (map<string, Unit*>::const_iterator it = abbreviationToUnit.begin(); it != abbreviationToUnit.end(); it++) {
		if(it->second->getCurricularYear() == curricularYear)
			result.push_back(it->second);
	}

	return result;
}

vector<Unit*> Course::getOptUnitsFromYear(unsigned int curricularYear) const {
	vector<Unit*> result;
	for (map<string, Unit*>::const_iterator it = abbreviationToUnit.begin(); it != abbreviationToUnit.end(); it++) {
		if (it->second->getCurricularYear() == curricularYear && dynamic_cast<OptionalUnit*>(it->second) != NULL)
			result.push_back(it->second);
	}
	return result;
}

vector<Unit*> Course::getManUnitsFromYear(unsigned int curricularYear) const {
	if (curricularYear < 4)
		return getUnitsFromYear(curricularYear);
	vector<Unit*> result;
	for (map<string, Unit*>::const_iterator it = abbreviationToUnit.begin(); it != abbreviationToUnit.end(); it++) {
		if (it->second->getCurricularYear() == curricularYear && dynamic_cast<MandatoryUnit*>(it->second) != NULL)
			result.push_back(it->second);
	}
	return result;
}

vector<Unit*> Course::getUnitsFromSameScientificArea(Unit* u1) const {
	vector<Unit*> result;
	for (map<string, Unit*>::const_iterator it = abbreviationToUnit.begin(); it != abbreviationToUnit.end(); it++) {
		if (dynamic_cast<OptionalUnit*>(it->second) != NULL) {
			if (it->second->getScientificArea() == u1->getScientificArea() && !(it->second->isFull()))
				result.push_back(it->second);
		}
	}
	return result;
}