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
		while (teachersIn >> abbreviation) {
			if (abbreviation == "|")
				break;
			t1.addUnitTaught(abbreviationToUnit.find(abbreviation)->second);
		}
		teachers.push_back(t1);
		teachersIn.ignore(1000, '\n');
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
		while (studentsIn >> abbreviation) {
			if (abbreviation == "|")
				break;
			Unit* u1 = abbreviationToUnit.find(abbreviation)->second;
			studentsIn >> grade;
			if (grade >= 10)
				s1.addUnitDone(pair<Unit*, unsigned int>(u1, grade));
			else //grade < 10
				s1.addUnitToDo(pair<Unit*, unsigned int>(u1, grade));
		}
		students.push_back(s1);
		studentsIn.ignore(1000, '\n');
		studentsIn.ignore(1000, '\n'); //Not sure but I think Student constructor does not skip blank line between students
	}
	studentsIn.close(); //To avoid conflict
}

vector<Student> Course::getStudents() const {
	return students;
}

vector<Teacher> Course::getTeachers() const {
	return teachers;
}

std::map<std::string, Unit*> Course::getMap() const {
	return abbreviationToUnit;
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
		if (dynamic_cast<MandatoryUnit*>(it->second) != NULL)
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
		if (it->second->getCurricularYear() == curricularYear)
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
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
	if (newStudentCurricularYear > 1) {
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
		if (i == 3) { //4th curricular year, which includes optional units
			vector<Unit*> optUnitsFromCurrentYear = getOptUnitsFromYear(i + 1);
			//Show optional units available
			cout << endl << "Which of the following did \"" << newStudentName << "\" take?" << endl;
			for (int k = 0; k < optUnitsFromCurrentYear.size(); k++)
				cout << optUnitsFromCurrentYear.at(k)->getAbbreviation() << " " << optUnitsFromCurrentYear.at(k)->getName() << " | " << optUnitsFromCurrentYear.at(k)->getECTS() << "ECTS | Area: " << optUnitsFromCurrentYear.at(k)->getScientificArea() << endl;
			float ects_from_opt_units = 0; //Must be <= 33 to respect the 75ECTS per year limit (the other 42 are from mandatory units)
			string abbreviation;
			do {
				cout << "Insert the abbreviation of a unit \"" << newStudentName << "\" has taken (0 to finish): ";
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> abbreviation;
				deleteWhitespace(abbreviation);
				if (abbreviation == "0")
					break;
				bool found = false;
				for (int l = 0; l < optUnitsFromCurrentYear.size(); l++) {
					if (optUnitsFromCurrentYear.at(l)->getAbbreviation() == abbreviation) {
						found = true;
						break;
					}
				}
				if (!found)
					cout << "Unit \"" << abbreviation << "\" does not exist! Please insert a valid abbreviation" << endl;
				else if ((ects_from_opt_units + abbreviationToUnit.find(abbreviation)->second->getECTS()) > 33) //Exceeded limit of 75ECTS
					cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
				else {
					ects_from_opt_units += abbreviationToUnit.find(abbreviation)->second->getECTS();
					cout << "Insert new student's final grade obtained at " << abbreviation << ": ";
					grade = readOp(0, 20);
					if (grade >= 10)
						newStudentUnitsDone.at(abbreviationToUnit.find(abbreviation)->second->getCurricularYear() - 1).push_back(pair<Unit*, unsigned int>(abbreviationToUnit.find(abbreviation)->second, grade));
					else
						newStudentUnitsToDo.at(abbreviationToUnit.find(abbreviation)->second->getCurricularYear() - 1).push_back(pair<Unit*, unsigned int>(abbreviationToUnit.find(abbreviation)->second, grade));
				}
			} while (true); //If abbreviation == "0" break is called
		}
		//Given that newStudentCurricularYear must be in range [1,5] we'll never reach this case below... so, will remove later I think
		/*if (i == 4) { //5th curricular year (should have ended studies but hasn't yet), which includes optinal units
			vector<Unit*> optUnitsFromCurrentYear = getOptUnitsFromYear(i + 1);
			//Show optional units available
			cout << endl << "Which of the following did \"" << newStudentName << "\" take?" << endl;
			for (int k = 0; k < optUnitsFromCurrentYear.size(); k++)
				cout << optUnitsFromCurrentYear.at(k)->getAbbreviation() << " " << optUnitsFromCurrentYear.at(k)->getName() << " | " << optUnitsFromCurrentYear.at(k)->getECTS() << "ECTS | Area: " << optUnitsFromCurrentYear.at(k)->getScientificArea() << endl;
			float ects_from_opt_units = 0; //Must be <= 39 to respect the 75ECTS per year limit (the other 36 are from dissertation preparation and the dissertation itself)
			string abbreviation;
			do {
				cout << "Insert the abbreviation of a unit \"" << newStudentName << "\" has taken (0 to finish): ";
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> abbreviation;
				deleteWhitespace(abbreviation);
				if (abbreviation == "0")
					break;
				bool found = false;
				for (int l = 0; l < optUnitsFromCurrentYear.size(); l++) {
					if (optUnitsFromCurrentYear.at(l)->getAbbreviation() == abbreviation) {
						found = true;
						break;
					}
				}
				if (!found)
					cout << "Unit \"" << abbreviation << "\" does not exist! Please insert a valid abbreviation" << endl;
				else if ((ects_from_opt_units + abbreviationToUnit.find(abbreviation)->second->getECTS()) > 39) //Exceeded limit of 75ECTS
					cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
				else {
					ects_from_opt_units += abbreviationToUnit.find(abbreviation)->second->getECTS();
					cout << "Insert new student's final grade obtained at " << abbreviation << ": ";
					grade = readOp(0, 20);
					if (grade >= 10)
						newStudentUnitsDone.at(abbreviationToUnit.find(abbreviation)->second->getCurricularYear() - 1).push_back(pair<Unit*, unsigned int>(abbreviationToUnit.find(abbreviation)->second, grade));
					else
						newStudentUnitsToDo.at(abbreviationToUnit.find(abbreviation)->second->getCurricularYear() - 1).push_back(pair<Unit*, unsigned int>(abbreviationToUnit.find(abbreviation)->second, grade));
				}
			} while (true); //If abbreviation == "0" break is called
		}*/
	}

	if (newStudentCurricularYear == 1) {
		Student s(newStudentName, newStudentStatus, newStudentCurricularYear, newStudentUnitsDone, newStudentUnitsToDo);
		students.push_back(s);
	}
	else {
		Student s(newStudentName, newStudentStatus, newStudentCurricularYear, newStudentUnitsDone, newStudentUnitsToDo, newStudentCode);
		students.push_back(s);
	}
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

void Course::showStudent(string studentName) const {
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getName() == studentName) {
			cout << students.at(i) << endl;
			return;
		}
	}
	throw invalidIdentification<string>(studentName);
}

