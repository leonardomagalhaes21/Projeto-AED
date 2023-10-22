#include "Classes/Student.h"
#include "Classes/UC.h"
#include "Classes/Data.h"
#include "Classes/Schedule.h"
#include "Classes/Lesson.h"
#include <iostream>

using namespace std;

int main() {

//teste 0 -> print ao horario de um aluno
    Student s = Student(202054812, "Manuel Mauro");

    s.getStudentSchedule().printSchedule();


//teste 1 -> print a horario de cadeira da turma
    UC uc= UC("L.EIC001","1LEIC06");
    uc.addClassLessons();
    uc.printLessons();

//teste 2 -> print a horario de cadeira
    UC u = UC("L.EIC001");
    uc.getSchedule().printSchedule();

//teste 3 -> print a horario de turma
    Data data;
    data.readClasses_Per_Uc();
    data.printClassTableSchedule("1LEIC03");
    return 0;
}