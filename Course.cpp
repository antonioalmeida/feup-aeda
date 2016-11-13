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

std::vector<Unit*> Course::getAllMandatoryUnits() const {
	vector<Unit*> result;
	for (map<string, Unit*>::const_iterator it = abbreviationToUnit.begin(); it != abbreviationToUnit.end(); it++) {
		if(dynamic_cast<MandatoryUnit*>(it->second) != NULL)
			result.push_back(it->second);
	}
	return result;
}

std::vector<Unit*> Course::getAllOptionalUnits() const {
	vector<Unit*> result;
	for (map<string, Unit*>::const_iterator it = abbreviationToUnit.begin(); it != abbreviationToUnit.end(); it++) {
		if (dynamic_cast<OptionalUnit*>(it->second) != NULL)
			result.push_back(it->second);
	}
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

void Course::addStudent() {
	string newStudentName;
	cout << "Insert the new student's name: ";
	getline(cin, newStudentName);
	deleteWhitespace(newStudentName);
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getName() == newStudentName)
			throw repeatedIdentification<string>(newStudentName);
	}

	string newStudentStatus;
	cout << "Insert the new student's status: ";
	getline(cin, newStudentStatus);

	unsigned int newStudentCurricularYear;
	cout << "Insert the new student's curricular year: ";
	newStudentCurricularYear = readOp(1, 5);

	unsigned long newStudentCode;
	if (newStudentCurricularYear == 1) {
		cout << "Insert the new student's code: ";
		cin >> newStudentCode; //Verify for invalid input (later)
		for (int i = 0; i < students.size(); i++) {
			if (students.at(i).getCode() == newStudentCode)
				throw repeatedIdentification<unsigned long>(newStudentCode);
		}
	}

	vector<vector<pair<Unit*, unsigned int>>> newStudentUnitsDone(5);
	vector<vector<pair<Unit*, unsigned int>>> newStudentUnitsToDo(5);
	unsigned int grade; //Auxiliar variable that will store each grade obtained in units student has attended
	for (int i = 0; i < newStudentCurricularYear - 1; i++) {
		vector<Unit*> manUnitsFromCurrentYear = getManUnitsFromYear(i + 1);
		for (int j = 0; j < manUnitsFromCurrentYear.size(); j++) {
			cout << "Insert new student's final grade obtained at " << manUnitsFromCurrentYear.at(j)->getAbbreviation() << ": ";
			grade = readOp(0, 20);
			if (grade >= 10)
				newStudentUnitsDone.at(manUnitsFromCurrentYear.at(j)->getCurricularYear() - 1).push_back(pair<Unit*, unsigned int>(manUnitsFromCurrentYear.at(j), grade));
			else
				newStudentUnitsToDo.at(manUnitsFromCurrentYear.at(j)->getCurricularYear() - 1).push_back(pair<Unit*, unsigned int>(manUnitsFromCurrentYear.at(j), grade));
		}
		if (i == 3) { //4th curricular year, which includes optional units (TO DO LATER)
			vector<Unit*> optUnitsFromCurrentYear = getOptUnitsFromYear(i + 1);
			//Show optional units available
			for (int k = 0; k < optUnitsFromCurrentYear.size(); k++)
				cout << optUnitsFromCurrentYear.at(k) << endl;
			//COMPLETE...
		}
		if (i == 4) { //5th curricular year (should have ended studies but hasn't yet), which includes optinal units (TO DO LATER)
			vector<Unit*> optUnitsFromCurrentYear = getOptUnitsFromYear(i + 1);
			//Show optional units available
			for (int k = 0; k < optUnitsFromCurrentYear.size(); k++)
				cout << optUnitsFromCurrentYear.at(k) << endl;
			//COMPLETE...
		}
	}
	
	if (newStudentCurricularYear == 1)
		Student s(newStudentName, newStudentStatus, newStudentCurricularYear, newStudentUnitsDone, newStudentUnitsToDo);
	else
		Student s(newStudentName, newStudentStatus, newStudentCurricularYear, newStudentUnitsDone, newStudentUnitsToDo, newStudentCode);
}

void Course::removeStudent(unsigned long studentCode) {
	bool found = false;
	Student oldStudent;
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getCode() == studentCode) {
			found = true;
			vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();
			for (int j = 0; j < unitsTaking.size(); j++) { //Update vacancies of possible optional units he's taking
				if (dynamic_cast<OptionalUnit*>(unitsTaking.at(j)) != NULL)
					unitsTaking.at(j)->incrementVacancies();
			}
			oldStudent = students.at(i);
			students.erase(students.begin() + i);
			break;
		}
	}

	if (!found)
		throw invalidIdentification<unsigned long>(studentCode);

	for (int i = 0; i < teachers.size(); i++) //Remove student of his mentor's pupils vector (if he had one, otherwise this piece of code does nothing)
		teachers.at(i).removeStudent(oldStudent);
}

