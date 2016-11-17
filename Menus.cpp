#include "Menus.h"

using namespace std;

void start(string &studentsFile, string &teachersFile, string &mandatoryUnitsFile, string &optionalUnitsFile) {
	cout << "Insert the students' filename: " << endl;
	getline(cin, studentsFile);
	ifstream studentsTestFile;
	studentsTestFile.open(studentsFile);
	if (!studentsTestFile.is_open()) //If opening fails, then filename is not valid
		throw inexistentFile(studentsFile);

	cout << "Insert the teachers' filename: " << endl;
	getline(cin, teachersFile);
	ifstream teachersTestFile;
	teachersTestFile.open(teachersFile);
	if (!teachersTestFile.is_open())
		throw inexistentFile(teachersFile);

	cout << "Insert the Mandatory Units' filename: " << endl;
	getline(cin, mandatoryUnitsFile);
	ifstream mandatoryUnitsTestFile;
	mandatoryUnitsTestFile.open(mandatoryUnitsFile);
	if (!mandatoryUnitsTestFile.is_open())
		throw inexistentFile(mandatoryUnitsFile);

	cout << "Insert the Optional Units' filename: " << endl;
	getline(cin, optionalUnitsFile);
	ifstream optionalUnitsTestFile;
	optionalUnitsTestFile.open(optionalUnitsFile);
	if (!optionalUnitsTestFile.is_open())
		throw inexistentFile(optionalUnitsFile);

	//No failure in opening = good to go. Close temporary files to avoid unwanted trouble
	studentsTestFile.close();
	teachersTestFile.close();
	mandatoryUnitsTestFile.close();
	optionalUnitsTestFile.close();
}


/******************************************
* Main Menu
******************************************/

unsigned short int mainMenu() {
	unsigned short int option;
	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Course Main Menu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB << "1 - Students menu" << endl;
	cout << TAB << "2 - Teachers menu" << endl;
	cout << TAB << "3 - Units menu" << endl;
	cout << TAB << "0 - Exit" << endl << endl; //Maybe show some statistics before exiting
	cout << TAB << "Enter your option: ";
	option = readOp(0, 3);

	return option;
}

void mainOption(Course &course) {
	unsigned short int option;

	while ((option = mainMenu()))
		switch (option) {
		case 1: studentsOptions(course);
			pressToContinue();
			break;
		case 2: teachersOptions(course);
			pressToContinue();
			break;
		case 3: unitsOptions(course);
			pressToContinue();
			break;
		}

	course.save();
}

// EDIT STUDENT, TEACHER AND UNIT ADD A NEW MENU TO EACH ONE TO SET THIS OBJECTS

/******************************************
 * Students Menu
 ******************************************/

unsigned short int studentsMenu() {
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Student Main Menu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << endl;
	cout << TAB << "1 - Create Student" << endl; //DONE
	cout << TAB << "2 - Edit Student" << endl; //DONE
	cout << TAB << "3 - Remove Student" << endl; //DONE
	cout << TAB << "4 - Register Student" << endl; //TO DO
	cout << TAB << "5 - List Students" << endl; //DONE
	cout << TAB << "6 - List Registrations" << endl; //DONE
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 6);

	return option;
}