void Course::showStudent(unsigned long int studentCode) const {
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getCode() == studentCode) {
			cout << students.at(i) << endl;
			return;
		}
	}
	throw invalidIdentification<unsigned long>(studentCode);
}

void Course::showStudents(bool(*comparisonFunction)(Student, Student)) const {
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
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

void Course::showStudentUnits(std::string studentName) const {
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getName() == studentName) {
			vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();
			cout << "Student identified by \"" << studentName << "\" is taking:" << endl;
			for (int j = 0; j < unitsTaking.size(); j++) {
				cout << unitsTaking.at(j) << endl;
			}
		}
		cout << endl;
		return;
	}
	throw invalidIdentification<string>(studentName);
}

void Course::showStudentUnits(unsigned long studentCode) const {
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getCode() == studentCode) {
			vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();
			cout << "Student identified by \"" << studentCode << "\" is taking:" << endl;
			for (int j = 0; j < unitsTaking.size(); j++) {
				cout << unitsTaking.at(j) << endl;
			}
		}
		cout << endl;
		return;
	}
	throw invalidIdentification<unsigned long>(studentCode);
}

void Course::showYearRegistrations(unsigned int yearToShow) const {
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getCurricularYear() == yearToShow) {
			vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();
			cout << "Student \"" << students.at(i).getName() << "\" is taking: ";
			for (int j = 0; j < unitsTaking.size(); j++)
				cout << unitsTaking.at(j)->getAbbreviation() << " ";
			cout << endl;
		}
	}
}