void Course::removeStudent(string studentName) {
	bool found = false;
	Student oldStudent;
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getName() == studentName) {
			found = true;
			vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();
			for (int j = 0; j < unitsTaking.size(); j++) { //Update vacancies of possible optional units he's taking
				if (dynamic_cast<OptionalUnit*>(unitsTaking.at(j)) != NULL)
					unitsTaking.at(j)->incrementVacancies();
			}
			oldStudent = students.at(i);
			students.erase(students.begin() + i);
			break;
		}
	}

	if (!found)
		throw invalidIdentification<string>(studentName);

	for (int i = 0; i < teachers.size(); i++) //Remove student of his mentor's pupils vector (if he had one, otherwise this piece of code does nothing)
		teachers.at(i).removeStudent(oldStudent);
}

void Course::showStudent(string studentName) const{
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getName() == studentName) {
			cout << students.at(i) << endl;
			return;
		}
	}
	throw invalidIdentification<string>(studentName);
}

void Course::showStudent(unsigned long int studentCode) const{
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getCode() == studentCode) {
			cout << students.at(i) << endl;
			return;
		}
	}
	throw invalidIdentification<unsigned long>(studentCode);
}

void Course::showStudents(bool(*comparisonFunction)(Student, Student)) const{
	vector<Student> studentsTemp = students;
	sort(studentsTemp.begin(), studentsTemp.end(), *comparisonFunction);
	for (int i = 0; i < studentsTemp.size(); i++)
		cout << studentsTemp.at(i) << endl;
	cout << endl;
}

void Course::showStudentsStatus(string status) const {
	vector<Student> studentsToShow;
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getStatus() == status)
			studentsToShow.push_back(students.at(i));
	}
	sort(studentsToShow.begin(), studentsToShow.end(), sortByName);
	for (int i = 0; i < studentsToShow.size(); i++)
		cout << studentsToShow.at(i) << endl;
	cout << endl;
}

void Course::showRegisteredStudents() const {
	vector<Student> studentsToShow;
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).isRegistered())
			studentsToShow.push_back(students.at(i));
	}
	sort(studentsToShow.begin(), studentsToShow.end(), sortByName);
	for (int i = 0; i < studentsToShow.size(); i++)
		cout << studentsToShow.at(i) << endl;
	cout << endl;
}

void Course::showUnregisteredStudents() const {
	vector<Student> studentsToShow;
	for (int i = 0; i < students.size(); i++) {
		if (!students.at(i).isRegistered())
			studentsToShow.push_back(students.at(i));
	}
	sort(studentsToShow.begin(), studentsToShow.end(), sortByName);
	for (int i = 0; i < studentsToShow.size(); i++)
		cout << studentsToShow.at(i) << endl;
	cout << endl;
}

void Course::showUnitRegistrations() const {
	string unitToShow;
	cout << "Insert the unit's abbreviation: ";
	getline(cin, unitToShow);
	deleteWhitespace(unitToShow);
	map<string, Unit*>::const_iterator it = abbreviationToUnit.find(unitToShow);
	if (it == abbreviationToUnit.end()) //Not found
		throw invalidIdentification<string>(unitToShow);

	vector<Student> result;
	for (int i = 0; i < students.size(); i++) {
		for (int j = 0; j < students.at(i).getUnitsTaking().size(); j++) {
			if (students.at(i).getUnitsTaking().at(j)->getAbbreviation() == unitToShow) {
				result.push_back(students.at(i));
				break;
			}
		}
	}

	sort(result.begin(), result.end(), sortByName);
	for (int i = 0; i < result.size(); i++)
		cout << result.at(i) << endl;
	cout << endl;
}


//Teachers


void Course::removeTeacher(string teacherName) {
	bool found = false;
	for (int i = 0; i < teachers.size(); i++) {
		if (teachers.at(i).getName() == teacherName) {
			found = true;
			//it's necessary update global variable lessStudents?
			teachers.erase(teachers.begin() + i);
			break;
		}
	}

	if (!found)
		throw invalidIdentification<string>(teacherName);
}

void Course::removeTeacher(unsigned long teacherCode) {
	bool found = false;
	for (int i = 0; i < teachers.size(); i++) {
		if (teachers.at(i).getCode() == teacherCode) {
			found = true;
			//it's necessary update global variable lessStudents?
			teachers.erase(teachers.begin() + i);
			break;
		}
	}

	if (!found)
		throw invalidIdentification<unsigned long>(teacherCode);
}

void Course::showTeachers(bool(*comparisonFunction)(Teacher, Teacher)) const {
	vector<Teacher> teachersTemp =teachers;
	sort(teachersTemp.begin(), teachersTemp.end(), *comparisonFunction);
	for (int i = 0; i < teachersTemp.size(); i++)
		cout << teachersTemp.at(i) << endl;
	cout << endl;
}

void Course::showTeacher(string teacherName) const {
	for (int i = 0; i < teachers.size(); i++) {
		if (teachers.at(i).getName() == teacherName) {
			cout << teachers.at(i) << endl;
			return;
		}
	}
	throw invalidIdentification<string>(teacherName);
}

