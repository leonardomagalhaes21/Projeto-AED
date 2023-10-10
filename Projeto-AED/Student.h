
#ifndef PROJECT_STUDENT_H
#define PROJECT_STUDENT_H


#include <string>

class Student {
    public:
        Student(int StudentCode, std::string StudentName);
        int get_StudentCode() const;
        std::string get_StudentName();
    private:
        int StudentCode_;
        std::string StudentName_;
};


#endif //PROJECT_STUDENT_H