void Course::showAllStudentsRegistrations() const {
	for (int i = 0; i < students.size(); i++) {
		vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();
		cout << "Student \"" << students.at(i).getName() << "\" is taking: ";
		for (int j = 0; j < unitsTaking.size(); j++)
			cout << unitsTaking.at(j)->getAbbreviation() << " ";
		cout << endl;
	}
}


void Course::editStudentName() {
	string studentName;
	cout << "Insert the student's old full name: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, studentName);
	deleteWhitespace(studentName);
	vector<Student>::iterator it = students.begin();
	for (it; it != students.end(); it++) {
		if (it->getName() == studentName)
			break;
	}

	if (it == students.end())
		throw invalidIdentification<string>(studentName);

	string newName;
	cout << "Insert the student's new full name: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, newName);
	vector<Student>::iterator second_it = students.begin();
	for (second_it; second_it != students.end(); second_it++) {
		if (second_it->getName() == newName)
			throw repeatedIdentification<string>(newName);
	}

	it->setName(newName);
}

void Course::editStudentStatus() {
	string studentName;
	cout << "Insert the student's full name: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, studentName);
	deleteWhitespace(studentName);
	vector<Student>::iterator it = students.begin();
	for (it; it != students.end(); it++) {
		if (it->getName() == studentName)
			break;
	}

	if (it == students.end())
		throw invalidIdentification<string>(studentName);

	string newStatus;
	cout << "Insert the student's new status: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, newStatus);
	it->setStatus(newStatus);
}

//Teachers


void Course::addTeacher() {
	string newTeacherName;
	cout << "Insert the new teacher's name: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, newTeacherName);

	string newTeacherCode;
	cout << "Insert the new teacher's code: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, newTeacherCode);

	for (vector<Teacher>::const_iterator it = teachers.begin(); it != teachers.end(); it++) {
		if (it->getName() == newTeacherName)
			throw repeatedIdentification<string>(newTeacherName);
		else if (it->getCode() == newTeacherCode)
			throw repeatedIdentification<string>(newTeacherCode);
	}

	string abbreviation;
	vector<Unit*> newTeacherUnitsTaught;
	do {
		cout << "Insert the abbreviation of a unit taught by \"" << newTeacherName << "\" (0 to finish): ";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, abbreviation);
		deleteWhitespace(abbreviation);
		if (!verifyUnit(abbreviation) && abbreviation != "0")
			cout << "Unit \"" << abbreviation << "\" does not exist! Please insert a valid abbreviation" << endl;
		else
			newTeacherUnitsTaught.push_back(abbreviationToUnit.find(abbreviation)->second);
	} while (abbreviation != "0");

	Teacher t1(newTeacherName, newTeacherCode, newTeacherUnitsTaught);
	teachers.push_back(t1);
}

void Course::editTeacherName() {
	string oldTeacherName;
	cout << "Insert the teacher's old full name: ";
	deleteWhitespace(oldTeacherName);
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, oldTeacherName);

	vector<Teacher>::iterator it = teachers.begin();
	for (it; it != teachers.end(); it++) {
		if (it->getName() == oldTeacherName)
			break;
	}

	if (it == teachers.end())
		throw invalidIdentification<string>(oldTeacherName);

	string newTeacherName;
	cout << "Insert the teacher's new full name: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, newTeacherName);

	for (vector<Teacher>::iterator second_it = teachers.begin(); second_it != teachers.end(); second_it++) {
		if (second_it->getName() == newTeacherName)
			throw repeatedIdentification<string>(newTeacherName);
	}

	it->setName(newTeacherName);
}

void Course::editTeacherCode() {
	string oldTeacherCode;
	cout << "Insert the teacher's old code: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, oldTeacherCode);
	deleteWhitespace(oldTeacherCode);

	vector<Teacher>::iterator it = teachers.begin();
	for (it; it != teachers.end(); it++) {
		if (it->getCode() == oldTeacherCode)
			break;
	}

	if (it == teachers.end())
		throw invalidIdentification<string>(oldTeacherCode);

	string newTeacherCode;
	cout << "Insert the teacher's new code: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, newTeacherCode);

	for (vector<Teacher>::iterator second_it = teachers.begin(); second_it != teachers.end(); second_it++) {
		if (second_it->getCode() == newTeacherCode)
			throw repeatedIdentification<string>(newTeacherCode);
	}

	it->setCode(newTeacherCode);
}

