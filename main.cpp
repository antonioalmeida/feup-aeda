#include <iostream>
#include "Menus.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char **argv) {

	srand(time(NULL));
	std::string course, studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName;

	try {
		start(studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName);
	}
	catch (inexistentFile &s) {
		cout << "ERROR: File \"" << s.getInexistentFileName() << "\" not found! Exiting..." << endl;
		pressToContinue();
		return 1;
	}

	Course mieic(studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName);
	mainOption(mieic);
	pressToContinue();

	return 0;
}
