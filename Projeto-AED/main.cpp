#include "Classes/Student.h"
#include "Classes/UC.h"
#include "Classes/Data.h"
#include "Classes/Schedule.h"
#include "Classes/Lesson.h"
#include <iostream>

using namespace std;

int main() {

    Student s = Student(202054812, "Manuel Mauro");

    s.getStudentSchedule().printSchedule();


    Lesson l = Lesson(1,1.5,12.5,"T");
    Lesson l2 =Lesson(2,2,14.5,"TP");
    Lesson l3=Lesson(3,2.5,10,"T");
    Lesson l4=Lesson(4,2.5,16,"TP");
    Lesson l5=Lesson(5,1,9.5,"T");
    list<Lesson> ll ={l,l2,l3,l4,l5};
    UC uc= UC("L.EIC001","1LEIC01",ll);
    uc.printLessons();
    Data data;
    data.printClassTableSchedule("1LEIC02");
    return 0;
}