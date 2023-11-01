#include "Student.h"
#include <string>
#include <set>

using namespace std;

/**
 * @brief Default constructor for the Student class.
 *
 * This constructor initializes a Student object with default values. It does not perform any significant operations.
 *
 * Time Complexity: O(1), constant time for object initialization.
 */
Student::Student(){

}

/**
 * @brief Constructor for the Student class with a specified student code, student name, and list of UCs.
 *
 * This constructor creates a Student object with the given student code, student name, and list of UCs. It initializes the attributes accordingly.
 *
 * Time Complexity: O(1), constant time for object initialization and attribute assignment.
 */
Student::Student(int studentCode, string studentName, list<UC> ucs){
    studentCode_ = studentCode;
    studentName_ = studentName;
    ucs_ = ucs;
}

/**
 * @brief Constructor for the Student class with a specified student code and student name.
 *
 * This constructor creates a Student object with the given student code and student name. It initializes the attributes accordingly.
 *
 * Time Complexity: O(1), constant time for object initialization and attribute assignment.
 */
Student::Student(int studentCode, string studentName){
    studentCode_ = studentCode;
    studentName_ = studentName;
}

/**
 * @brief Constructor for the Student class with a specified student code.
 *
 * This constructor creates a Student object with the given student code. It initializes the attributes accordingly.
 *
 * Time Complexity: O(1), constant time for object initialization and attribute assignment.
 */
Student::Student(int studentCode){
    studentCode_ = studentCode;
}

/**
 * @brief Get the student's unique code.
 *
 * This function returns the student's unique code.
 *
 * Time Complexity: O(1), constant time to return the attribute.
 */
int Student::getStudentCode() const {
    return studentCode_;
}

/**
 * @brief Get the student's name.
 *
 * This function returns the student's name.
 *
 * Time Complexity: O(1), constant time to return the attribute.
 */
string Student::getStudentName() const {
    return studentName_;
}

/**
 * @brief Find the name of a student by their student code in a list of students and UCs.
 *
 * This function searches for the name of a student with the specified student code in the given list of student-UC pairs.
 *
 * Time Complexity: O(n), linear time complexity where 'n' is the number of elements in the 'listStudents_Classes'.
 */
string Student::findName(const list<pair<Student, UC>>& listStudents_Classes , int num) {
    for (const auto& c : listStudents_Classes) {
        if (c.first.studentCode_ == num) {
            return c.first.studentName_;
        }
    }
    return "";
}

/**
 * @brief Get the list of UCs associated with the student.
 *
 * This function returns the list of UCs associated with the student.
 *
 * Time Complexity: O(1), constant time to return the attribute.
 */
list<UC> Student::getUCs() const {
    return ucs_;
}

/**
 * @brief Set the student's unique code.
 *
 * This function sets the student's unique code to the specified value.
 *
 * Time Complexity: O(1), constant time to assign the attribute.
 */
void Student::setStudentCode(int StudentCode) {
    studentCode_ = StudentCode;
}

/**
 * @brief Set the student's name.
 *
 * This function sets the student's name to the specified value.
 *
 * Time Complexity: O(1), constant time to assign the attribute.
 */
void Student::setStudentName(string StudentName) {
    studentName_ = StudentName;
}

/**
 * @brief Set the list of UCs associated with the student.
 *
 * This function sets the list of UCs associated with the student.
 *
 * Time Complexity: O(1), constant time to assign the attribute.
 */
void Student::setUCs(list<UC> ucs) {
    ucs_ = ucs;
}

/**
 * @brief Compare two students for ordering based on their student code and name.
 *
 * This function compares two Student objects based on their student code and name. It is used for sorting and ordering purposes.
 *
 * Time Complexity: O(1), constant time for comparison.
 */
bool Student::operator<(const Student &other) const {
    return std::tie(this->studentCode_, this->studentName_) < std::tie(other.studentCode_, other.studentName_);
}

/**
 * @brief Add a UC to the list of UCs associated with the student.
 *
 * This function adds a UC to the list of UCs associated with the student. It appends the UC to the list.
 *
 * Time Complexity: O(1), constant time to append a UC to the list.
 */
void Student::addUC(const UC& uc) {
    ucs_.push_back(uc);
}

/**
 * @brief Check if the student has a class with a specified class code.
 *
 * This function checks if the student has a class with the specified class code by iterating through the list of UCs.
 *
 * Time Complexity: O(n), linear time complexity where 'n' is the number of UCs in the list.
 */
bool Student::hasClass(string classCode) const {
    for(const UC& uc: ucs_){
        if(uc.getClassCode()==classCode){
            return true;
        }
    }
    return false;
}

/**
 * @brief Check if the student has a UC with a specified UC code.
 *
 * This function checks if the student has a UC with the specified UC code by iterating through the list of UCs.
 *
 * Time Complexity: O(n), linear time complexity where 'n' is the number of UCs in the list.
 */
bool Student::hasUC(const string& ucCode) const {
    for(const UC& uc: ucs_){
        if(uc.getUCCode()==ucCode){
            return true;
        }
    }
    return false;
}

/**
 * @brief Create a schedule for the student based on a list of student-UC pairs and UC-lesson pairs.
 *
 * This function creates a schedule for the student based on the provided lists of student-UC pairs and UC-lesson pairs.
 * It collects the UCs associated with the student and adds the corresponding lessons to the schedule.
 *
 * Time Complexity: O(n), linear time complexity where 'n' is the number of student-UC pairs and UC-lesson pairs in the input lists.
 */
