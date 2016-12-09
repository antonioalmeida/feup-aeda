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
		s1.calculateAverage();
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
			if (it->second->getScientificArea() == u1->getScientificArea() && it->second->getCurricularYear() == u1->getCurricularYear() && !(it->second->isFull()))
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
	for (unsigned int i = 0; i < students.size(); i++) {
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
		cin >> newStudentCode;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "ERROR: Input Invalid!" << endl;
		}
		else {
			for (unsigned int i = 0; i < students.size(); i++) {
				if (students.at(i).getCode() == newStudentCode)
					throw repeatedIdentification<unsigned long>(newStudentCode);
			}
		}
	}

	vector<vector<pair<Unit*, unsigned int>>> newStudentUnitsDone(5);
	vector<vector<pair<Unit*, unsigned int>>> newStudentUnitsToDo(5);
	unsigned int grade; //Auxiliar variable that will store each grade obtained in units student has attended
	for (unsigned int i = 0; i < newStudentCurricularYear - 1; i++) {
		vector<Unit*> manUnitsFromCurrentYear = getManUnitsFromYear(i + 1);
		for (unsigned int j = 0; j < manUnitsFromCurrentYear.size(); j++) {
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
			for (unsigned int k = 0; k < optUnitsFromCurrentYear.size(); k++)
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
				for (unsigned int l = 0; l < optUnitsFromCurrentYear.size(); l++) {
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
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students.at(i).getCode() == studentCode) {
			found = true;
			vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();
			for (unsigned int j = 0; j < unitsTaking.size(); j++) { //Update vacancies of possible optional units he's taking
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

	for (unsigned int i = 0; i < teachers.size(); i++) //Remove student of his mentor's pupils vector (if he had one, otherwise this piece of code does nothing)
		teachers.at(i).removeStudent(oldStudent);
}

void Course::removeStudent(string studentName) {
	bool found = false;
	Student oldStudent;
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students.at(i).getName() == studentName) {
			found = true;
			vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();
			for (unsigned int j = 0; j < unitsTaking.size(); j++) { //Update vacancies of possible optional units he's taking
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

	for (unsigned int i = 0; i < teachers.size(); i++) //Remove student of his mentor's pupils vector (if he had one, otherwise this piece of code does nothing)
		teachers.at(i).removeStudent(oldStudent);
}

void Course::showStudent(string studentName) const {
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students.at(i).getName() == studentName) {
			studentsPrintHeader();
			cout << students.at(i) << endl;
			return;
		}
	}
	throw invalidIdentification<string>(studentName);
}

void Course::showStudent(unsigned long int studentCode) const {
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students.at(i).getCode() == studentCode) {
			studentsPrintHeader();
			cout << students.at(i) << endl;
			return;
		}
	}
	throw invalidIdentification<unsigned long>(studentCode);
}

void Course::showStudents(bool(*comparisonFunction)(Student, Student)) const {
	vector<Student> studentsTemp = students;
	sort(studentsTemp.begin(), studentsTemp.end(), *comparisonFunction);

	studentsPrintHeader();
	for (unsigned int i = 0; i < studentsTemp.size(); i++) {
		cout << studentsTemp.at(i);
	}
	cout << endl;
}

void Course::showStudentsStatus(string status) const {
	vector<Student> studentsToShow;
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students.at(i).getStatus() == status)
			studentsToShow.push_back(students.at(i));
	}

	sort(studentsToShow.begin(), studentsToShow.end(), sortByName);
	studentsPrintHeader();

	for (unsigned int i = 0; i < studentsToShow.size(); i++)
		cout << studentsToShow.at(i);
	cout << endl;
}

void Course::showStudentsYear(unsigned short int curricularYear) const {
	vector<Student> studentsToShow;
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students.at(i).getCurricularYear() == curricularYear)
			studentsToShow.push_back(students.at(i));
	}

	sort(studentsToShow.begin(), studentsToShow.end(), sortByName);
	studentsPrintHeader();

	for (unsigned int i = 0; i < studentsToShow.size(); i++)
		cout << studentsToShow.at(i);
	cout << endl;

}
void Course::showRegisteredStudents() const {
	vector<Student> studentsToShow;
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students.at(i).isRegistered())
			studentsToShow.push_back(students.at(i));
	}
	sort(studentsToShow.begin(), studentsToShow.end(), sortByName);
	studentsPrintHeader();

	for (unsigned int i = 0; i < studentsToShow.size(); i++)
		cout << studentsToShow.at(i);
	cout << endl;
}

void Course::showUnregisteredStudents() const {
	vector<Student> studentsToShow;
	for (unsigned int i = 0; i < students.size(); i++) {
		if (!students.at(i).isRegistered())
			studentsToShow.push_back(students.at(i));
	}
	sort(studentsToShow.begin(), studentsToShow.end(), sortByName);
	studentsPrintHeader();

	for (unsigned int i = 0; i < studentsToShow.size(); i++)
		cout << studentsToShow.at(i);
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
	for (unsigned int i = 0; i < students.size(); i++) {
		for (unsigned int j = 0; j < students.at(i).getUnitsTaking().size(); j++) {
			if (students.at(i).getUnitsTaking().at(j)->getAbbreviation() == unitToShow) {
				result.push_back(students.at(i));
				break;
			}
		}
	}

	sort(result.begin(), result.end(), sortByName);
	studentsPrintHeader();

	for (unsigned int i = 0; i < result.size(); i++)
		cout << result.at(i) << endl;
	cout << endl;
}

