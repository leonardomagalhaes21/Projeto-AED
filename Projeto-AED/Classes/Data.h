#ifndef PROJECT_DATA_H
#define PROJECT_DATA_H
#include "UC.h"
#include "Student.h"
#include "Lesson.h"

class Student;
class UC;

class Data {
private:
    std::list<std::pair<UC,Lesson>> listClasses_;
    std::list<UC> listClasses_Per_Uc_;
    std::list<std::pair<Student, UC>> listStudents_Classes_;
    std::set<Student> students_;
    UC* findClass(std::string ucCode, std::string classCode) const;
public:
    Data();
    std::list<std::pair<UC,Lesson>> getListClasses_() const;
    std::list<UC> getListClasses_Per_Uc_();
    std::list<std::pair<Student, UC>> getListStudents_Classes_();
    void setListStudents_Classes_(std::list<std::pair<Student, UC>> l);
    void readClasses();
    void readClasses_Per_Uc();
    void readStudents_Classes();
    std::set<Student> getStudents();
    void printStudentsAscendingCode();
    void printStudentsDescendingCode();
    void printStudentsAscendingName();
    void printStudentsDescendingName();
    static void printStudentsByYear(int x,const std::list<std::pair<Student, UC>>& val);
    static void printStudentsByClass(const std::string& x,const std::list<std::pair<Student, UC>>& val);
    static int numberOfStudentsByYear(int x,const std::list<std::pair<Student, UC>>& val);
    static int numberOfStudentsInClass(const std::string& x,const std::list<std::pair<Student, UC>>& val);
    static void printStudentsWithNUcs(int x,const std::list<std::pair<Student, UC>>& val);
    static int numberStudentsWithNUcs(int n,const std::list<std::pair<Student, UC>>& val);
    static void printStudentsInUC(const std::string& x,const std::list<std::pair<Student, UC>>& val);
    static int numberOfStudentsInUC(const std::string& x,const std::list<std::pair<Student, UC>>& val);
    static void printUcsByClass(const std::string& Ccode,const std::list<UC>& val);
    static void printClassByUcs(const std::string& UCcode,const std::list<UC>& val);
    void printClassTableSchedule(const std::string& classCode) const;


    static void printClassSchedule(const std::string& classCode, const std::list<UC>& classes_per_uc, const std::list<std::pair<UC, Lesson>>& getListClasses) ;

};


#endif //PROJECT_DATA_H
