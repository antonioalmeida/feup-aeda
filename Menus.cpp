#include <iostream>

#include "Menus.h"
#include "Utils.h"
#include "Course.h"

using namespace std;

void start(string &studentsFile, string &teachersFile, string &mandatoryUnitsFile, string &optionalUnitsFile) {
    cout << "Insert the students' filename: " << endl;
    getline(cin, studentsFile);
    ifstream studentsTestFile;
    studentsTestFile.open(studentsFile);
    if(!studentsTestFile.is_open()) //If opening fails, then filename is not valid
        throw inexistentFile(studentsFile);
    
    cout << "Insert the teachers' filename: " << endl;
    getline(cin, teachersFile);
    ifstream teachersTestFile;
    teachersTestFile.open(teachersFile);
    if(!teachersTestFile.is_open())
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
			break;
		case 2: teachersOptions(course);
			break;
		case 3: unitsOptions(course);
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
	cout << TAB << "1 - Create Student" << endl; //PARTIALLY DONE (I'LL FINISH IT - CYRIL)
	cout << TAB << "2 - Edit Student" << endl; //DONE
	cout << TAB << "3 - Remove Student" << endl; //DONE
	cout << TAB << "4 - Registrate Student" << endl; //TO DO
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
			break;
		case 2:
			editStudentOptions(course);
			break;
		case 3: {
			unsigned short choice;
			cout << TAB << "1 - Identify student by name" << endl;
			cout << TAB << "2 - Identify student by code" << endl << endl;
			cout << TAB << "Enter your option: ";
			choice = readOp(1, 2);
			if (choice == 1) {
				string studentName;
				cout << "Insert the student's full name: ";
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
				cin >> studentCode; //Check for invalid input (later)
				try {
					course.removeStudent(studentCode);
					cout << "Student removed successfully" << endl;
				}
				catch (invalidIdentification<unsigned long> &s) {
					cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
				}
			}
			break;
		}
		case 4:
			registrateStudentOptions(course);
			break;
		case 5:
			listStudentsOptions(course);
			break;
		case 6:
			listRegistrationsOptions(course);
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
			break;
		case 2:
			try {
				course.editStudentStatus();
				cout << "Student name successfully edited" << endl; //Only reaches here if exception is not thrown
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			break;

		}
}


// Registrate Student MENU


unsigned short int registrateStudentMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Registrate Student Menu" << endl;
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
			//Random Student
			//course.registrateStudent();
			break;
		case 2:
		//This one with parameter to choose a specific student
			//course.registrateStudent();
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
			break;
		case 2: {
			cout << "Insert the curricular year: ";
			unsigned short int year = readOp(1, 5);
			course.showStudents(sortByCurricularYear);
			break;
		}
		case 3: {
			string statusToShow;
			cout << "Insert the status you wish to be listed: ";
			getline(cin, statusToShow);
			deleteWhitespace(statusToShow);
			course.showStudentsStatus(statusToShow);
			break;
		}
		case 4:
			course.showStudents(sortByAverage);
			break;
		case 5:
			showStudentOptions(course);
			break;
		case 6:
			course.showRegisteredStudents();
			break;
		case 7:
			course.showUnregisteredStudents();
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
			getline(cin, studentName);
			deleteWhitespace(studentName);
			try {
				course.showStudent(studentName);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			break;
		}
		case 2: {
			cout << "Insert the student's code: " << endl;
			unsigned long studentCode;
			cin >> studentCode; //Check for invalid input (later)
			try {
				course.showStudent(studentCode);
			}
			catch (invalidIdentification<unsigned long> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
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
			break;
		}
		case 2:
			studentRegistrationsOptions(course);
			break;
		case 3: {
			unsigned long yearToShow;
			yearToShow = readOp(1, 5);
			course.showYearRegistrations(yearToShow);
			break;
		}
		case 4:
			course.showAllStudentsRegistrations();
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
			getline(cin, studentName);
			deleteWhitespace(studentName);
			try {
				course.showStudentUnits(studentName);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			break;
		}
		case 2: {
			cout << "Insert the student's code: " << endl;
			unsigned long studentCode;
			cin >> studentCode; //Check for invalid input (later)
			try {
				course.showStudentUnits(studentCode);
			}
			catch (invalidIdentification<unsigned long> &s) {
				cout << "ERROR: No student identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
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
			catch(repeatedIdentification<string> &s){
				cout << "ERROR: There's a teacher identified by \"" << s.getRepIdentification() << "\" already!" << endl;
			}
			break;
		case 2:
			editTeacherOptions(course);
			break;
		case 3: {
			string teacherID;
			cout << "Insert the teacher's full name or his/her code: ";
			getline(cin, teacherID);
			deleteWhitespace(teacherID);
			try {
				course.removeTeacher(teacherID);
				cout << "Teacher removed successfully" << endl; //Only reaches here if exception is not thrown
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No teacher identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			break;
		}
		case 4:
			listTeachersOptions(course);
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
			break;
		case 3:
			try {
				course.teacherAddUnitTaught();
				cout << "Teacher edited successfully" << endl;
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No teacher identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
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
			break;
		case 2:
			showTeacherOptions(course);
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
			getline(cin, teacherID);
			deleteWhitespace(teacherID);
			try {
				course.showTeacher(teacherID);
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No teacher identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			break;
		}
		case 2: {
			cout << "Insert the unit's abbreviation: " << endl;
			string unitAbbreviation;
			getline(cin, unitAbbreviation);
			deleteWhitespace(unitAbbreviation);
			map<string, Unit*>::const_iterator it = course.getMap().find(unitAbbreviation);
			if (it == course.getMap().end())
				cout << "ERROR: No unit identified by \"" << unitAbbreviation << "\"!" << endl;
			else
				course.showTeacher(it->second);
			break;
		}
		case 3: {
			showTeacherPupilOptions(course);
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
			cout << "Insert the pupil's name: " << endl;
			string pupilName;
			getline(cin, pupilName);
			deleteWhitespace(pupilName);
			course.showTeacherPupil(pupilName);
			break;
		}
		case 2: {
			cout << "Insert the pupil's code: " << endl;
			unsigned long pupilCode;
			cin >> pupilCode; //Check for invalid input (later)
			course.showTeacherPupil(pupilCode);
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
	cout << TAB << "1 - Edit Unit" << endl; //TO DO (Is it really necessary though? Might want to have it not implemented at first and then later might put it in)
	cout << TAB << "2 - List Units" << endl; //DONE
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
			//course.setUnit();
			break;
		case 2:
			listUnitsOptions(course);
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
			break;
		case 2: {
			cout << "Insert the curricular year: " << endl;
			unsigned short int year;
			year = readOp(1, 5);
			course.showYearUnit(year);
			break;
		}
		case 3:
			course.showMandatoryUnit();
			break;
		case 4:
			course.showOptionalUnit();
			break;
		case 5:
			try {
				course.showSpecificUnit();
			}
			catch (invalidIdentification<string> &s) {
				cout << "ERROR: No unit identified by \"" << s.getInvIdentification() << "\"!" << endl;
			}
			break;
		case 6: {
			string scientificArea;
			cout << "Insert the scientific area: ";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, scientificArea);
			deleteWhitespace(scientificArea);
			course.showUnitsofScientificArea(scientificArea);
			break;
		}
		}
}