void Course::teacherAddUnitTaught() {
	string teacherName;
	cout << "Insert the teacher's full name: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, teacherName);
	deleteWhitespace(teacherName);

	vector<Teacher>::iterator it = teachers.begin();
	for (it; it != teachers.end(); it++) {
		if (it->getName() == teacherName)
			break;
	}

	if (it == teachers.end())
		throw invalidIdentification<string>(teacherName);

	string abbreviation;
	do {
		cout << "Insert the abbreviation of a unit taught by \"" << teacherName << "\" (0 if you changed your mind): ";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, abbreviation);
		deleteWhitespace(abbreviation);
		if (!verifyUnit(abbreviation) && abbreviation != "0")
			cout << "Unit \"" << abbreviation << "\" does not exist! Please insert a valid abbreviation" << endl;
		else
			it->addUnitTaught(abbreviationToUnit.find(abbreviation)->second);
	} while (abbreviation != "0" || !verifyUnit(abbreviation));
}

void Course::removeTeacher(string teacherID) {
	bool found = false;
	for (int i = 0; i < teachers.size(); i++) {
		if (teachers.at(i).getName() == teacherID || teachers.at(i).getCode() == teacherID) {
			found = true;
			if (teachers.at(i).getPupils().size() == Teacher::lessStudents) {
				unsigned int newMinimum = numeric_limits<unsigned int>::max();
				for (int j = 0; j < teachers.size(); i++) {
					if (j != i && teachers.at(j).getPupils().size() < newMinimum)
						newMinimum = teachers.at(j).getPupils().size();
				}
				Teacher::lessStudents = newMinimum;
			}
			teachers.erase(teachers.begin() + i);
			break;
		}
	}

	if (!found)
		throw invalidIdentification<string>(teacherID);
}

void Course::showTeachers(bool(*comparisonFunction)(Teacher, Teacher)) const {
	vector<Teacher> teachersTemp = teachers;
	sort(teachersTemp.begin(), teachersTemp.end(), *comparisonFunction);
	for (int i = 0; i < teachersTemp.size(); i++)
		cout << teachersTemp.at(i) << endl;
	cout << endl;
}

void Course::showTeacher(string teacherID) const {
	for (int i = 0; i < teachers.size(); i++) {
		if (teachers.at(i).getName() == teacherID|| teachers.at(i).getCode() == teacherID) {
			cout << teachers.at(i) << endl;
			return;
		}
	}
	throw invalidIdentification<string>(teacherID);
}

void Course::showTeacher(Unit* u1) const {
	for (int i = 0; i < teachers.size(); i++) {
		vector<Unit*> unitsTaughtTemp = teachers.at(i).getUnitsTaught();
		for (vector<Unit*>::iterator it = unitsTaughtTemp.begin(); it != unitsTaughtTemp.end(); it++) {
			if ((*it)->getAbbreviation() == u1->getAbbreviation()) {
				cout << teachers.at(i) << endl;
				return;
			}
		}
	}
}

