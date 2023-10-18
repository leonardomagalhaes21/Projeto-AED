#ifndef PROJECT_DATA_H
#define PROJECT_DATA_H
#include "UC.h"
#include "Student.h"
#include "Lesson.h"

class Data {
private:
    std::pair<UC,Lesson> ListClasses_;
    std::list<UC> ListClasses_Per_Uc_;
    std::list<std::pair<Student, UC>> ListStudents_Classes_;

public:

    void ReadClasses();
    void ReadClasses_Per_Uc();
    void ReadStudents_Classes();

};


#endif //PROJECT_DATA_H