void studentsOptions(Course &course) {
	unsigned int option;

	while ((option = studentsMenu()))
		switch (option) {
		case 1:
			try {
				course.addStudent();
				cout << "Student added successfully" << endl; //Only reaches here if exception is not thrown
			}
			catch (repeatedIdentification<unsigned long> &r) {
				cout << "ERROR: A student is already identified by \"" << r.getRepIdentification() << "\"!" << endl;
			}
			catch (repeatedIdentification<string> &r) {
				cout << "ERROR: A student is already identified by \"" << r.getRepIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		case 2:
			editStudentOptions(course);
			pressToContinue();
			break;
		case 3: {
			unsigned short choice;
			cout << TAB << "1 - Identify student by name" << endl;
			cout << TAB << "2 - Identify student by code" << endl << endl;
			cout << TAB << "0 - Return to previous menu" << endl << endl;
			cout << TAB << "Enter your option: ";
			choice = readOp(0, 2);
			if (choice == 1) {
				string studentName;
				cout << "Insert the student's full name: ";
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				getline(cin, studentName);
				deleteWhitespace(studentName);
				try {
					course.removeStudent(studentName);
					cout << "Student removed successfully" << endl; //Only reaches here if exception is not thrown
				}
				catch (invalidIdentification<string> &s) {
					cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
				}
			}
			else { //choice == 2
				unsigned long studentCode;
				cout << "Insert the student's code: ";
				cin >> studentCode;
				try {
					course.removeStudent(studentCode);
					cout << "Student removed successfully" << endl;
				}
				catch (invalidIdentification<unsigned long> &s) {
					cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
				}
			}
			pressToContinue();
			break;
		}
		case 4:
			registrateStudentOptions(course);
			pressToContinue();
			break;
		case 5:
			listStudentsOptions(course);
			pressToContinue();
			break;
		case 6:
			listRegistrationsOptions(course);
			pressToContinue();
			break;
		}
}

// Edit Student Menu

unsigned short int editStudentMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Edit Student Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Edit a student's name" << endl;
	cout << TAB << "2 - Edit a student's status" << endl;
	cout << TAB << "0 - Return to previous menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}

void editStudentOptions(Course & course) {
	unsigned int option;

	while ((option = editStudentMenu()))
		switch (option) {
		case 1:
			try {
				course.editStudentName();
				cout << "Student name successfully edited" << endl; //Only reaches here if exception is not thrown
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			catch (repeatedIdentification<string> &s) {
				cout << "ERROR: There's already a student identified by \"" << s.getRepIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		case 2:
			try {
				course.editStudentStatus();
				cout << "Student name successfully edited" << endl; //Only reaches here if exception is not thrown
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;

		}
}


// Registrate Student MENU


unsigned short int registrateStudentMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Register Student Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Register a random student" << endl;
	cout << TAB << "2 - Register a specific student" << endl;
	cout << TAB << "0 - Return to previous menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}

void registrateStudentOptions(Course & course) {
	unsigned int option;

	while ((option = registrateStudentMenu()))
		switch (option) {
		case 1:
			//course.registerRandomStudent();
			pressToContinue();
			break;
		case 2:
			try {
				//course.registerSpecificStudent();
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			catch (invalidIdentification<unsigned long> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			catch (alreadyRegistered<string> &s) {
				cout << "ERROR: Student \"" << s.getIdentifier() << "\" is already registered!" << endl;
			}
			catch (alreadyRegistered<unsigned long> &s) {
				cout << "ERROR: Student \"" << s.getIdentifier() << "\" is already registered!" << endl;
			}
			pressToContinue();
			break;

		}
}


//LIST STUDENTS MENU

unsigned short int listStudentsMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "List Students Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Show students alphabetically" << endl;
	cout << TAB << "2 - Show students by curricular year" << endl;
	cout << TAB << "3 - Show students by status" << endl;
	cout << TAB << "4 - Show students by average" << endl;
	cout << TAB << "5 - Show a single student" << endl;
	cout << TAB << "6 - Show registered students" << endl;
	cout << TAB << "7 - Show un-registered students" << endl;
	cout << TAB << "0 - Return to students menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 7);

	return option;
}


void listStudentsOptions(Course & course) {
	unsigned int option;

	while ((option = listStudentsMenu()))
		switch (option) {
		case 1:
			course.showStudents(sortByName);
			pressToContinue();
			break;
		case 2: {
			cout << "Insert the curricular year: ";
			unsigned short int year = readOp(1, 5);
			course.showStudents(sortByCurricularYear);
			pressToContinue();
			break;
		}
		case 3: {
			string statusToShow;
			cout << "Insert the status you wish to be listed: ";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, statusToShow);
			deleteWhitespace(statusToShow);
			course.showStudentsStatus(statusToShow);
			pressToContinue();
			break;
		}
		case 4:
			course.showStudents(sortByAverage);
			pressToContinue();
			break;
		case 5:
			showStudentOptions(course);
			pressToContinue();
			break;
		case 6:
			course.showRegisteredStudents();
			pressToContinue();
			break;
		case 7:
			course.showUnregisteredStudents();
			pressToContinue();
			break;
		}
}

// Show a Student MENU

unsigned short int showStudentMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Show a Specific Student Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Search by name" << endl;
	cout << TAB << "2 - Search by code" << endl;
	cout << TAB << "0 - Return to menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}

void showStudentOptions(Course & course) {
	unsigned int option;

	while ((option = showStudentMenu()))
		switch (option) {
		case 1: {
			cout << "Insert the student's name: " << endl;
			string studentName;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, studentName);
			deleteWhitespace(studentName);
			try {
				course.showStudent(studentName);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
		case 2: {
			cout << "Insert the student's code: " << endl;
			unsigned long studentCode;
			cin >> studentCode;
			try {
				course.showStudent(studentCode);
			}
			catch (invalidIdentification<unsigned long> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
		}
}


// LIST REGISTRATIONS MENU

unsigned short int listRegistrationsMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "List Registrations Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Show registrations by unit" << endl;
	cout << TAB << "2 - Show registrations by student" << endl;
	cout << TAB << "3 - Show registrations by year" << endl;
	cout << TAB << "4 - Show registrations of all students" << endl;
	cout << TAB << "0 - Return to menu." << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 4);

	return option;
}

void listRegistrationsOptions(Course & course) {
	unsigned int option;

	while ((option = listRegistrationsMenu()))
		switch (option) {
		case 1: {
			try {
				course.showUnitRegistrations();
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No unit identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
		case 2:
			studentRegistrationsOptions(course);
			pressToContinue();
			break;
		case 3: {
			unsigned long yearToShow;
			yearToShow = readOp(1, 5);
			course.showYearRegistrations(yearToShow);
			pressToContinue();
			break;
		}
		case 4:
			course.showAllStudentsRegistrations();
			pressToContinue();
			break;
		}
}


// Registration for one student MENU

unsigned short int studentRegistrationsMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Show Registration by a Specific Student Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Search by name" << endl;
	cout << TAB << "2 - Search by code" << endl;
	cout << TAB << "0 - Return to list registrations menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}

void studentRegistrationsOptions(Course & course) {
	unsigned int option;

	while ((option = studentRegistrationsMenu()))
		switch (option) {
		case 1: {
			cout << "Insert the student's name: " << endl;
			string studentName;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, studentName);
			deleteWhitespace(studentName);
			try {
				course.showStudentUnits(studentName);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
		case 2: {
			cout << "Insert the student's code: " << endl;
			unsigned long studentCode;
			cin >> studentCode;
			try {
				course.showStudentUnits(studentCode);
			}
			catch (invalidIdentification<unsigned long> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
		}
}


/******************************************
 * Teachers Menu
 ******************************************/

unsigned short int teachersMenu() {
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Teacher Main Menu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << endl;
	cout << TAB << "1 - Create Teacher" << endl; //DONE
	cout << TAB << "2 - Edit Teacher" << endl; //DONE
	cout << TAB << "3 - Remove Teacher" << endl; //DONE
	cout << TAB << "4 - List Teachers" << endl; //DONE
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 4);

	return option;
}


void teachersOptions(Course & course) {
	unsigned int option;

	while ((option = teachersMenu()))
		switch (option) {
		case 1:
			try {
				course.addTeacher();
				cout << "Teacher successfully created" << endl;
			}
			catch (repeatedIdentification<string> &s) {
				cout << "ERROR: There's a teacher identified by \"" << s.getRepIdentification() << "\" already!" << endl;
			}
			pressToContinue();
			break;
		case 2:
			editTeacherOptions(course);
			pressToContinue();
			break;
		case 3: {
			string teacherID;
			cout << "Insert the teacher's full name or his/her code: ";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, teacherID);
			deleteWhitespace(teacherID);
			try {
				course.removeTeacher(teacherID);
				cout << "Teacher removed successfully" << endl; //Only reaches here if exception is not thrown
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No teacher identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
		case 4:
			listTeachersOptions(course);
			pressToContinue();
			break;
		}
}

// Edit Teacher Menu

unsigned short int editTeacherMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Edit Teacher Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Edit a teacher's name" << endl;
	cout << TAB << "2 - Edit a teacher's code" << endl;
	cout << TAB << "3 - Add a new unit taught by a teacher" << endl;
	cout << TAB << "0 - Return to previous menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 3);

	return option;
}

void editTeacherOptions(Course & course) {
	unsigned int option;

	while ((option = editTeacherMenu()))
		switch (option) {
		case 1:
			try {
				course.editTeacherName();
				cout << "Teacher edited successfully" << endl;
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No teacher identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			catch (repeatedIdentification<string> &s) {
				cout << "ERROR: There's a teacher identified by \"" << s.getRepIdentification() << "\" already!" << endl;
			}
			pressToContinue();
			break;
		case 2:
			try {
				course.editTeacherCode();
				cout << "Teacher edited successfully" << endl;
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No teacher identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			catch (repeatedIdentification<string> &s) {
				cout << "ERROR: There's a teacher identified by \"" << s.getRepIdentification() << "\" already!" << endl;
			}
			pressToContinue();
			break;
		case 3:
			try {
				course.teacherAddUnitTaught();
				cout << "Teacher edited successfully" << endl;
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No teacher identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
}

//LIST Teachers MENU

unsigned short int listTeachersMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "List Teachers Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Show teachers alphabetically" << endl; //Done
	cout << TAB << "2 - Show a teacher" << endl;  //Done
	cout << TAB << "0 - Return to students menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}


void listTeachersOptions(Course & course) {
	unsigned int option;

	while ((option = listTeachersMenu()))
		switch (option) {
		case 1:
			course.showTeachers(sortTByName);
			pressToContinue();
			break;
		case 2:
			showTeacherOptions(course);
			pressToContinue();
			break;
		}
}

// Show a Teacher MENU

unsigned short int showTeacherMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Show a Specific Teacher Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Show teacher specified by name or code" << endl; //done
	cout << TAB << "2 - Show teacher responsible for specified unit" << endl; //done
	cout << TAB << "3 - Show teacher that mentors specified student" << endl; //done
	cout << TAB << "0 - Return to previous menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 3);

	return option;
}

void showTeacherOptions(Course & course) {
	unsigned int option;

	while ((option = showTeacherMenu()))
		switch (option) {
		case 1: {
			cout << "Insert the teacher's full name or code: " << endl;
			string teacherID;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, teacherID);
			deleteWhitespace(teacherID);
			try {
				course.showTeacher(teacherID);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No teacher identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
		case 2: {
			cout << "Insert the unit's abbreviation: " << endl;
			string unitAbbreviation;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, unitAbbreviation);
			deleteWhitespace(unitAbbreviation);
			if (!course.verifyUnit(unitAbbreviation))
				cout << "ERROR: No unit identified by \"" << unitAbbreviation << "\"!" << endl;
			else {
				map<string, Unit*>::const_iterator it = course.getMap().find(unitAbbreviation);
				course.showTeacher(it->second);
			}
			pressToContinue();
			break;
		}

		case 3: {
			showTeacherPupilOptions(course);
			pressToContinue();
			break;
		}
		}
}

// Show a Teacher by Pupil MENU

unsigned short int showTeacherPupilMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Show a Teacher by Pupil Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Specify pupil by name" << endl; //done
	cout << TAB << "2 - Specify pupil by code" << endl; //done
	cout << TAB << "0 - Return to previous menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}

void showTeacherPupilOptions(Course & course) {
	unsigned int option;

	while ((option = showTeacherPupilMenu()))
		switch (option) {
		case 1: {
			cout << "Insert the pupil's full name: " << endl;
			string pupilName;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, pupilName);
			deleteWhitespace(pupilName);
			try {
				course.showTeacherPupilByName(pupilName);
			}
			catch (invalidIdentification<string> &s) {
				cout << "Student identified by \"" << s.getInvIdentification() << "\" does not exist or has not been assigned a mentor yet!" << endl;
			}
			pressToContinue();
			break;
		}
		case 2: {
			cout << "Insert the pupil's code: " << endl;
			unsigned long pupilCode;
			cin >> pupilCode;
			try {
				course.showTeacherPupilByCode(pupilCode);
			}
			catch (invalidIdentification<unsigned long int> &s) {
				cout << "Student identified by \"" << s.getInvIdentification() << "\" does not exist or has not been assigned a mentor yet!" << endl;
			}
			pressToContinue();
			break;
		}
		}
}



/******************************************
 * Units Menu
 ******************************************/

unsigned short int unitsMenu() {
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Units Main Menu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << endl;
	cout << TAB << "1 - Edit Unit" << endl; //done
	cout << TAB << "2 - List Units" << endl; //done
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}


void unitsOptions(Course & course) {
	unsigned int option;

	while ((option = unitsMenu()))
		switch (option) {
		case 1:
			editUnitsOptions(course);
			pressToContinue();
			break;
		case 2:
			listUnitsOptions(course);
			pressToContinue();
			break;
		}
}

// Edit Units Menu

unsigned short int editUnitsMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Edit Units Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Edit a unit's name" << endl; //Done
	cout << TAB << "2 - Edit a unit's abbreviation" << endl;  //Done
	cout << TAB << "3 - Edit a unit's scientific area" << endl; //Done
	cout << TAB << "0 - Return to previous menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 3);

	return option;
}


void editUnitsOptions(Course & course) {
	unsigned int option;

	while ((option = editUnitsMenu()))
		switch (option) {
		case 1:
			try {
				course.editUnitName();
				cout << "Unit successfully edited" << endl;
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No unit identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			catch (repeatedIdentification<string> &s) {
				cout << "ERROR: Unit with name \"" << s.getRepIdentification() << "\" already exists!" << endl;
			}
			pressToContinue();
			break;
		case 2: {
			try {
				course.editUnitAbbreviation();
				cout << "Unit successfully edited" << endl;
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No unit identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			catch (repeatedIdentification<string> &s) {
				cout << "ERROR: Unit with abbreviation \"" << s.getRepIdentification() << "\" already exists!" << endl;
			}
			pressToContinue();
			break;
		}
		case 3:
			try {
				course.editUnitScientificArea();
				cout << "Unit successfully edited" << endl;
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No unit identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
}


// List Units Menu


unsigned short int listUnitsMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "List Units Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Show all units" << endl; //done
	cout << TAB << "2 - Show units of a specific year" << endl;  //done
	cout << TAB << "3 - Show mandatory units" << endl; //done
	cout << TAB << "4 - Show optional units" << endl; //done
	cout << TAB << "5 - Show a specific unit" << endl; //done
	cout << TAB << "6 - Show units of a specific scientific area" << endl; //done
	cout << TAB << "0 - Return to previous menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 6);

	return option;
}


void listUnitsOptions(Course & course) {
	unsigned int option;

	while ((option = listUnitsMenu()))
		switch (option) {
		case 1:
			course.showUnits();
			pressToContinue();
			break;
		case 2: {
			cout << "Insert the curricular year: " << endl;
			unsigned short int year;
			year = readOp(1, 5);
			course.showYearUnit(year);
			pressToContinue();
			break;
		}
		case 3:
			course.showMandatoryUnit();
			pressToContinue();
			break;
		case 4:
			course.showOptionalUnit();
			pressToContinue();
			break;
		case 5:
			try {
				course.showSpecificUnit();
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No unit identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		case 6: {
			string scientificArea;
			cout << "Insert the scientific area: ";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, scientificArea);
			deleteWhitespace(scientificArea);
			try{
			course.showUnitsofScientificArea(scientificArea);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No unit identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			pressToContinue();
			break;
		}
		}
}