void Course::showTeacherPupilByName(string pupilName) const {
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

void Course::showTeacherPupilByCode(unsigned long int pupilCode) const {
	for (int i = 0; i < teachers.size(); i++) {
		vector<Student*> pupilsTemp = teachers.at(i).getPupils();
		for (vector<Student*>::iterator it = pupilsTemp.begin(); it != pupilsTemp.end(); it++) {
			if ((*it)->getCode() == pupilCode) {
				cout << teachers.at(i) << endl;
				return;
			}
		}
	}
	throw invalidIdentification<unsigned long int>(pupilCode);
}

//Units


void Course::editUnitName() {
	string abbreviation;
	cout << "Insert the unit's abbreviation: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, abbreviation);
	deleteWhitespace(abbreviation);

	if (!verifyUnit(abbreviation))
		throw invalidIdentification<string>(abbreviation);

	string newName;
	cout << "Insert the unit's new name: ";
	getline(cin, newName);
	deleteWhitespace(newName);

	vector<Unit*> units = getAllUnits();
	for (unsigned int i = 0; i < units.size(); i++) {
		if (units.at(i)->getName() == newName)
			throw repeatedIdentification<string>(newName);
	}
	map<string, Unit*>::iterator it = abbreviationToUnit.find(abbreviation);
	it->second->setName(newName);
}
void Course::editUnitAbbreviation() {
	string abbreviation;
	cout << "Insert the unit's abbreviation: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, abbreviation);
	deleteWhitespace(abbreviation);

	if (!verifyUnit(abbreviation))
		throw invalidIdentification<string>(abbreviation);

	string newAbbreviation;
	cout << "Insert the unit's new abbreviation: ";
	getline(cin, newAbbreviation);
	deleteWhitespace(newAbbreviation);

	if (verifyUnit(newAbbreviation))
		throw repeatedIdentification<string>(newAbbreviation);

	map<string, Unit*>::iterator it = abbreviationToUnit.find(abbreviation);
	it->second->setAbbreviation(newAbbreviation);

	//Changing element in abbreviationToUnit map
	Unit* temp = it->second;
	abbreviationToUnit.erase(it);
	abbreviationToUnit[newAbbreviation] = temp;
}

void Course::editUnitScientificArea() {
	string abbreviation;
	cout << "Insert the unit's abbreviation: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, abbreviation);
	deleteWhitespace(abbreviation);

	if (!verifyUnit(abbreviation))
		throw invalidIdentification<string>(abbreviation);

	string newScientificArea;
	cout << "Insert the unit's new scientific area: ";
	getline(cin, newScientificArea);
	deleteWhitespace(newScientificArea);

	map<string, Unit*>::iterator it = abbreviationToUnit.find(abbreviation);
	it->second->setScientificArea(newScientificArea);
}

void Course::showUnits() const {
	vector<Unit*> unitTemp = getAllUnits();

	sort(unitTemp.begin(), unitTemp.end());

	for (int i = 0; i < unitTemp.size(); i++)
		cout << *unitTemp.at(i) << endl;
	cout << endl;
}

void Course::showSpecificUnit() const {
	string abbreviation;
	cout << "Insert the unit's abbreviation: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, abbreviation);
	deleteWhitespace(abbreviation);
	map<string, Unit*>::const_iterator it = abbreviationToUnit.find(abbreviation);
	if (it == abbreviationToUnit.end())
		throw invalidIdentification<string>(abbreviation);
	else
		cout << *(it->second);
}

void Course::showYearUnit(unsigned short int year) const {
	vector<Unit*> unitTemp = getUnitsFromYear(year);

	sort(unitTemp.begin(), unitTemp.end(), compareUnitPointers);

	for (int i = 0; i < unitTemp.size(); i++)
		cout << *unitTemp.at(i) << endl;
	cout << endl;
}

void Course::showMandatoryUnit() const {
	vector<Unit*> unitTemp = getAllMandatoryUnits();

	sort(unitTemp.begin(), unitTemp.end(), compareUnitPointers);

	for (int i = 0; i < unitTemp.size(); i++)
		cout << *unitTemp.at(i) << endl;
	cout << endl;
}

void Course::showOptionalUnit() const {
	vector<Unit*> unitTemp = getAllOptionalUnits();

	sort(unitTemp.begin(), unitTemp.end(), compareUnitPointers);

	for (int i = 0; i < unitTemp.size(); i++)
		cout << *unitTemp.at(i) << endl;
	cout << endl;
}

void Course::showUnitsofScientificArea(std::string scientificArea) const {
	vector<Unit*> result;
	for (map<string, Unit*>::const_iterator it = abbreviationToUnit.begin(); it != abbreviationToUnit.end(); it++) {
		if (it->second->getScientificArea() == scientificArea)
			result.push_back(it->second);
	}

	sort(result.begin(), result.end(), compareUnitPointers);
	for (int i = 0; i < result.size(); i++)
		cout << *(result.at(i)) << endl;
	cout << endl;
}

//Save
void Course::save() const {
	string studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName;

	cout << "Insert the filename where mandatory units will be saved: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, studentsFileName);
	ofstream studentsOut(studentsFileName);
	studentsOut << students.size() << endl;
	for (int i = 0; i < students.size(); i++) {
		students.at(i).save(studentsOut);
		studentsOut << endl << endl;
	}
	studentsOut.close();

	cout << "Insert the filename where teachers will be saved: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

	if (it != abbreviationToUnit.end())
		return true;

	return false;
}
