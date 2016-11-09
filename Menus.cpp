#include "Menus.h"
#include "Utils.h"
#include "Course.h"

using namespace std;

bool inicialInformation(string &studentsFile, string &teachersFile, string &mandatoryUnitsFile, string &optionalUnitsFile) {
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
	cout << endl;
    cout << TAB_BIG << "----------------------" << endl;
    cout << TAB_BIG << "---Course Main Menu---" << endl;
    cout << TAB_BIG << "----------------------" << endl;
	cout << TAB << "1 - Students menu" << endl;
	cout << TAB << "2 - Teachers menu" << endl;
	cout << TAB << "3 - Units menu" << endl;
	cout << TAB << "0 - Exit" << endl << endl; //Maybe show some statistics before exiting
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
	cout << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << TAB_BIG << "---Student MainMenu---" << endl;
	cout << TAB_BIG << "----------------------" << endl;
	cout << endl;
	cout << TAB << "1 - Create Student" << endl;
	cout << TAB << "2 - Edit Student" << endl;
	cout << TAB << "3 - Remove Student" << endl;
	cout << TAB << "4 - Registrate Student" << endl; //No - loop to another looping menu that allows to choose to registrate a random student (the first one in the vector that's not registered) or a specific one. These two will converge to the single function registrateStudent
	cout << TAB << "5 - List Students" << endl;
	/*cout << TAB << "6 - Assign Tutor" << endl; //No - tutor is assigned in the end of registration process of a student*/
	cout << TAB << "6 - List Registrations" << endl; //Redirects to a menu exactly equal to Student Menu... ?!
	cout << TAB << "0 - Return to Main Menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 7);

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
	cout << TAB << "1 - Show students alphabetically" << endl;
	cout << TAB << "2 - Show students by unit" << endl; //Redirects to a loop - ask for unit abbreviation (throw exception using invalidIdentification if doesn't exist) then call function with unit when valid
	cout << TAB << "3 - Show students by curricular year" << endl; //Before calling function, read which year is it with read_op (or equivalent function) and then call with the value
	cout << TAB << "4 - Show students by status" << endl;
	cout << TAB << "5 - Show students by average" << endl;
	cout << TAB << "6 - Show a student" << endl;
	//In comment for now... but what do you think?
	/*cout << TAB << "7 - Show registered students" << endl;
	cout << TAB << "8 - Show un-registered students" << endl;*/
	cout << TAB << "0 - Return to students menu" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 6);

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

