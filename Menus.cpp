#include "Menus.h"

bool infoInicial(string & course, string & StudentsFile, string & TeachersFile, string & MandatoryUnitsFile,string & OptionalUnitsFile)
{
	cout << "Insert course's name: "; 
	getline(cin, course);

	ask_fileNames(StudentsFile, TeachersFile, MandatoryUnitsFile, OptionalUnitsFile);

	return true;

}


/******************************************
* Start Menu
******************************************/

unsigned short int startMenu() {
	unsigned short int option;

	clearScreen();

	cout <<endl<< TAB_BIG << "MENU" << endl;
	cout << endl;
	cout << TAB<<"Welcome to students registration system"<<endl;
	cout << TAB << "1 - Students Manager" << endl;
	cout << TAB << "2 - Teachers Manager" << endl;
	cout << TAB << "3 - Units Manager" << endl;
	cout << TAB << "0 - Exit" << endl << endl;
	cout << TAB << "Enter your option: ";
	option = read_op(0, 3);

	if (option == 0)
		return 0;

	return option;
}

void startOptions(Course & course) 
{
	unsigned int option;

	while ((option = startMenu()))
		switch (option) {
		case 1: optionsStudents(course);
			break;
		case 2: optionsTeachers(course);
			break;
		case 3: optionsUnits(course);
			break;
		
		}

	course.save();
}


/******************************************
 * Students Manager
 ******************************************/
unsigned short int menuStudents() {
	unsigned short int option;

	clearScreen();
	cout << TAB_BIG << "Students Manager Menu" << endl;
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


void optionsStudents(Course & course) {
	unsigned int option;


	while ((option = menuStudents()))
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
unsigned short int menuListStudents() {
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


void optionsListStudents(Course & course) {
	unsigned int option;

	while ((option = menuListStudents()))
		switch (option) {
		case 1: course.showAllStudent();
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

unsigned short int menuListRegistrations() {
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


void optionsListRegistrations(Course & course) {
	unsigned int option;


	while ((option = menuListRegistrations()))
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

