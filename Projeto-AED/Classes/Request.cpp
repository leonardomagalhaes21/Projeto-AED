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
 * @detail This function records a request action and logs it with a new UC.
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
    operation.student_ = student;
    operation.newUc_ = newUc;
    operations_.push(operation);
}

/**
 * @brief Records and logs a request with a new and old UC.
 *
 * @detail This function records a request action and logs it with both a new and old UC.
 *
 * @param action The action to be logged.
 * @param student The student involved in the request.
 * @param newUc The new UC associated with the request.
 * @param oldUc The old UC associated with the request.
 *
 * Time Complexity: O(1)
 */
void RequestLog::requestAndLog(const std::string& action, const Student& student,UC newUc,UC oldUc) {
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
 * @detail This function records a request action and logs it with a student and class/UC code.
 *
 * @param action The action to be logged.
 * @param student The student involved in the request.
 * @param class_uc_Code The class or UC code associated with the request.
 *
 * Time Complexity: O(1)
 */
void RequestLog::requestAndLog(const std::string& action,const Student& student, std::string class_uc_Code){
    Operation operation;
    operation.action_ = action;
    operation.student_=student;
    operation.class_Uc_Code_=class_uc_Code;
    operations_.push(operation);
}

/**
 * @brief Save the request log to a file.
 *
 * @detail This function is responsible for saving the request log to a text file named "log.txt" located in the "../schedule" directory.
 * The request log includes details of each operation performed, such as the action type, new and old course and class codes,
 * the class_Uc_Code, and the student's code. The function begins by opening the file for writing and checks if the file opening was successful.
 * If the file cannot be opened, it reports an error to the standard error stream and returns without saving the log. For each operation in the log,
 * the function writes the relevant information to the file, including the action type and associated data.
 * After recording the operation in the log file, the `saveToData()` method is called on the operation to update the data as needed.
 * Finally, the function prints a success message to the standard output.
 *
 * Time Complexity: O(n), where n is the number of elements in the queue 'operations_'
 */
void RequestLog::save() {
    string f = "../schedule/log.txt";
    ofstream out(f);

    if (!out.is_open() && !out.good()) {
        std::cerr << "Failed to open file: " << f << std::endl;
        return;
    }

    out << "Request Log:" << endl;
    while (!operations_.empty()) {
        Operation operation = operations_.front();
        out << operation.action_ << " " ;
        out << operation.newUc_.getUCCode() << " ";
        out << operation.newUc_.getClassCode() << " ";
        out << operation.oldUc_.getUCCode() << " ";
        out << operation.oldUc_.getClassCode() << " ";
        out << operation.class_Uc_Code_ << " ";
        out << operation.student_.getStudentCode() << endl;
        operation.saveToData();
        operations_.pop();
    }
    cout << "Save successful!";
    out.close();
}

/**
 * @brief Save operation details to a data file.
 *
 * @detail This function saves operation details to a data file based on the type of action.
 * The action type is used to determine how the data should be saved in the file.
 * The supported actions include "AddUc," "RemoveUc," "RemoveClass," "SwitchUc," and "SwitchClass."
 *
 * Time Complexity: The time complexity of this function is O(N), where N is the number of lines in the file.
 */
void RequestLog::Operation::saveToData() {
    map<string, int> m = {
            {"AddUc", 1},
            {"RemoveUc", 2},
            {"RemoveClass", 3},
            {"SwitchUc", 4},
            {"SwitchClass", 5}
    };
    int a = m[action_];
    switch(a) {
        case 1: {
            string f = "../schedule/students_classes.csv";
            ifstream iff(f);
            if (!iff.is_open() || !iff.good()) {
                cerr << "Failed to open file: " << f << endl;
            }

            string StName, StCode, UcCode, ClassCode, line;
            stringstream ss;
            bool flag = false;
            while (getline(iff, line)) {
                istringstream inn(line);
                getline(inn, StCode, ',');
                getline(inn, StName, ',');
                getline(inn, UcCode, ',');
                inn >> ClassCode;
                string c = to_string(student_.getStudentCode());
                if (StCode == c && !(flag)) {
                    string s = c + "," + StName + "," + newUc_.getUCCode() + "," + newUc_.getClassCode();
                    ss << s << endl;
                    ss << line << endl;
                    flag = true;
                }
                else {
                    ss << line << endl;
                }
            }
            if (!flag){
                string c = to_string(student_.getStudentCode());
                string s = c + "," + student_.getStudentName() + "," + newUc_.getUCCode() + "," + newUc_.getClassCode();
                ss << s;
            }

            iff.close();
            ofstream out(f);

            out << ss.str();
            out.close();
            break;
        }
        case 2: {
            string f = "../schedule/students_classes.csv";
            ifstream iff(f);
            if (!iff.is_open() || !iff.good()) {
                cerr << "Failed to open file: " << f << endl;
            }

            string StName, StCode, UcCode, ClassCode, line;
            stringstream ss;

            while (getline(iff, line)) {
                istringstream inn(line);
                getline(inn, StCode, ',');
                getline(inn, StName, ',');
                getline(inn, UcCode, ',');
                inn >> ClassCode;
                string c = to_string(student_.getStudentCode());
                if (StCode != c || class_Uc_Code_ != UcCode) {
                    ss << line << endl;
                }
            }

            iff.close();
            ofstream out(f);

            out << ss.str();
            out.close();
            break;
        }
        case 3: {
            string f = "../schedule/students_classes.csv";
            ifstream iff(f);
            if (!iff.is_open() || !iff.good()) {
                cerr << "Failed to open file: " << f << endl;
            }

            string StName, StCode, UcCode, ClassCode, line;
            stringstream ss;

            while (getline(iff, line)) {
                istringstream inn(line);
                getline(inn, StCode, ',');
                getline(inn, StName, ',');
                getline(inn, UcCode, ',');
                inn >> ClassCode;
                string c = to_string(student_.getStudentCode());
                if (StCode != c || class_Uc_Code_ != ClassCode) {
                    ss << line << endl;
                }
            }

            iff.close();
            ofstream out(f);

            out << ss.str();
            out.close();
            break;
        }
        case 4: {
            string f = "../schedule/students_classes.csv";
            ifstream iff(f);
            if (!iff.is_open() || !iff.good()) {
                cerr << "Failed to open file: " << f << endl;
            }

            string StName, StCode, UcCode, ClassCode, line;
            stringstream ss;

            while (getline(iff, line)) {
                istringstream inn(line);
                getline(inn, StCode, ',');
                getline(inn, StName, ',');
                getline(inn, UcCode, ',');
                inn >> ClassCode;
                string c = to_string(student_.getStudentCode());
                if (StCode == c && oldUc_.getUCCode() == UcCode && oldUc_.getClassCode() == ClassCode) {
                    string s = c + "," + StName + "," + newUc_.getUCCode() + "," + newUc_.getClassCode();
                    ss << s << endl;
                }
                else {
                    ss << line << endl;
                }
            }

            iff.close();
            ofstream out(f);

            out << ss.str();
            out.close();
            break;
        }
        case 5: {
            string f = "../schedule/students_classes.csv";
            ifstream iff(f);
            if (!iff.is_open() || !iff.good()) {
                cerr << "Failed to open file: " << f << endl;
            }

            string StName, StCode, UcCode, ClassCode, line;
            stringstream ss;

            while (getline(iff, line)) {
                istringstream inn(line);
                getline(inn, StCode, ',');
                getline(inn, StName, ',');
                getline(inn, UcCode, ',');
                inn >> ClassCode;
                string c = to_string(student_.getStudentCode());
                if (StCode == c && oldUc_.getUCCode() == UcCode && oldUc_.getClassCode() == ClassCode) {
                    string s = c + "," + StName + "," + newUc_.getUCCode() + "," + newUc_.getClassCode();
                    ss << s << endl;
                }
                else {
                    ss << line << endl;
                }
            }

            iff.close();
            ofstream out(f);

            out << ss.str();
            out.close();
            break;
        }
        default:
            break;
    };
}

/**
 * @brief Undoes the most recent operation in the operations list.
 *
 * @detail This function undoes the most recent operation stored in the operations list.
 * The list of operations is implemented as a queue, where the oldest operation
 * is at the front (position 0), and the most recent operation is at the back.
 * The function removes the most recent operation, shifting all remaining operations
 * towards the front of the queue.
 *
 * @note This function will only have an effect if the operations list is not empty.
 *
 * Time Complexity: The average time complexity is O(n), where n is the number of operations in the list.
 */
void RequestLog::undo() {
    if (!operations_.empty()){
        for(int i=0;i<operations_.size()-1;i++){
            Operation aux=operations_.front();
            operations_.pop();
            operations_.push(aux);
        }
        operations_.pop();
    }
}

/**
 * @brief Default constructor for the Request class.
 *
 * @detail This constructor initializes an instance of the Request class.
 *
 * Time Complexity: O(1)
 */
Request::Request(){}

/**
 * @brief Adds an UC to a student's schedule.
 *
 * @detail This function adds a UC to a student's schedule if certain conditions are met. The conditions include
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
 * @detail This function switches a student's UC from an old UC to a new UC if certain conditions are met.
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
 * @detail This function removes a UC from a student's schedule.
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
 * @detail This function switches a student's class within a UC if certain conditions are met.
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
 * @detail This function removes a student from a specific class within a UC.
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

