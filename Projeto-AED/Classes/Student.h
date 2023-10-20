
#ifndef PROJECT_STUDENT_H
#define PROJECT_STUDENT_H



#include <string>
#include "Schedule.h"
#include "UC.h"
#include "Data.h"
#include "Lesson.h"

class Student {
    public:
        Student();
        Student(int studentCode, std::string studentName);
        int get_StudentCode() const;
        std::string get_StudentName();
        void set_StudentName(std::string studentName);
        void set_StudentCode(int studentCode);
        //bool operator< (const Student & student) const;
        Schedule getStudentSchedule();

    private:
        int studentCode_;
        std::string studentName_;
};


#endif //PROJECT_STUDENT_H
