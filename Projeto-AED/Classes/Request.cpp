#include "Request.h"
using namespace std;

/**
 * @brief Default constructor for the RequestLog structure.
 *
 * Time Complexity: O(1), constant time for object initialization.
 */
RequestLog::RequestLog() {}

/**
 * @brief Records and logs a request with a new UC.
 *
 * This function records a request action and logs it with a new UC.
 *
 * @param action The action to be logged.
 * @param student The student involved in the request.
 * @param newUc The new UC associated with the request.
 *
 * Time Complexity: O(1)
 */
void RequestLog::requestAndLog(const std::string& action,const Student& student, UC newUc) {
    Operation operation;
    operation.action_ = action;
    operation.newUc_ = newUc;
    operations_.push(operation);
}

/**
 * @brief Records and logs a request with a new and old UC.
 *
 * This function records a request action and logs it with both a new and old UC.
 *
 * @param action The action to be logged.
 * @param student The student involved in the request.
 * @param newUc The new UC associated with the request.
 * @param oldUc The old UC associated with the request.
 *
 * Time Complexity: O(1)
 */
void RequestLog::requestAndLog(const std::string& action, Student student,UC newUc,UC oldUc) {
    Operation operation;
    operation.action_ = action;
    operation.student_=student;
    operation.newUc_ = newUc;
    operation.oldUc_= oldUc;
    operations_.push(operation);
}

/**
 * @brief Records and logs a request with a student and class/UC code.
 *
 * This function records a request action and logs it with a student and class/UC code.
 *
 * @param action The action to be logged.
 * @param student The student involved in the request.
 * @param class_uc_Code The class or UC code associated with the request.
 *
 * Time Complexity: O(1)
 */
void RequestLog::requestAndLog(const std::string& action,Student student, std::string class_uc_Code){
    Operation operation;
    operation.action_ = action;
    operation.student_=student;
    operation.class_Uc_Code_=class_uc_Code;
    operations_.push(operation);
}


void RequestLog::printLog(const string& file) {
    ofstream out(file);
    string f = "../log.txt";

    if (!out.is_open() && !out.good()) {
        std::cerr << "Failed to open file: " << f << std::endl;
    }

    out << "Request Log:" << endl;
    while (!operations_.empty()) {
        const Operation& operation = operations_.front();
        out << operation.action_ << " ";
        out << operation.newUc_.getUCCode() << " ";
        out << operation.newUc_.getClassCode() << " ";
        out << operation.oldUc_.getUCCode() << " ";
        out << operation.oldUc_.getClassCode() << " ";
        out << operation.class_Uc_Code_ << " ";
        out << operation.student_.getStudentCode() << endl;
        operations_.pop();
    }
    out.close();
}



void RequestLog::undo() {
    if (!operations_.empty()) {
        operations_.pop();
    }
}

/**
 * @brief Default constructor for the Request class.
 *
 * This constructor initializes an instance of the Request class.
 *
 * Time Complexity: O(1)
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
 * Time Complexity: O(n²) where n is the number of student-UC pairs in 'val'.
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

/**
 * @brief Switches a student's UC from an old UC to a new UC.
 *
 * This function switches a student's UC from an old UC to a new UC if certain conditions are met.
 *
 * @param s The student for whom the UC is being switched.
 * @param oldUC The old UC to be removed.
 * @param newUC The new UC to be added.
 * @param val The list of student-UC pairs.
 * @param val2 The list of UC-lesson pairs.
 * @param m The map of UCs to students.
 * @return True if the UC switch is successful, false otherwise.
 *
 * Time Complexity: O(n) where n is the number of student-UC pairs in 'val'.
 */
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

/**
 * @brief Removes a UC from a student's schedule.
 *
 * This function removes a UC from a student's schedule.
 *
 * @param s The student from whom the UC is being removed.
 * @param uc The UC to be removed.
 * @param val The list of student-UC pairs.
 * @return True if the UC is removed successfully, false otherwise.
 *
 * Time Complexity: O(n) where n is the number of student-UC pairs in 'val'.
 */
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

/**
 * @brief Switches a student's class within a UC.
 *
 * This function switches a student's class within a UC if certain conditions are met.
 *
 * @param s The student for whom the class is being switched.
 * @param oldUC The old UC containing the class to be removed.
 * @param newUC The new UC containing the class to be added.
 * @param val The list of student-UC pairs.
 * @param val2 The list of UC-lesson pairs.
 * @param m The map of UCs to students.
 * @return True if the class switch is successful, false otherwise.
 *
 * Time Complexity: O(n) where n is the number of student-UC pairs in 'val'.
 */
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

/**
 * @brief Removes a student from a specific class.
 *
 * This function removes a student from a specific class within a UC.
 *
 * @param s The student to be removed from the class.
 * @param cc The class code of the class to be removed from.
 * @param val The list of student-UC pairs.
 * @return True if the student is removed from the class successfully, false otherwise.
 *
 * Time Complexity: O(n) where n is the number of student-UC pairs in 'val'.
 */
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

