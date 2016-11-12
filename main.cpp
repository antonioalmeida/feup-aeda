#include <iostream>
#include "Menus.h"

using namespace std;

int main(int argc, char **argv) {
    
    std::string course, studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName;
    
	try {
		start(studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName);
	}
	catch(inexistentFile &s){
		cout << "ERROR: File \"" << s.getInexistentFileName() << "\" not found! Exiting..." << endl;
		return 1;
	}
	
	Course mieic(studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName);
	mainOption(mieic);
    
	return 0;
    
}
