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
    d.readClasses_Per_Uc();
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

//teste 3 -> print a horario de turma (table)
    d.printClassTableSchedule("1LEIC03");


    Menu m= Menu();
    m.showMenu();
    cout << "\n";

//teste 5 print a horario de turma
    d.printClassSchedule("1LEIC03",d.getListClasses_Per_Uc_(),d.getListClasses_());

//teste 4 -> métodos adicionais
    //d.printStudentsByYear(2019,d.getListStudents_Classes_());
    //cout << d.numberOfStudentsByYear(2019,d.getListStudents_Classes_());
    //d.printStudentsByClass("3LEIC08",d.getListStudents_Classes_());
    //cout << d.numberOfStudentsInClass("3LEIC08",d.getListStudents_Classes_());
    //d.printStudentsWithNUcs(7,d.getListStudents_Classes_());
    //cout << d.numberStudentsWithNUcs(7,d.getListStudents_Classes_());
    return 0;
}