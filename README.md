# MIEIC
## CLI C++ based tool that emulates a course's registration system. Made in colaboration with @cyrilico and @diogotorres97

### Classes
##### PessoaFEUP (base class):
- name
- code "(up?)2015..."
- email (more than one?)
- birthDate
- Purely vitual method to display info (making this class abstract)

##### Derived from PessoaFEUP (excluding classes derived PessoaFEUP)
- ##### Student:
    - year (important because of failed/repeated units)
    - "estatuto"
    - ects (number of credits)
    - units vector
    - Registration approval methods
    
- ##### Teacher:
    - Units vector (can teach more than one class - use unit class or simply the code? (ej PROG))
    - "Pupils" vector (students that teacher is a tutor to)

##### Date 
- day
- month
- year
- getMethods
- setsMethods?
- Exceptions
    - invalidDay
    - invalidMonth
    - invalidYear (?)

##### Course (rename to MIEIC?)
- Students vector (organized by year?)
- Teachers vector (organized by year? maybe not needed due to smaller size)
- Courses vector (organized by year)
- Students methods:
    - registrateStudent, removeStudent
    - showStudents (by year, by unit, by age (?), alphabetically (?))
    - assignTutor(student) (tutor choice method needs to be defined)
    - listRegistrations (by unit, by student (name?))
- (Methods related to files content)

##### Unit
- name (or simply code?)
- code (see point above)
- year
- ects
- teachers vector (need to differentiate between main an auxiliar teachers)
- students vector (organized by year?)
- vacancies (? maybe only defined in derived classes - create a virtual function that returns true on obligatory units and a number on optional units)

##### Derived from Unit:
##### - ObligatoryUnit
   - vacancies (?)
   
##### - OptionalUnit
   - scientificArea
   - course (?)
   - institution (?)

Other ideas:
- When program is started, ask if user wants to read info from files or start with an empty database
- File with units' names
- Need to decide format to write info to files
- Exception on a single header file?
- How to organize a student's units?
- When registering a student, ask for date or use PC's time?
