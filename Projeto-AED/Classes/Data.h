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
    std::list<UC> listClassesPerUC_;
    std::list<std::pair<Student, UC>> listStudentsClasses_;
    std::set<Student> students_;
    std::map<int, std::set<Student>> nUCsToStudentsMap_;
    std::map<std::string, std::set<std::string>> ucToClassMap_;
    std::map<std::string, std::set<std::string>> classToUCMap_;
    std::map<std::string, std::set<Student>> ucToStudentsMap_;
    std::map<std::string, std::set<Student>> classToStudentsMap_;
    std::map<int, std::set<Student>> yearToStudentsMap_;
    std::map<UC, std::set<Student>> ucClasstoStudentsMap_;

public:
    Data();
    std::list<std::pair<UC,Lesson>> getListClasses_() const;
    std::list<UC> getListClassesPerUC_();
    std::list<std::pair<Student, UC>> getListStudentsClasses_();
    void setListStudentsClasses_(std::list<std::pair<Student, UC>> l);
    void startNUCsToStudentsMap();
    std::map<int, std::set< Student>> getNUCsToStudentsMap();
    void startUCToClassMap();
    void startClassToUCMap();
    std::map<std::string, std::set<std::string>> getUCToClassMap();
    std::map<std::string, std::set<std::string>> getClassToUcMap();
    void startUCToStudentsMap();
    std::map<std::string, std::set<Student>> getUCToStudentsMap();
    void startClassToStudentsMap();
    std::map<std::string, std::set<Student>> getClassToStudentsMap();
    void startYearToStudentsMap();
    std::map<int, std::set<Student>> getYearToStudentsMap();
    void startUCClasstoStudentsMap();
    std::map<UC, std::set<Student>> getUCClasstoStudentsMap();
    void readClasses();
    void readClassesPerUC();
    void readStudentsClasses();
    std::set<Student> getStudents();
    void printStudentsAscendingCode();
    void printStudentsDescendingCode();
    void printStudentsAscendingName();
    void printStudentsDescendingName();
    static void printStudentsByYear(int x,const std::map<int, std::set<Student>>& m);
    static void printStudentsByClass(const std::string& x,const std::map<std::string, std::set<Student>>& m);
    static int numberOfStudentsByYear(int x,const std::map<int, std::set<Student>>& m);
    static int numberOfStudentsInClass(const std::string& x,const std::map<std::string, std::set<Student>>& m);
    static void printStudentsWithNUCs(int x,const std::map<int, std::set<Student>>& m);
    static int numberStudentsWithNUCs(int n,const std::map<int, std::set<Student>>& m);
    static void printStudentsInUC(const std::string& x,const std::map<std::string, std::set<Student>>& ucToStudentsMap);
    static int numberOfStudentsInUC(const std::string& x,const std::map<std::string, std::set<Student>>& m);
    static void printUCsByClass(const std::string& Ccode,std::map<std::string, std::set<std::string>>);
    static void printClassByUCs(const std::string& UCcode,std::map<std::string, std::set<std::string>>);
    void printClassTableSchedule(const std::string& classCode) const;
    static void printClassSchedule(const std::string& classCode, const std::list<UC>& classes_per_uc, const std::list<std::pair<UC, Lesson>>& getListClasses) ;
    static void printTop5UCs(const std::map<std::string, std::set<Student>>& m);
    static void printStudentsInUCClass(const std::string& ucCode,const std::string& classCode, std::map<UC, std::set<Student>> m );
    static int numberOfStudentsInUCClass(const std::string& ucCode,const std::string& classCode, std::map<UC, std::set<Student>> m );
};


#endif //PROJECT_DATA_H
