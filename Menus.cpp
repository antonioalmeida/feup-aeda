#include "Menus.h"

bool inicialInformation(string &course, string &studentsFile, string &teachersFile, string &mandatoryUnitsFile, string &optionalUnitsFile) {
    
    cout << "Insert the courses's name: " << endl;
    getline(cin, course);
    
    cout << "Insert the students' filename: " << endl;
    getline(cin, studentsFile);
    ifstream studentsTestFile;
    studentsTestFile.open(studentsFile);
    if(!clientTestFile.is_open()) //If opening fails, then filename is not valid
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

	cout <<endl<< TAB_BIG << "MENU" << endl;
	cout << endl;
    cout << TAB_BIG << "----------------------" << endl;
    cout << TAB_BIG << "-----Main Menu------" << endl;
    cout << TAB_BIG << "----------------------" << endl;
	cout << TAB << "1 - Students menu" << endl;
	cout << TAB << "2 - Teachers menu" << endl;
	cout << TAB << "3 - Units menu" << endl;
	cout << TAB << "0 - Exit" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 3);

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


/******************************************
 * Students Menu
 ******************************************/

unsigned short int studentsMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Students Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Create Student" << endl;
	cout << TAB << "2 - Edit Student" << endl;
	cout << TAB << "3 - Remove Student" << endl;
	cout << TAB << "4 - Registrate Student" << endl;
	cout << TAB << "5 - List Students" << endl;
	cout << TAB << "6 - Assign Tutor" << endl;
	cout << TAB << "7 - List Registrations" << endl;
	cout << TAB << "0 - Return to main menu." << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 7);

	if (option == 0)
		return 0;

	return option;

}


void studentsOptions(Course & course) {
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
			course.registrateStudent();
			break;
		case 5:
			listStudentsOptions(course);
			break;
		case 6:
			course.assignTutor();
			break;
		case 7:
			listRegistrationsOptions(course);
			break;
		}
}

//LIST STUDENTS MENU

unsigned short int listStudentsMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "List Students Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Show Students Alphabetically" << endl;
	cout << TAB << "2 - Show Students by Unit" << endl;
	cout << TAB << "3 - Show Students by Curricular Year" << endl;
	cout << TAB << "4 - Show Students by Certain Status" << endl;
	cout << TAB << "5 - Show Students by Average" << endl;
	cout << TAB << "6 - Show a Student" << endl;
	cout << TAB << "0 - Return to menu." << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 6);

	if (option == 0)
		return 0;

	return option;
}


void listStudentsOptions(Course & course) {
	unsigned int option;

	while ((option = listStudentsMenu()))
		switch (option) {
		case 1: course.showAllStudents();
			break;
		case 2:
			course.showUnitStudents();
			break;
		case 3:
			course.showYearStudents();
			break;
		case 4:
			course.showStatusStudents();
			break;
		case 5:
			course.showAverageStudents();
			break;
		case 6:
			course.showStudent();
			break;
		}
}

// LIST REGISTRATIONS MENU

unsigned short int listRegistrationsMenu() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "List Registrations Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Create Student" << endl;
	cout << TAB << "2 - Edit Student" << endl;
	cout << TAB << "3 - Remove Student" << endl;
	cout << TAB << "4 - Registrate Student" << endl;
	cout << TAB << "5 - List Students" << endl;
	cout << TAB << "6 - Assign Tutor" << endl;
	cout << TAB << "7 - List Registrations" << endl;
	cout << TAB << "0 - Return to menu." << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 7);

	if (option == 0)
		return 0;

	return option;

}

void listRegistrationsOptions(Course & course) {
	unsigned int option;

	while ((option = listRegistrationsMenu()()))
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
			course.registrateStudent();
			break;
		case 5:
			optionsListStudents(course);
			break;
		case 6:
			course.assignTutor();
			break;
		case 7:
			optionsListRegistrations(course);
			break;
		}
}