void Course::showStudentUnits(string studentName) const {
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students.at(i).getName() == studentName) {
			vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();
			cout << "Student identified by \"" << studentName << "\" is taking:" << endl;
			for (unsigned int j = 0; j < unitsTaking.size(); j++) {
				cout << unitsTaking.at(j) << endl;
			}
			cout << endl;
			return;
		}
	}
	throw invalidIdentification<string>(studentName);
}

void Course::showStudentUnits(unsigned long studentCode) const {
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students.at(i).getCode() == studentCode) {
			vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();
			cout << "Student identified by \"" << studentCode << "\" is taking:" << endl;
			for (unsigned int j = 0; j < unitsTaking.size(); j++) {
				cout << unitsTaking.at(j);
			}
			cout << endl;
			return;
		}
	}
	throw invalidIdentification<unsigned long>(studentCode);
}

void Course::showYearRegistrations(unsigned int yearToShow) const {
	cout << setw(26) << "Name" << setw(25) << "Registration Date" << setw(17) << "Units Taking" << endl << endl;
	for (unsigned int i = 0; i < students.size(); i++) {
		if (students.at(i).getCurricularYear() == yearToShow) {
			cout << setw(32) << students.at(i).getName() << "  ";
			if (!students.at(i).isRegistered()) {
				cout << "is not registered" << endl;
				continue; //moves on to next student
			}

			cout << "    " << students.at(i).getRegistrationDate() << "       ";
			vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();

			for (unsigned int j = 0; j < unitsTaking.size(); j++)
				cout << unitsTaking.at(j)->getAbbreviation() << " ";

			cout << endl;
		}
	}
}

