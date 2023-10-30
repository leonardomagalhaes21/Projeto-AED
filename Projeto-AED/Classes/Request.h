#ifndef PROJECT_REQUEST_H
#define PROJECT_REQUEST_H


#include "Student.h"
struct RequestLog {
    struct Operation {
        std::string action_; // "add" ou "remove"
        UC newUc_;
        UC oldUc_;
        std::string class_Uc_Code_;
        Student student_;
    };

    std::vector<Operation> operations; // Para armazenar informações sobre as operações
    std::list<int> data; // Sua lista de dados

    void requestAndLog(const std::string& action,Student student, UC newUc);
    void requestAndLog(const std::string& action, Student student,UC newUc, UC oldUc);
    void requestAndLog(const std::string& action,Student student, std::string class_uc_Code);

    void printLog();
};

class Request {
    public:
    Request();
    static bool addUC(const Student& s, const std::string& ucc, const std::string& cc, std::list<std::pair<Student, UC>>& val, const std::list<std::pair<UC, Lesson>>& val2, const std::map<UC, std::set<Student>>& m);
    void switchUC(const Student& s, const UC& oldUC, const UC& newUC, std::list<std::pair<Student, UC>>& val,const std::list<std::pair<UC, Lesson>>& val2, const std::map<UC, std::set<Student>>& m);
    void removeUC(const Student& s, const UC& uc, std::list<std::pair<Student, UC>>& val);
    bool addClass(const Student& s, const UC& uc, std::list<std::pair<Student, UC>>& val, const std::list<std::pair<UC, Lesson>>& val2);
    void switchClass(const Student& s, const UC& oldUC, const UC& newUC, std::list<std::pair<Student, UC>>& val,const std::list<std::pair<UC, Lesson>>& val2);
    void removeClass(const Student& s, const UC& uc, std::list<std::pair<Student, UC>>& val);
private:
    RequestLog log;
};


#endif //PROJECT_REQUEST_H
