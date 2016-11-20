#pragma once

#include <iostream>
#include "Course.h"

/*! \file menus.h
 \brief Menus shown throughout program execution
 */

//! Asks for input files so information can be read. Throws inexistentFile exception if any of given files does not exist
/*!
\param studentsFile name of file where students will be read from
\param teachersFile name of file where teachers will be read from
\param mandatoryUnitsFile name of file where mandatory units will be read from
\param optionalUnitsFile name of file where mandatory units will be read from
*/
void start(std::string &studentsFile, std::string &teachersFile, std::string &mandatoryUnitsFile, std::string &optionalUnitsFile);


//! Shows main menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int mainMenu();

//! Processes option read from main menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void mainOption(Course &course);

//! Shows students' main menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int studentsMenu();

//! Processes option read from students' main menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void studentsOptions(Course &course);

//! Shows editing students' menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int editStudentMenu();

//! Processes option read from editing students' menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void editStudentOptions(Course & course);

//! Shows registering students' menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int registrateStudentMenu();

//! Processes option read from registering students' menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void registrateStudentOptions(Course & course);

//! Shows identification of specific student's menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int registrateSpecificStudentMenu();

//! Processes option read from identification of specific student's menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void registrateSpecificStudentOptions(Course & course);

//! Shows students listing's menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int listStudentsMenu();

//! Processes option read from students listing's menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void listStudentsOptions(Course & course);

//! Shows identification of specific student's menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int showStudentMenu();

//! Processes option read from identification of specific student's menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void showStudentOptions(Course & course);

//! Shows listing students registrations' menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int listRegistrationsMenu();

//! Processes option read from listing students registrations' menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void listRegistrationsOptions(Course & course);

//! Shows identification of specific student's menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int studentRegistrationsMenu();

//! Processes option read from identification of specific student's menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void studentRegistrationsOptions(Course & course);

//! Shows teacher's main menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int teachersMenu();

//! Processes option read from teacher's main menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void teachersOptions(Course & course);

//! Shows editing teacher's menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int editTeacherMenu();

//! Processes option read from editing teacher's menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void editTeacherOptions(Course & course);

//! Shows listing teacher's menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int listTeachersMenu();

//! Processes option read from listing teacher's menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void listTeachersOptions(Course & course);

//! Shows identification of specific teacher's menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int showTeacherMenu();

//! Processes option read from identification of specific teacher's menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void showTeacherOptions(Course & course);

//! Shows identification of specific teacher by one of his pupils' menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int showTeacherPupilMenu();

//! Processes option read from identification of specific teacher by one of his pupils' menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void showTeacherPupilOptions(Course & course);

//! Shows units' main menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int unitsMenu();

//! Processes option read from units' main menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void unitsOptions(Course & course);

//! Shows editing units' menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int editUnitsMenu();

//! Processes option read from editing units' menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void editUnitsOptions(Course & course);

//! Shows listing units' menu options and reads user's option
/*!
\return user's option from the menu
*/
unsigned short int listUnitsMenu();

//! Processes option read from listing units' menu on object of type Course
/*!
\param course course where the option will be processed at
*/
void listUnitsOptions(Course & course);