void Course::showAllStudentsRegistrations() const {
	cout << setw(26) << "Name" << setw(25) << "Registration Date" << setw(17) << "Units Taking" << endl << endl;
	for (unsigned int i = 0; i < students.size(); i++) {
		cout << setw(32) << students.at(i).getName() << "  ";
		if (!students.at(i).isRegistered()) {
			cout << "is not registered" << endl;
			continue; //moves on to next student
		}

		cout << "    " << students.at(i).getRegistrationDate() << "       ";
		vector<Unit*> unitsTaking = students.at(i).getUnitsTaking();

		for (unsigned int j = 0; j < unitsTaking.size(); j++)
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
	getline(cin, newStatus);
	it->setStatus(newStatus);
}

void Course::registerRandomStudent() {
	vector<Student>::iterator it = students.begin();
	for (it; it != students.end(); it++) {
		if (!it->isRegistered())
			break;
	}

	if (it == students.end())
		throw alreadyRegistered<string>("Everybody"); //Everybody has been registered

	vector<Unit*> unitsLeftBehind;
	for (unsigned int i = 0; i < it->getUnitsToDo().size(); i++) {
		for (unsigned int j = 0; j < it->getUnitsToDo().at(i).size(); j++)
			unitsLeftBehind.push_back(it->getUnitsToDo().at(i).at(j).first);
	}

	vector<Unit*> manUnitsFromCurrentYear = getManUnitsFromYear(it->getCurricularYear());
	vector<Unit*> optUnitsFromCurrentYear = getOptUnitsFromYear(it->getCurricularYear()); //Empty unless curricular year is 4 or 5

																						  //Show units the student has left behind so he knows what to put in first
	if (unitsLeftBehind.size() > 0) {
		cout << "Units from previous years left to do:" << endl;
		unitsPrintHeader();
		for (unsigned int i = 0; i < unitsLeftBehind.size(); i++)
			cout << *(unitsLeftBehind.at(i)) << endl;
	}
	sort(unitsLeftBehind.begin(), unitsLeftBehind.end(), compareUnitPointers); //To guarantee units from lower curricular years are registered first

																			   //Show units the student from the current year
	cout << "Units from the current year:" << endl;
	unitsPrintHeader();
	for (unsigned int i = 0; i < manUnitsFromCurrentYear.size(); i++)
		cout << *(manUnitsFromCurrentYear.at(i)) << endl;

	string abbreviation;
	float total_ects = 0;

	//First, make sure student registers to the units he's got behind
	while (unitsLeftBehind.size() > 0) {
		cout << "Insert the abbreviation of a unit \"" << it->getName() << "\" is going to take: ";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> abbreviation;
		deleteWhitespace(abbreviation);
		int indexOfCurrentUnit = -1;
		for (unsigned int l = 0; l < unitsLeftBehind.size(); l++) {
			if (unitsLeftBehind.at(l)->getAbbreviation() == abbreviation) {
				indexOfCurrentUnit = l;
				break;
			}
		}
		if (indexOfCurrentUnit == -1)
			cout << "Unit \"" << abbreviation << "\" does not exist or is not valid! Please insert a valid abbreviation" << endl;
		else if (unitsLeftBehind.at(0)->getCurricularYear() > unitsLeftBehind.at(indexOfCurrentUnit)->getCurricularYear()) //If there is at least one unit left behind from a curricular year lower than the one provided in abbreviation
			cout << "There are units left behind from curricular years lower than \"" << abbreviation << "\", must register to those first!" << endl;
		else if ((total_ects + abbreviationToUnit.find(abbreviation)->second->getECTS()) > MAX_ECTS) //Delete this if? I think it'll never reach 75ECTS only of left behind units
			cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
		else {
			total_ects += abbreviationToUnit.find(abbreviation)->second->getECTS();
			it->addUnitTaking(unitsLeftBehind.at(indexOfCurrentUnit));
			cout << "Unit \"" << abbreviation << "\" successfully added" << endl;
			unitsLeftBehind.erase(unitsLeftBehind.begin() + indexOfCurrentUnit);
		}
	}

	//Now, make sure student registers to all mandatory units (or as much as he can)
	while (manUnitsFromCurrentYear.size() > 0 && total_ects <= MAX_ECTS) {
		cout << "Insert the abbreviation of a unit \"" << it->getName() << "\" is going to take: ";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> abbreviation;
		deleteWhitespace(abbreviation);
		int indexOfCurrentUnit = -1;
		for (unsigned int l = 0; l < manUnitsFromCurrentYear.size(); l++) {
			if (manUnitsFromCurrentYear.at(l)->getAbbreviation() == abbreviation) {
				indexOfCurrentUnit = l;
				break;
			}
		}
		if (indexOfCurrentUnit == -1)
			cout << "Unit \"" << abbreviation << "\" does not exist or is not valid! Please insert a valid abbreviation" << endl;
		else if ((total_ects + abbreviationToUnit.find(abbreviation)->second->getECTS()) > MAX_ECTS) //insert another test to see student has credits left but no units left with small enough ects? and if so, exit loop
			cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
		else {
			total_ects += abbreviationToUnit.find(abbreviation)->second->getECTS();
			it->addUnitTaking(manUnitsFromCurrentYear.at(indexOfCurrentUnit));
			cout << "Unit \"" << abbreviation << "\" successfully added" << endl;
			manUnitsFromCurrentYear.erase(manUnitsFromCurrentYear.begin() + indexOfCurrentUnit);
		}
        
        float creditsLeft = MAX_ECTS-total_ects;
        bool proceed = false;
        /* Check if student still has credit left to register in mandatory units. If he does not, break loop */
        for(unsigned int i = 0; i < manUnitsFromCurrentYear.size(); i++){
            if(manUnitsFromCurrentYear.at(i)->getECTS() <= creditsLeft){
                proceed = true;
                break;
            }
        }
        if(!proceed)
            break;
        
	}

	//Now, if it is the case (if empty vector just skips loop) and there's credit left, register to optional units
	while (optUnitsFromCurrentYear.size() > 0 && total_ects <= MAX_ECTS) {
		cout << "Insert the abbreviation of a unit \"" << it->getName() << "\" has taken (0 to finish): ";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> abbreviation;
		deleteWhitespace(abbreviation);
		if (abbreviation == "0")
			break;
		int indexOfCurrentUnit = -1;
		for (unsigned int l = 0; l < optUnitsFromCurrentYear.size(); l++) {
			if (optUnitsFromCurrentYear.at(l)->getAbbreviation() == abbreviation) {
				indexOfCurrentUnit = l;
				break;
			}
		}
		if (indexOfCurrentUnit == -1)
			cout << "Unit \"" << abbreviation << "\" does not exist! Please insert a valid abbreviation" << endl;
		else if ((total_ects + abbreviationToUnit.find(abbreviation)->second->getECTS()) > MAX_ECTS)
			cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
		else if (optUnitsFromCurrentYear.at(indexOfCurrentUnit)->isFull()) { //Select optional unit is a valid option but is already full, so suggest units from same scientific area THAT ARE NOT FULL
			cout << "Unit \"" << abbreviation << "\" is currently full! Here's some other units from the same area that might interest you:" << endl;
			vector<Unit*> sameAreaUnits = getUnitsFromSameScientificArea(optUnitsFromCurrentYear.at(indexOfCurrentUnit));
			unitsPrintHeader();
			for (unsigned int i = 0; i < sameAreaUnits.size(); i++)
				cout << *(sameAreaUnits.at(i)) << endl;
		}
		else {
			total_ects += abbreviationToUnit.find(abbreviation)->second->getECTS();
			it->addUnitTaking(optUnitsFromCurrentYear.at(indexOfCurrentUnit));
			optUnitsFromCurrentYear.at(indexOfCurrentUnit)->updateVacancies();
			cout << "Unit \"" << abbreviation << "\" successfully added" << endl;
			optUnitsFromCurrentYear.erase(optUnitsFromCurrentYear.begin() + indexOfCurrentUnit);
		}
	}

	Date dateOfRegistration;
	do {
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Insert the date \"" << it->getName() << "\" has registered in: (DD/MM/YYYY) ";
		string registrationDate;
		getline(cin, registrationDate);
		deleteWhitespace(registrationDate);
		dateOfRegistration = Date(registrationDate);

		if (!validDate(dateOfRegistration.getDay(), dateOfRegistration.getMonth(), dateOfRegistration.getYear()))
			cout << "The date you inserted is not valid \n";
		else {
			it->setRegistrationDate(dateOfRegistration);
			cout << "The student \"" << it->getName() << "\" was successfuly registrated on " << dateOfRegistration;
		}

	} while (!validDate(dateOfRegistration.getDay(), dateOfRegistration.getMonth(), dateOfRegistration.getYear()));

	//Add the student to the teacher with the least amount of pupils (the first one that comes up)
	for (unsigned int i = 0; i < teachers.size(); i++) {
		if (teachers.at(i).getPupils().size() == Teacher::lessStudents) {
			teachers.at(i).addStudent(&(*it));

			unsigned int newMinimum = numeric_limits<unsigned int>::max();
			for (unsigned int j = 0; j < teachers.size(); j++) {
				if (j != i && teachers.at(j).getPupils().size() < newMinimum)
					newMinimum = teachers.at(j).getPupils().size();
			}
			Teacher::lessStudents = newMinimum;
			cout << " and is now a pupil of " << teachers.at(i).getName() << endl;
			break;
		}
	}

	it->setECTSTaking(total_ects);
	it->setRegistration();

}

void Course::registerSpecificStudentByName() {
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
	else if (it->isRegistered())
		throw alreadyRegistered<string>(studentName);

	vector<Unit*> unitsLeftBehind;
	for (unsigned int i = 0; i < it->getUnitsToDo().size(); i++) {
		for (unsigned int j = 0; j < it->getUnitsToDo().at(i).size(); j++)
			unitsLeftBehind.push_back(it->getUnitsToDo().at(i).at(j).first);
	}

	vector<Unit*> manUnitsFromCurrentYear = getManUnitsFromYear(it->getCurricularYear());
	vector<Unit*> optUnitsFromCurrentYear = getOptUnitsFromYear(it->getCurricularYear()); //Empty unless curricular year is 4 or 5

																						  //Show units the student has left behind so he knows what to put in first
	if (unitsLeftBehind.size() > 0) {
		cout << "Units from previous years left to do:" << endl;
		unitsPrintHeader();
		for (unsigned int i = 0; i < unitsLeftBehind.size(); i++)
			cout << *(unitsLeftBehind.at(i)) << endl;
	}
	sort(unitsLeftBehind.begin(), unitsLeftBehind.end(), compareUnitPointers); //To guarantee units from lower curricular years are registered first

																			   //Show units the student from the current year
	cout << "Units from the current year:" << endl;
	unitsPrintHeader();
	for (unsigned int i = 0; i < manUnitsFromCurrentYear.size(); i++)
		cout << *(manUnitsFromCurrentYear.at(i)) << endl;

	string abbreviation;
	float total_ects = 0;

	//First, make sure student registers to the units he's got behind
	while (unitsLeftBehind.size() > 0) {
		cout << "Insert the abbreviation of a unit \"" << it->getName() << "\" is going to take: ";
		//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> abbreviation;
		deleteWhitespace(abbreviation);
		int indexOfCurrentUnit = -1;
		for (unsigned int l = 0; l < unitsLeftBehind.size(); l++) {
			if (unitsLeftBehind.at(l)->getAbbreviation() == abbreviation) {
				indexOfCurrentUnit = l;
				break;
			}
		}
		if (indexOfCurrentUnit == -1)
			cout << "Unit \"" << abbreviation << "\" does not exist or is not valid! Please insert a valid abbreviation" << endl;
		else if (unitsLeftBehind.at(0)->getCurricularYear() > unitsLeftBehind.at(indexOfCurrentUnit)->getCurricularYear()) //If there is at least one unit left behind from a curricular year lower than the one provided in abbreviation
			cout << "There are units left behind from curricular years lower than \"" << abbreviation << "\", must register to those first!" << endl;
		else if ((total_ects + abbreviationToUnit.find(abbreviation)->second->getECTS()) > MAX_ECTS)
			cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
		else {
			total_ects += abbreviationToUnit.find(abbreviation)->second->getECTS();
			it->addUnitTaking(unitsLeftBehind.at(indexOfCurrentUnit));
			cout << "Unit \"" << abbreviation << "\" successfully added" << endl;
			unitsLeftBehind.erase(unitsLeftBehind.begin() + indexOfCurrentUnit);
		}
	}

	//Now, make sure student registers to all mandatory units (or as much as he can)
	while (manUnitsFromCurrentYear.size() > 0 && total_ects <= MAX_ECTS) {
		cout << "Insert the abbreviation of a unit \"" << it->getName() << "\" is going to take: ";
		cin >> abbreviation;
		deleteWhitespace(abbreviation);
		int indexOfCurrentUnit = -1;
		for (unsigned int l = 0; l < manUnitsFromCurrentYear.size(); l++) {
			if (manUnitsFromCurrentYear.at(l)->getAbbreviation() == abbreviation) {
				indexOfCurrentUnit = l;
				break;
			}
		}
		if (indexOfCurrentUnit == -1)
			cout << "Unit \"" << abbreviation << "\" does not exist or is not valid! Please insert a valid abbreviation" << endl;
		else if ((total_ects + abbreviationToUnit.find(abbreviation)->second->getECTS()) > MAX_ECTS) //insert another test to see student has credits left but no units left with small enough ects? and if so, exit loop
			cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
		else {
			total_ects += abbreviationToUnit.find(abbreviation)->second->getECTS();
			it->addUnitTaking(manUnitsFromCurrentYear.at(indexOfCurrentUnit));
			cout << "Unit \"" << abbreviation << "\" successfully added" << endl;
			manUnitsFromCurrentYear.erase(manUnitsFromCurrentYear.begin() + indexOfCurrentUnit);
		}
        
        float creditsLeft = MAX_ECTS-total_ects;
        bool proceed = false;
        /* Check if student still has credit left to register in mandatory units. If he does not, break loop */
        for(unsigned int i = 0; i < manUnitsFromCurrentYear.size(); i++){
            if(manUnitsFromCurrentYear.at(i)->getECTS() <= creditsLeft){
                proceed = true;
                break;
            }
        }
        if(!proceed)
            break;
        
        
	}

	if (optUnitsFromCurrentYear.size() > 0) {
		cout << "Optional Units from the current year:" << endl;
		unitsPrintHeader();
		for (unsigned int i = 0; i < optUnitsFromCurrentYear.size(); i++)
			cout << *(optUnitsFromCurrentYear.at(i)) << endl;
	}

	//Now, if it is the case (if empty vector just skips loop) and there's credit left, register to optional units
	while (optUnitsFromCurrentYear.size() > 0 && total_ects <= MAX_ECTS) {
		cout << "Insert the abbreviation of a unit \"" << it->getName() << "\" has taken (0 to finish): ";
		//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> abbreviation;
		deleteWhitespace(abbreviation);
		if (abbreviation == "0")
			break;
		int indexOfCurrentUnit = -1;
		for (unsigned int l = 0; l < optUnitsFromCurrentYear.size(); l++) {
			if (optUnitsFromCurrentYear.at(l)->getAbbreviation() == abbreviation) {
				indexOfCurrentUnit = l;
				break;
			}
		}
		if (indexOfCurrentUnit == -1)
			cout << "Unit \"" << abbreviation << "\" does not exist! Please insert a valid abbreviation" << endl;
		else if ((total_ects + abbreviationToUnit.find(abbreviation)->second->getECTS()) > MAX_ECTS)
			cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
		else if (optUnitsFromCurrentYear.at(indexOfCurrentUnit)->isFull()) { //Select optional unit is a valid option but is already full, so suggest units from same scientific area THAT ARE NOT FULL
			cout << "Unit \"" << abbreviation << "\" is currently full! Here's some other units from the same area that might interest you:" << endl;
			vector<Unit*> sameAreaUnits = getUnitsFromSameScientificArea(optUnitsFromCurrentYear.at(indexOfCurrentUnit));
			unitsPrintHeader();
			for (unsigned int i = 0; i < sameAreaUnits.size(); i++)
				cout << *(sameAreaUnits.at(i)) << endl;
		}
		else {
			total_ects += abbreviationToUnit.find(abbreviation)->second->getECTS();
			it->addUnitTaking(optUnitsFromCurrentYear.at(indexOfCurrentUnit));
			optUnitsFromCurrentYear.at(indexOfCurrentUnit)->updateVacancies();
			cout << "Unit \"" << abbreviation << "\" successfully added" << endl;
			optUnitsFromCurrentYear.erase(optUnitsFromCurrentYear.begin() + indexOfCurrentUnit);
		}
	}

	Date dateOfRegistration;
	do {
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Insert the date \"" << it->getName() << "\" has registered in: (DD/MM/YYYY) ";
		string registrationDate;
		getline(cin, registrationDate);
		deleteWhitespace(registrationDate);
		dateOfRegistration = Date(registrationDate);

		if (!validDate(dateOfRegistration.getDay(), dateOfRegistration.getMonth(), dateOfRegistration.getYear()))
			cout << "The date you inserted is not valid \n";
		else {
			it->setRegistrationDate(dateOfRegistration);
			cout << "The student \"" << it->getName() << "\" was successfuly registrated on " << dateOfRegistration;
		}

	} while (!validDate(dateOfRegistration.getDay(), dateOfRegistration.getMonth(), dateOfRegistration.getYear()));

	//Add the student to the teacher with the least amount of pupils (the first one that comes up)
	for (unsigned int i = 0; i < teachers.size(); i++) {
		if (teachers.at(i).getPupils().size() == Teacher::lessStudents) {
			teachers.at(i).addStudent(&(*it));

			unsigned int newMinimum = numeric_limits<unsigned int>::max();
			for (unsigned int j = 0; j < teachers.size(); j++) {
				if (j != i && teachers.at(j).getPupils().size() < newMinimum)
					newMinimum = teachers.at(j).getPupils().size();
			}
			Teacher::lessStudents = newMinimum;
			cout << " and is now a pupil of " << teachers.at(i).getName() << endl;
			break;
		}
	}

	it->setECTSTaking(total_ects);
	it->setRegistration();
}

void Course::registerSpecificStudentByCode() {
	unsigned long int studentCode;
	cout << "Insert the student's code: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin >> studentCode;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "ERROR: Input Invalid!" << endl;
	}

	else {
		vector<Student>::iterator it = students.begin();
		for (it; it != students.end(); it++) {
			if (it->getCode() == studentCode)
				break;
		}

		if (it == students.end())
			throw invalidIdentification<unsigned long int>(studentCode);
		else if (it->isRegistered())
			throw alreadyRegistered<unsigned long int>(studentCode);

		vector<Unit*> unitsLeftBehind;
		for (unsigned int i = 0; i < it->getUnitsToDo().size(); i++) {
			for (unsigned int j = 0; j < it->getUnitsToDo().at(i).size(); j++)
				unitsLeftBehind.push_back(it->getUnitsToDo().at(i).at(j).first);
		}

		vector<Unit*> manUnitsFromCurrentYear = getManUnitsFromYear(it->getCurricularYear());
		vector<Unit*> optUnitsFromCurrentYear = getOptUnitsFromYear(it->getCurricularYear()); //Empty unless curricular year is 4 or 5

																							  //Show units the student has left behind so he knows what to put in first
		if (unitsLeftBehind.size() > 0) {
			cout << "Units from previous years left to do:" << endl;
			unitsPrintHeader();
			for (unsigned int i = 0; i < unitsLeftBehind.size(); i++)
				cout << *(unitsLeftBehind.at(i)) << endl;
		}
		sort(unitsLeftBehind.begin(), unitsLeftBehind.end(), compareUnitPointers); //To guarantee units from lower curricular years are registered first

																				   //Show units the student from the current year
		cout << "Units from the current year:" << endl;
		unitsPrintHeader();
		for (unsigned int i = 0; i < manUnitsFromCurrentYear.size(); i++)
			cout << *(manUnitsFromCurrentYear.at(i)) << endl;

		string abbreviation;
		float total_ects = 0;

		//First, make sure student registers to the units he's got behind
		while (unitsLeftBehind.size() > 0) {
			cout << "Insert the abbreviation of a unit \"" << it->getName() << "\" is going to take: ";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> abbreviation;
			deleteWhitespace(abbreviation);
			int indexOfCurrentUnit = -1;
			for (unsigned int l = 0; l < unitsLeftBehind.size(); l++) {
				if (unitsLeftBehind.at(l)->getAbbreviation() == abbreviation) {
					indexOfCurrentUnit = l;
					break;
				}
			}
			if (indexOfCurrentUnit == -1)
				cout << "Unit \"" << abbreviation << "\" does not exist or is not valid! Please insert a valid abbreviation" << endl;
			else if (unitsLeftBehind.at(0)->getCurricularYear() > unitsLeftBehind.at(indexOfCurrentUnit)->getCurricularYear()) //If there is at least one unit left behind from a curricular year lower than the one provided in abbreviation
				cout << "There are units left behind from curricular years lower than \"" << abbreviation << "\", must register to those first!" << endl;
			else if ((total_ects + abbreviationToUnit.find(abbreviation)->second->getECTS()) > MAX_ECTS) //Delete this if? I think it'll never reach 75ECTS only of left behind units
				cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
			else {
				total_ects += abbreviationToUnit.find(abbreviation)->second->getECTS();
				it->addUnitTaking(unitsLeftBehind.at(indexOfCurrentUnit));
				cout << "Unit \"" << abbreviation << "\" successfully added" << endl;
				//it->removeUnitToDo(unitsLeftBehind.at(indexOfCurrentUnit)); //not sure if i wanna remove it (might want to keep it to later save in file)
				unitsLeftBehind.erase(unitsLeftBehind.begin() + indexOfCurrentUnit);
			}
		}

		//Now, make sure student registers to all mandatory units (or as much as he can)
		while (manUnitsFromCurrentYear.size() > 0 && total_ects <= MAX_ECTS) {
			cout << "Insert the abbreviation of a unit \"" << it->getName() << "\" is going to take: ";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> abbreviation;
			deleteWhitespace(abbreviation);
			int indexOfCurrentUnit = -1;
			for (unsigned int l = 0; l < manUnitsFromCurrentYear.size(); l++) {
				if (manUnitsFromCurrentYear.at(l)->getAbbreviation() == abbreviation) {
					indexOfCurrentUnit = l;
					break;
				}
			}
			if (indexOfCurrentUnit == -1)
				cout << "Unit \"" << abbreviation << "\" does not exist or is not valid! Please insert a valid abbreviation" << endl;
			else if ((total_ects + abbreviationToUnit.find(abbreviation)->second->getECTS()) > MAX_ECTS) //insert another test to see student has credits left but no units left with small enough ects? and if so, exit loop
				cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
			else {
				total_ects += abbreviationToUnit.find(abbreviation)->second->getECTS();
				it->addUnitTaking(manUnitsFromCurrentYear.at(indexOfCurrentUnit));
				cout << "Unit \"" << abbreviation << "\" successfully added" << endl;
				manUnitsFromCurrentYear.erase(manUnitsFromCurrentYear.begin() + indexOfCurrentUnit);
			}
            
            float creditsLeft = MAX_ECTS-total_ects;
            bool proceed = false;
            /* Check if student still has credit left to register in mandatory units. If he does not, break loop */
            for(unsigned int i = 0; i < manUnitsFromCurrentYear.size(); i++){
                if(manUnitsFromCurrentYear.at(i)->getECTS() <= creditsLeft){
                    proceed = true;
                    break;
                }
            }
            if(!proceed)
                break;
            
		}

		//Now, if it is the case (if empty vector just skips loop) and there's credit left, register to optional units
		while (optUnitsFromCurrentYear.size() > 0 && total_ects <= MAX_ECTS) {
			cout << "Insert the abbreviation of a unit \"" << it->getName() << "\" has taken (0 to finish): ";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin >> abbreviation;
			deleteWhitespace(abbreviation);
			if (abbreviation == "0")
				break;
			int indexOfCurrentUnit = -1;
			for (unsigned int l = 0; l < optUnitsFromCurrentYear.size(); l++) {
				if (optUnitsFromCurrentYear.at(l)->getAbbreviation() == abbreviation) {
					indexOfCurrentUnit = l;
					break;
				}
			}
			if (indexOfCurrentUnit == -1)
				cout << "Unit \"" << abbreviation << "\" does not exist! Please insert a valid abbreviation" << endl;
			else if ((total_ects + abbreviationToUnit.find(abbreviation)->second->getECTS()) > MAX_ECTS)
				cout << "Unit \"" << abbreviation << "\" would cause 75ECTS limit to be exceeded! Please insert a valid abbreviation" << endl;
			else if (optUnitsFromCurrentYear.at(indexOfCurrentUnit)->isFull()) { //Select optional unit is a valid option but is already full, so suggest units from same scientific area THAT ARE NOT FULL
				cout << "Unit \"" << abbreviation << "\" is currently full! Here's some other units from the same area that might interest you:" << endl;
				vector<Unit*> sameAreaUnits = getUnitsFromSameScientificArea(optUnitsFromCurrentYear.at(indexOfCurrentUnit));
				unitsPrintHeader();
				for (unsigned int i = 0; i < sameAreaUnits.size(); i++)
					cout << *(sameAreaUnits.at(i)) << endl;
			}
			else {
				total_ects += abbreviationToUnit.find(abbreviation)->second->getECTS();
				it->addUnitTaking(optUnitsFromCurrentYear.at(indexOfCurrentUnit));
				optUnitsFromCurrentYear.at(indexOfCurrentUnit)->updateVacancies();
				cout << "Unit \"" << abbreviation << "\" successfully added" << endl;
				optUnitsFromCurrentYear.erase(optUnitsFromCurrentYear.begin() + indexOfCurrentUnit);
			}
		}

		Date dateOfRegistration;
		do {
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Insert the date \"" << it->getName() << "\" has registered in: (DD/MM/YYYY) ";
			string registrationDate;
			getline(cin, registrationDate);
			deleteWhitespace(registrationDate);
			dateOfRegistration = Date(registrationDate);

			if (!validDate(dateOfRegistration.getDay(), dateOfRegistration.getMonth(), dateOfRegistration.getYear()))
				cout << "The date you inserted is not valid \n";
			else {
				it->setRegistrationDate(dateOfRegistration);
				cout << "The student \"" << it->getName() << "\" was successfuly registrated on " << dateOfRegistration;
			}

		} while (!validDate(dateOfRegistration.getDay(), dateOfRegistration.getMonth(), dateOfRegistration.getYear()));


		//Add the student to the teacher with the least amount of pupils (the first one that comes up)
		for (unsigned int i = 0; i < teachers.size(); i++) {
			if (teachers.at(i).getPupils().size() == Teacher::lessStudents) {
				teachers.at(i).addStudent(&(*it));

				unsigned int newMinimum = numeric_limits<unsigned int>::max();
				for (unsigned int j = 0; j < teachers.size(); j++) {
					if (j != i && teachers.at(j).getPupils().size() < newMinimum)
						newMinimum = teachers.at(j).getPupils().size();
				}
				Teacher::lessStudents = newMinimum;
				cout << " and is now a pupil of " << teachers.at(i).getName() << endl;
				break;
			}
		}

		it->setECTSTaking(total_ects);
		it->setRegistration();
	}
}

