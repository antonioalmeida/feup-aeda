#include "Menus.h"
#include "Utils.h"
#include "Course.h"

using namespace std;

bool inicialInformation(string &studentsFile, string &teachersFile, string &mandatoryUnitsFile, string &optionalUnitsFile) {
    cout << "Insert the students' filename: " << endl;
    getline(cin, studentsFile);
    ifstream studentsTestFile;
    studentsTestFile.open(studentsFile);
    if(!studentsTestFile.is_open()) //If opening fails, then filename is not valid
        return false;
    
    cout << "Insert the teachers' filename: " << endl;
    getline(cin, teachersFile);
    ifstream teachersTestFile;
    teachersTestFile.open(teachersFile);
    if(!teachersTestFile.is_open())
        return false;
    
    cout << "Insert the Mandatory Units' filename: " << endl;
    getline(cin, mandatoryUnitsFile);
    ifstream mandatoryUnitsTestFile;
    mandatoryUnitsTestFile.open(mandatoryUnitsFile);
    if(!mandatoryUnitsTestFile.is_open())
        return false;
    
    cout << "Insert the Optional Units' filename: " << endl;
    getline(cin, optionalUnitsFile);
    ifstream optionalUnitsTestFile;
    optionalUnitsTestFile.open(optionalUnitsFile);
    if(!optionalUnitsTestFile.is_open())
        return false;
    
    //No failure in opening = good to go. Close temporary files to avoid unwanted trouble
    studentsTestFile.close();
    teachersTestFile.close();
    mandatoryUnitsTestFile.close();
    optionalUnitsTestFile.close();
    return true;
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
	cout << TAB << "1 - Create Student" << endl;
	cout << TAB << "2 - Edit Student" << endl;
	cout << TAB << "3 - Remove Student" << endl;
	cout << TAB << "4 - Registrate Student" << endl;
	cout << TAB << "5 - List Students" << endl;
	cout << TAB << "6 - List Registrations" << endl;
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 6);

	return option;
}