void Course::showTeacher(unsigned long int teacherCode) const {
	for (int i = 0; i < teachers.size(); i++) {
		if (teachers.at(i).getCode() == teacherCode) {
			cout << teachers.at(i) << endl;
			return;
		}
	}
	throw invalidIdentification<unsigned long>(teacherCode);
}

void Course::showTeacher(string unitAbreviation) const {
	for (int i = 0; i < teachers.size(); i++) {
		vector<Unit*> unitsTaughtTemp = teachers.at(i).getUnitsTaught();
		for (vector<Unit*>::iterator it = unitsTaughtTemp.begin(); it != unitsTaughtTemp.end(); it++) {
			if ((*it)->getAbbreviation() == unitAbreviation) {
				cout << teachers.at(i) << endl;
				return;
			}
		}
	}
	throw invalidIdentification<string>(unitAbreviation);
}

void Course::showTeacherPupil(string pupilName) const {
	for (int i = 0; i < teachers.size(); i++) {
		vector<Student*> pupilsTemp = teachers.at(i).getPupils();
		for (vector<Student*>::iterator it = pupilsTemp.begin(); it != pupilsTemp.end(); it++) {
			if ((*it)->getName() == pupilName) {
				cout << teachers.at(i) << endl;
				return;
			}
		}
	}
	throw invalidIdentification<string>(pupilName);
}

void Course::showTeacherPupil(unsigned long int pupilCode) const {
	for (int i = 0; i < teachers.size(); i++) {
		vector<Student*> pupilsTemp = teachers.at(i).getPupils();
		for (vector<Student*>::iterator it = pupilsTemp.begin(); it != pupilsTemp.end(); it++) {
			if ((*it)->getCode() == pupilCode) {
				cout << teachers.at(i) << endl;
				return;
			}
		}
	}
	throw invalidIdentification<unsigned long>(pupilCode);
}

//Units

void Course::showUnits() const {
	vector<Unit*> unitTemp= getAllUnits();

	sort(unitTemp.begin(), unitTemp.end());

	for (int i = 0; i < unitTemp.size(); i++)
		cout << *unitTemp.at(i) << endl;
	cout << endl;
}

void Course::showYearUnit(unsigned short int year) const {
	vector<Unit*> unitTemp = getUnitsFromYear(year);

	sort(unitTemp.begin(), unitTemp.end());
	
	for (int i = 0; i < unitTemp.size();i++)
		cout << *unitTemp.at(i) << endl;
	cout << endl;
}

void Course::showMandatoryUnit() const {
	vector<Unit*> unitTemp = getAllMandatoryUnits();
	
	sort(unitTemp.begin(), unitTemp.end());

	for (int i = 0; i < unitTemp.size(); i++)
		cout << *unitTemp.at(i) << endl;
	cout << endl;
}

void Course::showOptionalUnit() const {
	vector<Unit*> unitTemp = getAllOptionalUnits();

	sort(unitTemp.begin(), unitTemp.end());

	for (int i = 0; i < unitTemp.size(); i++)
		cout << *unitTemp.at(i) << endl;
	cout << endl;
}



//Save
void Course::save() const {
	string studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName;

	cout << "Insert the filename where mandatory units will be saved: ";
	getline(cin, mandatoryUnitsFileName);
	ofstream mandatoryUnitsOut(mandatoryUnitsFileName);
	vector<Unit*> manUnits = getAllMandatoryUnits();
	mandatoryUnitsOut << manUnits.size() << endl;
	for (int i = 0; i < manUnits.size(); i++) {
		manUnits.at(i)->save(mandatoryUnitsOut);
		mandatoryUnitsOut << endl << endl;
	}
	mandatoryUnitsOut.close();

	cout << "Insert the filename where optional units will be saved: ";
	getline(cin, optionalUnitsFileName);
	ofstream optionalUnitsOut(optionalUnitsFileName);
	vector<Unit*> optUnits = getAllOptionalUnits();
	optionalUnitsOut << optUnits.size() << endl;
	for (int i = 0; i < optUnits.size(); i++) {
		optUnits.at(i)->save(optionalUnitsOut);
		optionalUnitsOut << endl << endl;
	}
	optionalUnitsOut.close();

	cout << "Insert the filename where students will be saved: ";
	getline(cin, studentsFileName);
	ofstream studentsOut(studentsFileName);
	studentsOut << students.size() << endl;
	for (int i = 0; i < students.size(); i++) {
		students.at(i).save(studentsOut);
		studentsOut << endl << endl;
	}
	studentsOut.close();

	cout << "Insert the filename where teachers will be saved: ";
	getline(cin, teachersFileName);
	ofstream teachersOut(teachersFileName);
	studentsOut << teachers.size() << endl;
	for (int i = 0; i < teachers.size(); i++) {
		teachers.at(i).save(teachersOut);
		teachersOut << endl << endl;
	}
	teachersOut.close();
}

bool Course::verifyUnit(string unitAbbreviation) const {
    map<string, Unit*>::const_iterator it = abbreviationToUnit.find(unitAbbreviation);
    
    if(it != abbreviationToUnit.end())
        return true;
    
    return false;
}