//Teachers


void Course::addTeacher() {
	string newTeacherName;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Insert the new teacher's name: " << endl;
	getline(cin, newTeacherName);

	string newTeacherCode;
	cout << "Insert the new teacher's code: " << endl;
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
		cout << "Insert the abbreviation of a unit taught by \"" << newTeacherName << "\" (0 to finish): " << endl;
		getline(cin, abbreviation);
		deleteWhitespace(abbreviation);
		if (abbreviation == "0")
			break;
		if (!verifyUnit(abbreviation))
			cout << "Unit \"" << abbreviation << "\" does not exist! Please insert a valid abbreviation" << endl;
		else
			newTeacherUnitsTaught.push_back(abbreviationToUnit.at(abbreviation));
	} while (true);
    
    Teacher::lessStudents = 0; //Update minimum value of pupils
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
		getline(cin, abbreviation);
		deleteWhitespace(abbreviation);
		if (abbreviation == "0")
			break;
		if (!verifyUnit(abbreviation) && abbreviation != "0")
			cout << "Unit \"" << abbreviation << "\" does not exist! Please insert a valid abbreviation" << endl;
		else
			it->addUnitTaught(abbreviationToUnit.find(abbreviation)->second);
	} while (true);
}

void Course::removeTeacher(string teacherID) {
	bool found = false;
	for (unsigned int i = 0; i < teachers.size(); i++) {
		if (teachers.at(i).getName() == teacherID || teachers.at(i).getCode() == teacherID) {
			found = true;
			if (teachers.at(i).getPupils().size() == Teacher::lessStudents) {
				unsigned int newMinimum = numeric_limits<unsigned int>::max();
				for (unsigned int j = 0; j < teachers.size(); j++) {
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

	teachersPrintHeader();
	for (unsigned int i = 0; i < teachersTemp.size(); i++)
		cout << teachersTemp.at(i);
	cout << endl;
}

void Course::showTeacher(string teacherID) const {
	for (unsigned int i = 0; i < teachers.size(); i++) {
		if (teachers.at(i).getName() == teacherID || teachers.at(i).getCode() == teacherID) {
			teachersPrintHeader();
			cout << teachers.at(i);
			return;
		}
	}
	throw invalidIdentification<string>(teacherID);
}

void Course::showTeacher(Unit* u1) const {
	for (unsigned int i = 0; i < teachers.size(); i++) {
		vector<Unit*> unitsTaughtTemp = teachers.at(i).getUnitsTaught();
		for (vector<Unit*>::iterator it = unitsTaughtTemp.begin(); it != unitsTaughtTemp.end(); it++) {
			if ((*it)->getAbbreviation() == u1->getAbbreviation()) {
				teachersPrintHeader();
				cout << teachers.at(i);
				return;
			}
		}
	}
}

void Course::showTeacherPupilByName(string pupilName) const {
	for (unsigned int i = 0; i < teachers.size(); i++) {
		vector<Student*> pupilsTemp = teachers.at(i).getPupils();
		for (vector<Student*>::iterator it = pupilsTemp.begin(); it != pupilsTemp.end(); it++) {
			if ((*it)->getName() == pupilName) {
				teachersPrintHeader();
				cout << teachers.at(i);
				return;
			}
		}
	}
	throw invalidIdentification<string>(pupilName);
}

void Course::showTeacherPupilByCode(unsigned long int pupilCode) const {
	for (unsigned int i = 0; i < teachers.size(); i++) {
		vector<Student*> pupilsTemp = teachers.at(i).getPupils();
		for (vector<Student*>::iterator it = pupilsTemp.begin(); it != pupilsTemp.end(); it++) {
			if ((*it)->getCode() == pupilCode) {
				teachersPrintHeader();
				cout << teachers.at(i);
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

	unitsPrintHeader();

	sort(unitTemp.begin(), unitTemp.end(), compareUnitPointers);

	for (unsigned int i = 0; i < unitTemp.size(); i++)
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
	else {
		unitsPrintHeader();
		cout << *(it->second) << endl;
	}
}

void Course::showYearUnit(unsigned short int year) const {
	vector<Unit*> unitTemp = getUnitsFromYear(year);

	sort(unitTemp.begin(), unitTemp.end(), compareUnitPointers);

	unitsPrintHeader();
	for (unsigned int i = 0; i < unitTemp.size(); i++)
		cout << *unitTemp.at(i) << endl;
	cout << endl;
}

void Course::showMandatoryUnit() const {
	vector<Unit*> unitTemp = getAllMandatoryUnits();

	sort(unitTemp.begin(), unitTemp.end(), compareUnitPointers);

	unitsPrintHeader();
	for (unsigned int i = 0; i < unitTemp.size(); i++)
		cout << *unitTemp.at(i) << endl;
	cout << endl;
}

void Course::showOptionalUnit() const {
	vector<Unit*> unitTemp = getAllOptionalUnits();

	sort(unitTemp.begin(), unitTemp.end(), compareUnitPointers);

	unitsPrintHeader();
	for (unsigned int i = 0; i < unitTemp.size(); i++)
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

	unitsPrintHeader();
	for (unsigned int i = 0; i < result.size(); i++)
		cout << *(result.at(i)) << endl;
	cout << endl;
}

//Save
void Course::save() const {
	string studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName;

	cout << "Insert the filename where mandatory units will be saved: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, mandatoryUnitsFileName);
	ofstream mandatoryUnitsOut(mandatoryUnitsFileName+".txt");
	vector<Unit*> manUnits = getAllMandatoryUnits();
	mandatoryUnitsOut << manUnits.size() << endl;
	for (unsigned int i = 0; i < manUnits.size(); i++) {
		manUnits.at(i)->save(mandatoryUnitsOut);
		mandatoryUnitsOut << endl << endl;
	}

	cout << "Insert the filename where optional units will be saved: ";
	getline(cin, optionalUnitsFileName);
	ofstream optionalUnitsOut(optionalUnitsFileName+".txt");
	vector<Unit*> optUnits = getAllOptionalUnits();
	optionalUnitsOut << optUnits.size() << endl;
	for (unsigned int i = 0; i < optUnits.size(); i++) {
		optUnits.at(i)->save(optionalUnitsOut);
		optionalUnitsOut << endl << endl;
	}
	optionalUnitsOut.close();

	cout << "Insert the filename where students will be saved: ";
	getline(cin, studentsFileName);
	ofstream studentsOut(studentsFileName+".txt");
	studentsOut << students.size() << endl;
	for (unsigned int i = 0; i < students.size(); i++) {
		students.at(i).save(studentsOut);
		studentsOut << endl << endl;
	}
	studentsOut.close();

	ofstream studentsOutExecution(studentsFileName + "_execution.txt");
	studentsOutExecution << students.size() << endl;
	for (unsigned int i = 0; i < students.size(); i++) {
		students.at(i).save(studentsOutExecution);
		studentsOutExecution << endl;
		if (students.at(i).getUnitsTaking().size() > 0) {
			studentsOutExecution << "Taking: ";
			for (unsigned int j = 0; j < students.at(i).getUnitsTaking().size(); j++)
				studentsOutExecution << students.at(i).getUnitsTaking().at(j)->getAbbreviation() << " ";
			studentsOutExecution << endl << "Mentored by ";
			for (unsigned int k = 0; k < teachers.size(); k++) {
				vector<Student*> pupilsTemp = teachers.at(k).getPupils();
				bool found = false;
				for (vector<Student*>::iterator it = pupilsTemp.begin(); it != pupilsTemp.end(); it++) {
					if ((*it)->getName() == students.at(i).getName()) {
						studentsOutExecution << teachers.at(k).getName() << endl;
						found = true;
						break;
					}
				}
				if (found)
					break;
			}
		}
		studentsOutExecution << endl << endl;
	}
	studentsOutExecution.close();

	cout << "Insert the filename where teachers will be saved: ";
	getline(cin, teachersFileName);
	ofstream teachersOut(teachersFileName+".txt");
	teachersOut << teachers.size() << endl;
	for (unsigned int i = 0; i < teachers.size(); i++) {
		teachers.at(i).save(teachersOut);
		teachersOut << endl << endl;
	}
	teachersOut.close();

	ofstream teachersOutExecution(teachersFileName+"_execution.txt");
	teachersOutExecution << teachers.size() << endl;
	for (unsigned int i = 0; i < teachers.size(); i++) {
		teachers.at(i).save(teachersOutExecution);
		teachersOutExecution << endl;
		if (teachers.at(i).getPupils().size() > 0) {
			teachersOutExecution << "Mentors: ";
			for (unsigned int j = 0; j < teachers.at(i).getPupils().size(); j++)
				teachersOutExecution << teachers.at(i).getPupils().at(j)->getName() << " | ";
		}
		teachersOutExecution << endl << endl;
	}
	teachersOutExecution.close();
}

bool Course::verifyUnit(string unitAbbreviation) const {
	map<string, Unit*>::const_iterator it = abbreviationToUnit.find(unitAbbreviation);

	if (it != abbreviationToUnit.end())
		return true;

	return false;
}
