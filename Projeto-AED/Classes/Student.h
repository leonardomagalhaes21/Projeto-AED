
#ifndef PROJECT_STUDENT_H
#define PROJECT_STUDENT_H

#include <string>
#include "Schedule.h"
#include "UC.h"
#include "Data.h"
#include "Lesson.h"
#include <list>

class UC;
class Schedule;


class Student {

public:
    Student();
    Student(int studentCode, std::string studentName);
    Student(int studentCode);
    Student(int studentCode, std::string studentName, std::list<UC> ucs);
    int getStudentCode() const;
    std::string getStudentName() const;
    std::list<UC> getUCs() const;
    void setStudentName(std::string studentName);
    void setStudentCode(int studentCode);
    void setUCs(std::list<UC> ucs);
    bool operator< (const Student & other) const;
    void addUC(const UC& uc);
    bool hasClass(std::string classCode) const;
    bool hasUC(const std::string& ucCode) const;
    Schedule getStudentSchedule(const std::list<std::pair<Student, UC>>& l1, const std::list<std::pair<UC, Lesson>>& l2) const ;
    void printStudentTableSchedule(int student_code,const std::list<std::pair<Student, UC>>& l1,const std::list<std::pair<UC, Lesson>>& l2) const;
    static std::string findName(const std::list<std::pair<Student, UC>>& listStudents_Classes, int num) ;

private:
    int studentCode_;
    std::string studentName_;
    std::list<UC> ucs_;
};


#endif //PROJECT_STUDENT_H