void studentsOptions(Course &course) {
	unsigned int option;

	while ((option = studentsMenu()))
		switch (option) {
		case 1: course.addStudent();
			break;
		case 2:
			course.setStudent();
			break;
        case 3:
            course.removeStudent();
            break;
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


// Registrate Student MENU


unsigned short int registrateStudentMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Registrate Student Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Random Student" << endl;
	cout << TAB << "2 - Specific Student" << endl;
	cout << TAB << "0 - Return to menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}

void registrateStudentOptions(Course & course) {
	unsigned int option;

	while ((option = registrateStudentMenu()()))
		switch (option) {
		case 1: 
			//Random Student
			course.RegistrateStudent();
			break;
		case 2:
		//This one with parameter to choose a specific student
			course.RegistrateStudent();
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
	cout << TAB << "2 - Show students by unit" << endl; 
	cout << TAB << "3 - Show students by curricular year" << endl;
	cout << TAB << "4 - Show students by status" << endl;
	cout << TAB << "5 - Show students by average" << endl;
	cout << TAB << "6 - Show a student" << endl;
	cout << TAB << "7 - Show registered students" << endl;
	cout << TAB << "8 - Show un-registered students" << endl;
	cout << TAB << "0 - Return to students menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 8);

	return option;
}


void listStudentsOptions(Course & course) {
	unsigned int option;

	while ((option = listStudentsMenu()))
		switch (option) {
		case 1:
            course.showStudents(sortByName);
			break;
		case 2:
            bool validInput = false;
            string unitAbbreviation
            cout << "Insert the course's unit : "
            do {
                getline(cin, unitAbbreviation);
                deleteWhitespace(&unitAbbreviation);
                validInput = verifyUnit(unitAbbreviation);
            } while(!validInput);
             
			course.showUnitStudents();
			break;
		case 3:
			cout << "Insert the curricular year: " ;
			unsigned short int year= readOp(1,5);
			course.showYearStudents(year);
			break;
		case 4:
			course.showStatusStudents();
			break;
		case 5:
			course.showStudents(sortByAverage);
			break;
		case 6:
			showStudentOptions(course);
			break;
		case 7:
			course.showRegisteredStudent();
			break;
		case 8:
			course.showUnRegisteredStudent();
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

	while ((option = showStudentMenu()()))
		switch (option) {
		case 1: 
            cout << "What is the student's name? : " << endl;
            string studentName;
            getline(cin, studentName);
            deleteWhitespace(&studentName);
 			course.showStudent(studentName);
			break;
		case 2:
            cout << "What is the sudent's code? : " << endl;
            unsigned long int studentCode;
            cin >> studentCode;
			course.showStudent(studentCode);
			break;
		}
}


// LIST REGISTRATIONS MENU

unsigned short int listRegistrationsMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "List Registrations Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Show Registrations by Unit" << endl;
	cout << TAB << "2 - Show Registrations by Student" << endl; 
	cout << TAB << "3 - Show Registrations by Year" << endl;
	cout << TAB << "4 - Show all Registrations" << endl;
	cout << TAB << "0 - Return to menu." << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 4);

	return option;
}

void listRegistrationsOptions(Course & course) {
	unsigned int option;

	while ((option = listRegistrationsMenu()()))
		switch (option) {
		case 1: 
		//read and check Unit
			course.showUnitRegistrations();
			break;
		case 2:
			studentRegistrationsOptions(course);
			break;
		case 3:
		//read and check year
			course.showYearRegistrations();
			break;
		case 4:
			course.showRegistrations();
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
	cout << TAB << "0 - Return to menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 2);

	return option;
}

void studentRegistrationsOptions(Course & course) {
	unsigned int option;

	while ((option = studentRegistrationsMenu()()))
		switch (option) {
		case 1: 
			// read name and check, and insert like a parameter
			//find here and insert direct a pointer to a student?
			course.showRegistration();
			break;
		case 2:
			// read code and check, and insert like a parameter
			//same above
			course.showRegistration();
			break;
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
	cout << TAB << "1 - Create Teacher" << endl;
	cout << TAB << "2 - Edit Teacher" << endl;
	cout << TAB << "3 - Remove Teacher" << endl;
	cout << TAB << "4 - List Teachers" << endl;
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
			course.addTeacher();
			break;
		case 2:
			course.setTeacher();
			break;
        case 3:
            course.removeTeacher();
            break;
		case 4:
			listTeachersOptions(course);
			break;
	}
}

//LIST Teachers MENU

unsigned short int listTeachersMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "List Teachers Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Show teachers alphabetically" << endl;
	cout << TAB << "2 - Show a teacher" << endl; 
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
			course.showAllTeachers();
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
	cout << TAB << "1 - Search by name" << endl;
	cout << TAB << "2 - Search by code" << endl;
	cout << TAB << "3 - Search by unit" << endl;
	cout << TAB << "4 - Search by pupil" << endl; //It is correct here??
	cout << TAB << "0 - Return to menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 4);

	return option;
}

void showTeacherOptions(Course & course) {
	unsigned int option;

	while ((option = showTeacherMenu()()))
		switch (option) {
		case 1: 
			// read name and check, and insert like a parameter
			course.showTeacher();
			break;
		case 2:
			// read code and check, and insert like a parameter
			course.showTeacher();
			break;
		case 2:
			// read unit and check, and insert like a parameter
			course.showTeacher();
			break;
		case 2:
			// read pupil and check if exist, and insert like a parameter
			course.showTeacher();
			break;
		}
}

/******************************************
 * Units Menu
 ******************************************/
// CREATE, EDIT AND REMOVE -> Can cause conflicts with teachers and students?

unsigned short int unitsMenu() {
	unsigned short int option;

	clearScreen();
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Units Main Menu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << endl;
	cout << TAB << "1 - Create Unit" << endl;
	cout << TAB << "2 - Edit Unit" << endl;
	cout << TAB << "3 - Remove Unit" << endl;
	cout << TAB << "4 - List Units" << endl;
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 4);

	return option;
}


void unitsOptions(Course & course) {
	unsigned int option;

	while ((option = unitsMenu()))
		switch (option) {
		case 1: course.addUnit();
			break;
		case 2:
			course.setUnit();
			break;
        case 3:
            course.removeUnit();
            break;
		case 4:
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
	cout << TAB << "1 - Show units alphabetically" << endl; //no interest i think
	cout << TAB << "2 - Show units by year" << endl; 
	cout << TAB << "3 - Show mandatory units" << endl;
	cout << TAB << "4 - Show optional units" << endl;
	cout << TAB << "5 - Show a unit" << endl;
	cout << TAB << "0 - Return to students menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = readOp(0, 5);

	return option;
}


void listUnitsOptions(Course & course) {
	unsigned int option;

	while ((option = listUnitsMenu()))
		switch (option) {
		case 1: 
			course.showUnits();
			break;
		case 2:
			cout << "Insert the curricular year: " << endl;
			unsigned short int year= readOp(1,5);
			course.showYearUnit(year);
			break;
		case 3:
			course.showMandatoryUnit();
			break;
		case 4:
			course.showOptionalUnit();
			break;
		case 5:
		//read code 
			course.showUnit();
			break;
		}
}