Schedule Student::getStudentSchedule(const std::list<std::pair<Student, UC>>& l1,const std::list<std::pair<UC, Lesson>>& l2) const {
    Schedule s = Schedule();
    set<UC> ucs;

    for (const auto& c : l1){
        if (c.first.getStudentCode() == studentCode_){
            ucs.insert(c.second);
        }
    }

    for (const auto& c : l2){
        if (ucs.find(c.first) != ucs.end()){
            s.addLesson(c.first,c.second);
        }
    }

    return s;

}

/**
 * @brief Prints the schedule of a student to the console.
 *
 * This function prints the weekly schedule of a student, including the hours, days of the week, and the lessons they are attending.
 *
 * @param studentCode The code of the student for whom the schedule should be printed.
 * @param l1 A list of pairs containing students and their corresponding classes.
 * @param l2 A list of pairs containing classes and their lessons.
 *
 * Time Complexity: O(n²)
 */
void Student::printStudentTableSchedule(int studentCode,const std::list<std::pair<Student, UC>>& l1,const std::list<std::pair<UC, Lesson>>& l2) const {

    cout << studentName_ + " schedule\n";
    string schedule_ = " ____________________________________________________________________________________________________\n"
                       "|      Hour     |     Monday     |    Tuesday     |    Wednesday   |    Thursday    |     Friday     |\n"
                       "|_______________|________________|________________|________________|________________|________________|\n";


    vector<string> scheduleVector;
    for (int i = 0; i < 24 * 5 * 2; i += 2) {
        scheduleVector.push_back("                |");
        scheduleVector.push_back("________________|");
    }

    Schedule s = Schedule();
    set<UC> ucs;

    for (const auto& c : l1){
        if (c.first.getStudentCode() == studentCode){
            ucs.insert(c.second);
        }
    }

    for (const auto& c : l2){
        if (ucs.find(c.first) != ucs.end()){
            s.addLesson(c.first,c.second);
        }
    }
    for (const UC& ucClass : ucs ){
        for (const auto& lesson : s.getSchedule()){
            int weekDayPos=lesson.second.getWeekday() -1;
            float duration = lesson.second.getDuration();
            int lessonPosition = 24 * 2 * weekDayPos + (lesson.second.getStartHour() - 8.00) * 4;
            //scheduleVector[lessonPosition]=" "+ucClass.getUcCode()+"("+lesson.getType()+")";
            if ("T" == lesson.second.getType()){
                scheduleVector[lessonPosition] = "  "+lesson.first.getUCCode()+"("+lesson.second.getType()+")";
                scheduleVector[lessonPosition] += string(12 - lesson.first.getUCCode().length() - lesson.second.getType().length(), ' ');
            }
            else if((ucClass.getUCCode()) == "UP001"){
                scheduleVector[lessonPosition] = " "+lesson.first.getUCCode()+"("+lesson.second.getType()+")";
                scheduleVector[lessonPosition] += string(11 - lesson.first.getUCCode().length() - lesson.second.getType().length(), ' ');
            }
            else{
                scheduleVector[lessonPosition] = " "+lesson.first.getUCCode()+"("+lesson.second.getType()+")";
                scheduleVector[lessonPosition] += string(13 - lesson.first.getUCCode().length() - lesson.second.getType().length(), ' ');
            }
            scheduleVector[lessonPosition] += "|";

            scheduleVector[++lessonPosition] = "    " + lesson.first.getClassCode() + "     |";

            duration -= 0.5;
            while (duration > 0.5) {
                duration -= 0.5;
                scheduleVector[++lessonPosition] = "                |";
                scheduleVector[++lessonPosition] = "                |";
            }
            scheduleVector[++lessonPosition] = "                |";
        }

    }

    float time = 8.0;
    for (int i = 0; i < 24 * 2; i += 2) {
        if (time < 10 || (time + 0.5 < 10)) schedule_ += "|  ";
        else schedule_ += "| ";

        schedule_ += " "+to_string(static_cast<int>(time)) + ':' + to_string(static_cast<int>((time - static_cast<int>(time)) * 6)) + "0-";

        time += 0.5;
        if (time-static_cast<int>(time)==0){
            schedule_ += to_string(static_cast<int>(time)) + ':' + to_string(static_cast<int>((time - static_cast<int>(time)) * 6))+ "0 ";
        }
        else {
            schedule_ += to_string(static_cast<int>(time)) + ':' + to_string(static_cast<int>((time - static_cast<int>(time)) * 6 * 10))+" ";
        }
        if (time < 10 && (time - 0.5 < 10)) schedule_ += ' ';
        schedule_ += " |" + scheduleVector[i] + scheduleVector[48 * 1 + i] + scheduleVector[48 * 2 + i] + scheduleVector[48 * 3 + i] + scheduleVector[48 * 4 + i] + '\n';
        schedule_ += "|_______________|" + scheduleVector[i + 1] + scheduleVector[48 * 1 + i + 1] + scheduleVector[48 * 2 + i + 1] + scheduleVector[48 * 3 + i + 1] + scheduleVector[48 * 4 + i + 1] + '\n';
    }
    cout << schedule_;
}





