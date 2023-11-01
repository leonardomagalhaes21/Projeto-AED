#include "Request.h"
using namespace std;


void RequestLog::requestAndLog(const std::string& action,const Student& student, UC newUc) {
    Operation operation;
    operation.action_ = action;
    operation.newUc_ = newUc;
    operations.push_back(operation);
}

void RequestLog::requestAndLog(const std::string& action, Student student,UC newUc,UC oldUc) {
    Operation operation;
    operation.action_ = action;
    operation.student_=student;
    operation.newUc_ = newUc;
    operation.oldUc_= oldUc;
    operations.push_back(operation);
}

void RequestLog::requestAndLog(const std::string& action,Student student, std::string class_uc_Code){
    Operation operation;
    operation.action_ = action;
    operation.student_=student;
    operation.class_Uc_Code_=class_uc_Code;
}

/*
void RequestLog::printLog() {
    std::cout << "Request Log:" << std::endl;
    for (const Operation& operation : operations) {
        std::cout << operation.action << " " << operation.value << std::endl;
    }
}
*/
Request::Request(){}

/**
 * @brief Adds an UC to a student's schedule.
 *
 * This function adds a UC to a student's schedule if certain conditions are met. The conditions include
 * checking the student's UC count, ensuring there are no schedule conflicts, and checking the UC's capacity.
 *
 * @param s The student for whom the UC is being added.
 * @param ucc The UC code to add.
 * @param cc The class code of the UC.
 * @param val The list of student-UC pairs.
 * @param val2 The list of UC-lesson pairs.
 * @param m The map of UCs to students.
 * @return True if the UC is added successfully, false otherwise.
 *
 * @b Complexity: O(n) where n is the number of student-UC pairs in 'val' (worst case: O(N))
 */
bool Request::addUC(const Student& s, const string& ucc, const string& cc, list<pair<Student, UC>>& val, const list<pair<UC, Lesson>>& val2, const map<UC, set<Student>>& m) {
    int n = 0;

    for(const pair<Student,UC>& c: val){
        if (c.first.getStudentCode() == s.getStudentCode()){
            n++;
        }
    }
    bool cond1, cond2, cond3;
    cond1 = n<7;
    cond2 = true;
    cond3 = true;

    UC a = UC(ucc, cc);

    Schedule schedule = s.getStudentSchedule(val,val2);

    for(const auto& c : val2){
        if(c.first.getClassCode() == cc && c.first.getUCCode() == ucc) {
            a.addLesson(c.second);
        }
    }
    for(const auto& c : schedule.getSchedule()){
        for (const auto& d : a.getLessons()){
            if (c.second.coincideT(d)){
                cond2 = false;
                break;
            }
        }
        if (!cond2) break;
    }

    if (m.at(a).size() +1 > UC::capacity_){
        cond3 = false;
    }

    if (cond1 && cond2 && cond3){
        pair<Student, UC> p = {s,a};
        val.push_back(p);
        return true;
    }
    return false;


}

bool Request::switchUC(const Student& s, const UC& oldUC, const UC& newUC, list<pair<Student, UC>>& val,const list<pair<UC, Lesson>>& val2, const map<UC, set<Student>>& m) {
    if (!removeUC(s, oldUC, val)) {
        return false;
    }


    if (addUC(s, newUC.getUCCode(), newUC.getClassCode(), val, val2, m)) {
        return true;
    }
    else {
        removeUC(s, newUC, val);
        addUC(s, oldUC.getUCCode(), oldUC.getClassCode(), val, val2, m);
        return false;
    }

}

bool Request::removeUC(const Student& s, const UC& uc, list<pair<Student, UC>>& val) {
    bool flag = false;
    for (auto it = val.begin(); it != val.end(); ) {
        if (it->first.getStudentCode()==s.getStudentCode() and it->second.getUCCode()==uc.getUCCode()) {
            it = val.erase(it);
            flag = true;
        }
        else {
            ++it;
        }
    }
    if (flag){
        return true;
    }
    return false;

}

bool Request::switchClass(const Student& s, const UC& oldUC, const UC& newUC, list<pair<Student, UC>>& val,const list<pair<UC, Lesson>>& val2, const map<UC, set<Student>>& m) {
    if (!removeUC(s, oldUC, val)){
        return false;
    };

    bool cond = ((int) (m.at(newUC).size() - m.at(oldUC).size()) < 4);

    if (cond) {
        if (addUC(s, newUC.getUCCode(), newUC.getClassCode(), val, val2, m)) {
            return true;
        } else {
            removeUC(s, newUC, val);
            addUC(s, oldUC.getUCCode(), oldUC.getClassCode(), val, val2, m);
            return false;
        }
    }
    else return false;
}

bool Request::removeClass(const Student& s, const string& cc, list<pair<Student, UC>>& val) {
    bool flag = false;
    for (auto it = val.begin(); it != val.end(); ) {
        if (it->first.getStudentCode()==s.getStudentCode() and it->second.getClassCode()==cc) {
            it = val.erase(it);
            flag = true;
        }
        else {
            ++it;
        }
    }
    if (flag){
        return true;
    }
    return false;

}

