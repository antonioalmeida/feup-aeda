#include <iostream>

int main(int argc, char **argv) {
    
    string course, studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName;
    
    bool validState = initialInformation(course, studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName);
    if(!validState)
        return -1;
    
    //Course supermarket(course, studentsFileName, teachersFileName, mandatoryUnitsFileName, optionalUnitsFileName);
    
	return 0;
    
}
