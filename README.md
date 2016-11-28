# MIEIC Registrations 
## CLI C++ based tool that emulates a course's registration system. Made in colaboration with @cyrilico and @diogotorres97
### Project for AEDA's course @FEUP

### Main Classes
##### Person (base class):
- name
- code
- email 
- Purely vitual method to display info (making this class abstract)

##### Derived from Person
- ##### Student:
    - code: "20XXXXXXX"
    - curricularYear: ranges from 1-5
    - status: examples - "Ordinary", "Athlete"
    - ectsTaking
    - matrix unitsDone
    - matrix unitsToDo
    - vector unitsTaking
    - registrationDate
    
- ##### Teacher:
    - code
    - vector unitsTaught
    - vector pupils
    - static lessStudents - unsigned int that represents the least amount of pupils a teacher has


##### Unit
- name 
- abbreviation
- scientificArea
- ECTS
- curricularYear

##### Derived from Unit:
##### - MandatoryUnit
   - unlimited vacancies
   
##### - OptionalUnit
   - limited vacancies

For more information see the documentation <a href="antonioalmeida.github.io/aedamieic">here</a>.
