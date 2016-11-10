#pragma once
#include "Course.h"

bool inicialInformation(std::string &studentsFile, std::string &teachersFile, std::string &mandatoryUnitsFile, std::string &optionalUnitsFile); //!< Asks user for filenames. Returns true if all are valid


/* Main Menu */
unsigned short int mainMenu();
void mainOption(Course &course);

/* Students Menus */
unsigned short int studentsMenu();
void studentsOptions(Course &course);

    //Registrate Students Menu
    unsigned short int registrateStudentMenu();
    void registrateStudentOptions(Course & course);

    //List Students Menu
    unsigned short int listStudentsMenu();
    void listStudentsOptions(Course & course);

        //Show Student Menu
        unsigned short int showStudentMenu();
        void showStudentOptions(Course & course);

        //List Registrations Menu
        unsigned short int listRegistrationsMenu();
        void listRegistrationsOptions(Course & course);

            //Registrations for a single student Menu
            unsigned short int studentRegistrationsMenu();
            void studentRegistrationsOptions(Course & course);

/* Teachers Menu */
unsigned short int teachersMenu();
void teachersOptions(Course & course);

    //List Teachers Menu
    unsigned short int listTeachersMenu();
    void listTeachersOptions(Course & course);

        //Show Teacher Menu
        unsigned short int showTeacherMenu();
        void showTeacherOptions(Course & course);

/* Units Menu */
unsigned short int unitsMenu();
void unitsOptions(Course & course);

    //List Units Menu
    unsigned short int listUnitsMenu();
    void listUnitsOptions(Course & course);
