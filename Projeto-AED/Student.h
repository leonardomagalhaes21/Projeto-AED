
#ifndef PROJECT_STUDENT_H
#define PROJECT_STUDENT_H


#include <string>

class Student {
    public:
        Student(int studentCode, std::string studentName);
        int get_StudentCode() const;
        std::string get_StudentName();
    private:
        int studentCode_;
        std::string studentName_;
};


#endif //PROJECT_STUDENT_H
