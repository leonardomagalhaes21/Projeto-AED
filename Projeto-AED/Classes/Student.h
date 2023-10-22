
#ifndef PROJECT_STUDENT_H
#define PROJECT_STUDENT_H



#include <string>
#include "Schedule.h"
#include "UC.h"
#include "Data.h"
#include "Lesson.h"
#include <list>

class Student {
    public:
        Student();
        Student(int studentCode, std::string studentName);
        Student(int studentCode, std::string studentName, std::list<UC> ucs);
        int get_StudentCode() const;
        std::string get_StudentName() const;
        std::list<UC> get_Ucs() const;
        void set_StudentName(std::string studentName);
        void set_StudentCode(int studentCode);
        void set_Ucs(std::list<UC> ucs);
        bool operator< (const Student & student) const;
        bool has_Class(std::string classCode) const;
        bool has_Uc(std::string ucCode) const;
        Schedule getStudentSchedule() const;
        void printStudentTableSchedule() const;

    private:
        int studentCode_;
        std::string studentName_;
        std::list<UC> ucs_;
};


#endif //PROJECT_STUDENT_H
