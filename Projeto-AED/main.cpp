#include "Classes/Student.h"
#include "Classes/UC.h"
#include "Classes/Data.h"
#include "Classes/Schedule.h"
#include "Classes/Lesson.h"
#include <iostream>
#include "Classes/Menu.h"

using namespace std;

int main() {

    Data d = Data();
    d.readStudents_Classes();
    d.readClasses();


//teste 0 -> print ao horario de um aluno
    Student s = Student(202054812, "Manuel Mauro");

    s.getStudentSchedule(d.getListStudents_Classes_(),d.getListClasses_()).printSchedule();


//teste 1 -> print a horario de cadeira da turma
    UC uc= UC("L.EIC001","1LEIC06");
    uc.addClassLessons(d.getListClasses_());
    uc.printLessons();

//teste 2 -> print a horario de cadeira
    UC u = UC("L.EIC001");
    uc.getSchedule(d.getListClasses_()).printSchedule();

//teste 3 -> print a horario de turma
    d.printClassTableSchedule("1LEIC03");
    return 0;

//showMenu()
//
}