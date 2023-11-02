/**
 * @file data.cpp
 * @brief This file contains the implementation of the Data class.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <map>
#include "Data.h"
using namespace std;

/**
 * @brief Constructor for the Data class. Initializes various data structures.
 *
 * @detail This constructor executes all the necessary methods to populate the data base.
 *
 * Time Complexity: O(1)
 */
Data::Data() {
    readClasses();
    readClassesPerUC();
    readStudentsClasses();
    startNUCsToStudentsMap();
    startUCToClassMap();
    startClassToUCMap();
    startUCToStudentsMap();
    startClassToStudentsMap();
    startYearToStudentsMap();
    startUCClasstoStudentsMap();
}

/**
 * @brief Reads classes and their schedules from the CSV file 'classes.csv' and populates the data structures.
 *
 * @detail This function reads class information from a CSV file and populates the internal
 * data structures. It creates a list of pairs, each containing a UC (course) and a Lesson,
 * representing the class details, such as day of the week, start time, and duration.
 *
 * Time Complexity: O(N), where N is the number of lines in the CSV file.
 *
 * @note This function assumes that the file format is well-formed and doesn't perform extensive
 * error checking for simplicity. Ensure that the file exists and has the correct format.
 */
void Data::readClasses(){
    string f = "../schedule/classes.csv";
    ifstream file(f);
    if (!file.is_open() && !file.good()) {
        std::cerr << "Failed to open file: " << f << endl;
    }
    string line, ClassCode, UcCode, Weekday, Type, StartHour, Duration;
    list<pair<UC,Lesson>> aux;
    getline(file, line);

    map<string, int> WeekdayToNum = {
            {"Monday", 1},
            {"Tuesday", 2},
            {"Wednesday", 3},
            {"Thursday", 4},
            {"Friday", 5}
    };

    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, ClassCode, ',');
        getline(iss, UcCode, ',');
        getline(iss, Weekday, ',');
        getline(iss, StartHour, ',');
        getline(iss, Duration, ',');
        iss >> Type;


        int w = WeekdayToNum[Weekday];
        float sh = stof(StartHour);
        float d = stof(Duration);


        pair<UC,Lesson> p (UC(UcCode,ClassCode), Lesson(w, d, sh, Type));
        aux.push_back(p);
    }
    listClasses_ = aux;
    file.close();
}

/**
 * @brief Reads all the classes and the corresponding UC's from the CSV file 'classes_per_uc.csv' and populates the data structures.
 *
 * @detail This function reads class per UC information from a CSV file and populates the internal
 * data structures. It creates a list of UCs associated with their corresponding classes.
 *
 * Time Complexity: O(N), where N is the number of lines in the CSV file.
 *
 * @note This function assumes that the file format is well-formed and doesn't perform extensive
 * error checking for simplicity. Ensure that the file exists and has the correct format.
 */
void Data::readClassesPerUC(){
    string f = "../schedule/classes_per_uc.csv";
    ifstream file(f);
    if (!file.is_open() && !file.good()) {
        std::cerr << "Failed to open file: " << f << endl;
    }
    string UcCode,ClassCode,line;
    list<UC> aux;
    list<Lesson> Lesson={};
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, ClassCode, ',');
        iss >> UcCode;
        aux.push_back(UC(UcCode, ClassCode, Lesson));
    }
    listClassesPerUC_=aux;
    file.close();
}

/**
 * @brief Reads student classes data from the CSV file 'students_classes.csv' and populates the data structures.
 *
 * @detail This function reads student-class relationships from a CSV file and populates the internal
 * data structures. It creates pairs of students and their associated classes (UC) and also
 * keeps track of unique students. Each student have at least an UC and a class.
 *
 * Time Complexity: O(N), where N is the number of lines in the CSV file.
 *
 * @note This function assumes that the file format is well-formed and doesn't perform extensive
 * error checking for simplicity. Ensure that the file exists and has the correct format.
 */
void Data::readStudentsClasses(){
    string f = "../schedule/students_classes.csv";
    ifstream file(f);
    if (!file.is_open() && !file.good()) {
        std::cerr << "Failed to open file: " << f << endl;
    }
    string StName,StCode, UcCode, ClassCode, line;

    list<pair<Student, UC>> aux;
    getline(file, line);
    while(getline(file, line)) {
        istringstream inn(line);
        getline(inn, StCode, ',');
        getline(inn, StName, ',');
        getline(inn, UcCode, ',');
        inn >> ClassCode;

        int stc = stoi(StCode);

        pair<Student,UC> p (Student(stc,StName), UC(UcCode, ClassCode));
        aux.push_back(p);
        students_.insert(Student(stc,StName));

    }
    listStudentsClasses_ = aux;
    file.close();
}

/**
 * @brief Gets the list of class data, containing the schedule of each class. It was defined in readClasses().
 * @return A list of pairs, each containing UC and Lesson information.
 * Time Complexity: O(1)
 */
std::list<std::pair<UC, Lesson>> Data::getListClasses_() const {
    return listClasses_;
}

/**
 * @brief Gets the list of classes per UC, containing all the classes and corresponding UC's.It was defined in readClassesPerUC().
 * @return A list of UC objects representing classes per UC.
 *
 * Time Complexity: O(1)
 */
std::list<UC> Data::getListClassesPerUC_() {
    return listClassesPerUC_;
}

/**
 * @brief Gets the list of students on each class. It was defined in readClassesPerUC().
 * @return A list of pairs, each containing Lesson and UC information.
 *
 * Time Complexity: O(1)
 */
std::list<std::pair<Student, UC>> Data::getListStudentsClasses_() {
    return listStudentsClasses_;
}
/**
 * @brief Gets the list of all the students. It was defined in readStudentsClasses().
 * @return A set of students, containing all the students.
 *
 * Time Complexity: O(1)
 */
set<Student> Data::getStudents(){
    return students_;
}
/**
 * @brief Sets the list of student-class associations.
 * @param l The new list of pairs, each containing Student and UC information.
 *
 * Time Complexity: O(1)
 */
void Data::setListStudentsClasses_(std::list<std::pair<Student, UC>> l){
    listStudentsClasses_= l;
}

/**
 * @brief Prints the list of students in ascending order of their student codes.
 * Each line displays the student code followed by the student name.
 *
 * Time Complexity: O(n * log(n)), where 'n' is the number of students and sorted by the operator < defined in the class Student.
 *
 * @detail This function iterates through the set of students and prints their student codes
 * along with their names. The students are printed in ascending order of their student codes.
 */
void Data::printStudentsAscendingCode(){
    for ( const auto& student: students_){
        cout << student.getStudentCode() << " - " << student.getStudentName()<< endl;
    }
}

/**
 * @brief Prints the list of students in descending order of their student codes.
 * Each line displays the student code followed by the student name.
 *
 * Time Complexity: O(n * log(n)), where 'n' is the number of students and sorted by the operator < defined in the class Student.
 *
 * @detail This function iterates through the set of students and prints their student codes
 * along with their names. The students are printed in descending order of their student codes.
 */
void Data::printStudentsDescendingCode() {
    vector<Student> studentsVector(students_.begin(), students_.end());
    std::sort(studentsVector.rbegin(), studentsVector.rend());

    for (const auto& student : studentsVector) {
        cout << student.getStudentCode() << " - " << student.getStudentName() << endl;
    }
}

/**
 * @brief Prints the list of students in ascending order of their student codes.
 *
 * @detail This function iterates through the set of students and prints each student's code followed by their name.
 * The list is sorted in ascending order based on student codes.
 *
 * Time complexity: O(n * log(n)), where 'n' is the number of students.
 */
void Data::printStudentsAscendingName() {
    vector<Student> studentsVector(students_.begin(), students_.end());
    std::sort(studentsVector.begin(), studentsVector.end(), [](const Student& a, const Student& b) {
        return a.getStudentName() < b.getStudentName();
    });

    for (const auto& student : studentsVector) {
        cout << student.getStudentName() << " - " << student.getStudentCode() << endl;
    }
}

/**
 * @struct CompareStudentsByName
 * @brief Functor for comparing students by their names in descending order.
 *
 * @detail This struct provides a custom comparison operator to compare students by their names.
 * It is designed for use with standard sorting algorithms like std::sort to sort students
 * in descending order of their names.
 *
 * Time Complexity: O(n * log(n)), where 'n' is the number of students being sorted.
 */
struct CompareStudentsByName {
    /**
    * @brief Comparison operator to compare students by their names.
    *
    * @param lhs The left-hand side student for comparison.
    * @param rhs The right-hand side student for comparison.
    * @return True if the name of 'lhs' is greater (lexicographically) than the name of 'rhs'.
    */
    bool operator()(const Student& lhs, const Student& rhs) const {
        return lhs.getStudentName() > rhs.getStudentName();
    }
};

/**
 * @brief Prints the list of students in descending order of their names.
 * Each line displays the student name followed by the student code.
 *
 * @detail This function creates a sorted set of students based on their names in descending order,
 * and then iterates through the set, printing the student names followed by their codes.
 *
 * Time Complexity: O(N * log(N)), where N is the number of students.
 */
void Data::printStudentsDescendingName() {
    set<Student, CompareStudentsByName> students;

    for (const auto& student : students_) {
        students.insert(student);
    }

    for (const auto& student : students) {
        cout << student.getStudentName() << " - " << student.getStudentCode()<< endl;
    }
}

/**
 * @brief Initializes a map that groups students by their admission year.
 *
 * @detail This function processes the list of students and creates a mapping where each
 * admission year corresponds to a set of students who started in that year.
 * The map yearToStudentsMap_ is populated with this information.
 *
 * Time complexity: O(n), where 'n' is the number of students.
 */
void Data::startYearToStudentsMap(){
    for (const auto& c : listStudentsClasses_){
        yearToStudentsMap_[c.first.getStudentCode()/100000].insert(c.first);
    }
}

/**
 * @brief Retrieves the map that groups students by their admission year.
 *
 * @detail This function returns the map yearToStudentsMap_, which associates each admission year with a set of students
 * who started in that year. You can use this map to access the grouped students by their admission year.
 *
 * @return A map where the keys are admission years and the values are sets of students.
 *
 * Time complexity: O(1)
 */
map<int, set<Student>> Data::getYearToStudentsMap(){
    return yearToStudentsMap_;
}

/**
 * @brief Prints the students who started in a specific admission year.
 *
 * @detail This function prints the names and student codes of the students who were admitted in the given admission year.
 * If there are no students admitted in that year, it will not display anything.
 *
 * @param x The admission year for which you want to print students.
 * @param m The map associating admission years with sets of students.
 *
 * Time complexity: O(n), where 'n' is the number of students.
 */
void Data::printStudentsByYear(int x, const map<int, set<Student>>& m) {
    auto i = m.find(x);
    if (i != m.end()) {
        for (const auto &c : i->second) {
            cout << c.getStudentName() << " (" << c.getStudentCode() << ")" << '\n';
        }
    }
}

/**
 * @brief Get the number of students in a specific year.
 *
 * @detail This function retrieves the number of students in a given academic year based on a map
 * that associates years with sets of students.
 *
 * @param x The academic year for which to count the students.
 * @param m A map that associates academic years with sets of students.
 * @return The number of students in the specified academic year.
 *
 * @note The function returns 0 if the specified academic year is not found in the map.
 *
 * Time Complexity: O(1)
 */

int Data::numberOfStudentsByYear(int x,const map<int, set<Student>>& m){
    auto i = m.find(x);
    if (i != m.end()) {
        return (int) i->second.size();
    }
    else return 0;
}

/**
 * @brief Initialize a map associating class codes with sets of students.
 *
 * @detail This function iterates through the list of student-class pairs and populates
 * a map that associates class codes with sets of students enrolled in each class.
 *
 * Time Complexity: O(n), where 'n' is the number of student-class pairs.
 */
void Data::startClassToStudentsMap(){
    for (const auto& c : listStudentsClasses_){
        classToStudentsMap_[c.second.getClassCode()].insert(c.first);
    }
}

/**
 * @brief Retrieve the map associating class codes with sets of students.
 *
 * This function returns the map that associates class codes with sets of students
 * enrolled in each class. Make sure to call Data::startClassToStudentsMap before
 * using this function to ensure the map is properly initialized.
 *
 * @return A map where class codes are keys, and sets of students are values.
 *
 * Time Complexity: O(1)
 */
map<string, set<Student>> Data::getClassToStudentsMap(){
    return classToStudentsMap_;
}

/**
 * @brief Print the list of students in a specific class.
 *
 * This function prints the list of students in a class identified by the given class code.
 *
 * @param x The class code for which to print the list of students.
 * @param m A map associating class codes with sets of students.
 *
 * Time Complexity: O(n), where 'n' is the number of students in the specified class.
 */
void Data::printStudentsByClass(const string& x,const map<string, set<Student>>& m){

    auto i = m.find(x);
    if (i != m.end()) {
        for (const auto &c: i->second) {
            cout << c.getStudentName() << " (" << c.getStudentCode() << ")" << '\n';
        }
    }
}

/**
 * @brief Get the number of students in a specific class.
 *
 * This function returns the number of students in a class identified by the given class code.
 *
 * @param x The class code for which to retrieve the number of students.
 * @param m A map associating class codes with sets of students.
 *
 * @return The number of students in the specified class.
 *
 * Time Complexity: O(1) - Constant time, as it involves a single map lookup operation.
 */
int Data::numberOfStudentsInClass(const string& x,const map<string, set<Student>>& m) {
    auto i = m.find(x);
    if (i != m.end()) {
        return (int) i->second.size();
    }
    else return 0;
}

/**
 * @brief Initialize a map associating UC (Course) codes with sets of students.
 *
 * This function iterates through the list of student-class pairs and populates
 * a map that associates UC (Course) codes with sets of students enrolled in each UC.
 *
 * Time Complexity: O(n), where 'n' is the number of student-class pairs.
 */
void Data::startUCToStudentsMap(){
    for (const auto& c : listStudentsClasses_){
        ucToStudentsMap_[c.second.getUCCode()].insert(c.first);
    }
}

/**
 * @brief Get a map associating UC (Course) codes with sets of students.
 *
 * This function returns a map that associates UC (Course) codes with sets of students enrolled in each UC.
 *
 * @return A map where each key is a UC (Course) code, and the associated value is a set of students in that UC.
 *
 * Time Complexity: O(1)
 */
map<string, set<Student>> Data::getUCToStudentsMap(){
    return ucToStudentsMap_;
}

/**
 * @brief Print the list of students in a specific UC along with their names and student codes.
 *
 * This function prints the list of students in a specific UC along with their names and student codes.
 *
 * @param x The UC code for which to print the students.
 * @param m A map associating UC (Course) codes with sets of students.
 *
 * Time Complexity: O(n), where 'n' is the number of students in the specified UC.
 */
void Data::printStudentsInUC(const string& x,const map<string, set<Student>>& m){

    auto i = m.find(x);
    if (i != m.end()) {
        for (const auto &c: i->second) {
            cout << c.getStudentName() << " (" << c.getStudentCode() << ")" << '\n';
        }
    }
}

/**
 * @brief Get the number of students in a specific UC (Course).
 *
 * This function returns the number of students in a specific UC (Course) based on the provided UC code.
 *
 * @param x The UC (Course) code for which to retrieve the number of students.
 * @param m A map associating UC (Course) codes with sets of students.
 *
 * @return The number of students in the specified UC.
 *
 * Time Complexity: O(1) on average, assuming constant-time map lookup.
 */
int Data::numberOfStudentsInUC(const string& x,const map<string, set<Student>>& m) {
    auto i = m.find(x);
    if (i != m.end()) {
        return (int) i->second.size();
    }
    else return 0;
}
/**
 * @brief Initialize a map associating the number of UCs to a list of students.
 *
 * This function calculates the number of UCs (Courses) associated with each student and populates a map
 * that associates the number of UCs to a list of students who are enrolled in that many UCs.
 *
 * Time Complexity: O(n), where 'n' is the number of student-class pairs.
 */
void Data::startNUCsToStudentsMap(){

    std::map<int, int> studentCodeToN;

    for (const auto& d : listStudentsClasses_) {
        studentCodeToN[d.first.getStudentCode()]++;
    }

    for (const auto& d : listStudentsClasses_) {
        Student s = d.first;
        int c = studentCodeToN[s.getStudentCode()];

        nUCsToStudentsMap_[c].insert(s);
    }
}

/**
 * @brief Retrieve a map associating the number of UCs to a list of students.
 *
 * This function returns a map that associates the number of UCs (Courses) with a list of students
 * who are enrolled in that many UCs.
 *
 * @return A map where the keys represent the number of UCs and the values are lists of students.
 *
 * Time Complexity: O(1)
 */
map<int, set<Student>> Data::getNUCsToStudentsMap(){
    return nUCsToStudentsMap_;
}

/**
 * @brief Print students with a specific number of enrolled UCs.
 *
 * This function prints the list of students who are enrolled in a specific number of UCs.
 * If there are no students with the given number of UCs, nothing will be printed.
 *
 * @param n The number of UCs for which to retrieve and print students.
 * @param m A map where the keys represent the number of UCs, and the values are lists of students.
 *
 *  * Time Complexity: O(1) for finding the list of students with the specified number of UCs.
 */
void Data::printStudentsWithNUCs(int n,const map<int, set<Student>>& m){

    auto i= m.find(n);

    if (i == m.end()){
        return;
    }
    else {
        for (const auto& s: i->second) {
            cout << s.getStudentName() << " (" << s.getStudentCode() << ")\n";
        }
    }
}

/**
 * @brief Get the number of students with a specific number of enrolled UCs.
 *
 * This function returns the number of students who are enrolled in a specific number of UCs.
 *
 * @param n The number of UCs for which to retrieve the number of students.
 * @param m A map where the keys represent the number of UCs, and the values are lists of students.
 *
 * @return The number of students with the specified number of UCs.
 *
 *  * Time Complexity: O(1) for finding the list of students with the specified number of UCs.
 */
int Data::numberStudentsWithNUCs(int n,const map<int, set<Student>>& m){

    auto i= m.find(n);

    if (i == m.end()){
        return 0;
    }
    else {
        return (int) i->second.size();
    }
}

/**
 * @brief Initialize a map associating UC codes with sets of class codes.
 *
 * This function iterates through the list of student-class pairs and populates
 * a map that associates UC codes with sets of class codes in which students are enrolled.
 *
 * Time Complexity: O(n), where 'n' is the number of student-class pairs.
 */
void Data::startUCToClassMap(){
    for (const auto& d : listStudentsClasses_) {
        ucToClassMap_[d.second.getUCCode()].insert(d.second.getClassCode());
    }
}

/**
 * @brief Initialize a map associating class codes with sets of UC codes.
 *
 * This function iterates through the list of student-class pairs and populates
 * a map that associates class codes with sets of UC codes for each class.
 *
 * Time Complexity: O(n), where 'n' is the number of student-class pairs.
 */
void Data::startClassToUCMap(){
    for (const auto& d : listStudentsClasses_) {
        classToUCMap_[d.second.getClassCode()].insert(d.second.getUCCode());
    }
}

/**
 * @brief Get the map associating UC codes with sets of class codes.
 *
 * This function returns the map that associates UC codes with sets of class codes
 * for each UC.
 *
 * @return A map that associates UC codes with sets of class Codes for each UC.
 *
 * Time Complexity: O(1)
 */
map<string, set<string>> Data::getUCToClassMap(){
    return ucToClassMap_;
}

/**
 * @brief Get the map associating class codes with sets of UC codes.
 *
 * This function returns the map that associates class codes with sets of UC codes
 * for each class.
 *
 * * @return A map that associates class codes with sets of UC Codes for each class.
 *
 * Time Complexity: O(1)
 */
map<string, set<string>> Data::getClassToUcMap(){
    return classToUCMap_;
}

/**
 * @brief Print the class codes associated with a specific UC code.
 *
 * This function prints the class codes associated with a specific UC code.
 *
 * @param UCCode The UC code for which class codes are to be printed.
 * @param m The map associating UC codes with sets of class codes.
 *
 * Time Complexity: O(n), where 'n' is the number of UC code to class code associations.
 */
void Data::printClassByUCs(const string& UCCode,map<string, set<string>> m){
    auto i = m.find(UCCode);
    if (i != m.end()) {
        for (const auto& c : i->second) {
            cout << c << endl;
        }
    }
}

/**
 * @brief Print the UC codes associated with a specific class code.
 *
 * This function prints the UC codes associated with a specific class code.
 *
 * @param CCode The class code for which UC codes are to be printed.
 * @param m The map associating class codes with sets of UC codes.
 *
 * Time Complexity: O(n), where 'n' is the number of class code to UC code associations.
 */
void Data::printUCsByClass(const string& CCode,map<string, set<string>> m){
    auto i = m.find(CCode);
    if (i != m.end()) {
        for (const auto& u : i->second) {
            cout << u << endl;
        }
    }
}

/**
 * @brief Print the schedule of a class based on its class code.
 *
 * This function prints the class schedule for a specific class identified by its class code. The schedule
 * displays class hours and days of the week with associated UCs and lesson types.
 *
 * @param classCode The class code for which the schedule is to be printed.
 *
 * Time Complexity: O(n), where 'n' is the number of classes in the list of classes.
 */
void Data::printClassTableSchedule(const string& classCode) const{

    cout << classCode + " schedule\n";
    string schedule_ = " ____________________________________________________________________________________________________\n"
                       "|      Hour     |     Monday     |    Tuesday     |    Wednesday   |    Thursday    |     Friday     |\n"
                       "|_______________|________________|________________|________________|________________|________________|\n";


    vector<string> scheduleVector;
    for (int i = 0; i < 24 * 5 * 2; i += 2) {
        scheduleVector.push_back("                |");
        scheduleVector.push_back("________________|");
    }
    for (const auto& ucClass : getListClasses_() ){
        if (ucClass.first.getClassCode() == classCode) {
            Lesson lesson= ucClass.second;
            int weekDayPos=lesson.getWeekday() -1;

            float duration = lesson.getDuration();
            int lessonPosition = 24 * 2 * weekDayPos + (lesson.getStartHour() - 8.00) * 4;



            if (ucClass.first.getUCCode().length() + lesson.getType().length() +2 < 14) {
                if ("T" == ucClass.second.getType()){
                    scheduleVector[lessonPosition] = "  " + ucClass.first.getUCCode() + "(" + lesson.getType() + ")";
                    scheduleVector[lessonPosition] += string(12 - ucClass.first.getUCCode().length() - lesson.getType().length(), ' ');
                }
                else if((ucClass.first.getUCCode()) == "UP001"){
                    scheduleVector[lessonPosition] = "   " + ucClass.first.getUCCode() + "(" + lesson.getType() + ")";
                    scheduleVector[lessonPosition] += string(11 - ucClass.first.getUCCode().length() - lesson.getType().length(), ' ');
                }
                else{
                    scheduleVector[lessonPosition] = " " + ucClass.first.getUCCode() + "(" + lesson.getType() + ")";
                    scheduleVector[lessonPosition] += string(13 - ucClass.first.getUCCode().length() - lesson.getType().length(), ' ');
                }
            }
            scheduleVector[lessonPosition] += "|";

            scheduleVector[++lessonPosition] = "    " + ucClass.first.getClassCode() + "     |";

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

        schedule_ +=" "+to_string(static_cast<int>(time)) + ':' + to_string(static_cast<int>((time - static_cast<int>(time)) * 6)) + "0-";

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

/**
 * @brief Print the schedule of a specific class.
 *
 * This function prints the schedule of a specific class identified by its class code. It collects
 * the relevant class schedules and then calls the `printSchedule` function to display the class's schedule.
 *
 * @param classCode The class code for which the schedule is to be printed.
 * @param classes_per_uc The list of classes per UC.
 * @param getListClasses The list of classes with their lessons.
 *
 * Time Complexity: O(n), where 'n' is the total number of class-lesson pairs in the 'getListClasses' list.
 */
void Data::printClassSchedule(const string& classCode, const std::list<UC>& classes_per_uc, const std::list<std::pair<UC, Lesson>>& getListClasses) {
    Schedule s = Schedule();

    for (const auto& c : getListClasses){
        if (c.first.getClassCode() == classCode){
            s.addLesson(c.first,c.second);
        }
    }
    s.printSchedule();
}

/**
 * @brief Print the top 5 Undergraduate Courses (UCs) with the most students.
 *
 * This function prints the top 5 UCs with the most students enrolled in them.
 *
 * @param m A map that associates UC codes with sets of students.
 *
 * Time Complexity: O(n * log(n)), where 'n' is the number of distinct UCs.
 */
void Data::printTop5UCs(const map<string, set<Student>>& m) {

    vector<pair<string, int>> vec;

    for (const auto& c : m) {
        int a = c.second.size();
        pair<string,int> p = {c.first, a};
        vec.push_back(p);
    }

    sort(vec.begin(), vec.end(),[](const pair<string, int>& a, const pair<string, int>& b){
             return a.second > b.second;
         });

    cout << "1. UC: " << vec[0].first << " -> " << vec[0].second << " students" << endl;
    cout << "2. UC: " << vec[1].first << " -> " << vec[1].second << " students" << endl;
    cout << "3. UC: " << vec[2].first << " -> " << vec[2].second << " students" << endl;
    cout << "4. UC: " << vec[3].first << " -> " << vec[3].second << " students" << endl;
    cout << "5. UC: " << vec[4].first << " -> " << vec[4].second << " students" << endl;
}

/**
 * @brief Initialize a map associating UC-Classes with sets of students.
 *
 * This function iterates through the list of student-class pairs and populates
 * a map that associates UC-Classes with sets of students enrolled in each UC-Class.
 * If the UC-Class is not already in the map, it is added with an empty set of students.
 *
 * Time Complexity: O(n), where 'n' is the number of student-class pairs.
 */
void Data::startUCClasstoStudentsMap() {
    for (const auto& c : listStudentsClasses_){
        if (ucClasstoStudentsMap_.find(c.second) != ucClasstoStudentsMap_.end()){
            ucClasstoStudentsMap_[c.second].insert(c.first);
        }
        else{
            ucClasstoStudentsMap_[c.second] = set<Student>();
        }
    }
}

/**
 * @brief Get a map associating UC-Classes with sets of students.
 *
 * This function returns a map that associates UC-Classes with sets of students enrolled in each UC-Class.
 *
 * @return A map where each UC-Class (UC) is mapped to a set of students (Student) enrolled in that UC-Class.
 *
 * Time Complexity: O(1).
 */
std::map<UC, std::set<Student>> Data::getUCClasstoStudentsMap() {
    return ucClasstoStudentsMap_;
}

/**
 * @brief Print the list of students in a specific UC-Class.
 *
 * This function prints the list of students enrolled in a specific UC-Class specified by the provided UC code and Class code.
 *
 * @param ucCode The UC code (e.g., "UC001") of the target UC.
 * @param classCode The Class code (e.g., "C101") of the target Class.
 * @param m A map that associates UC-Classes (UC) with sets of students (Student).
 *
 * Time Complexity: O(n), where 'n' is the number of students in the specified UC-Class.
 */
void Data::printStudentsInUCClass(const string &ucCode, const string &classCode, std::map<UC, std::set<Student>> m) {
    UC a = UC(ucCode,classCode);
    for(const auto& s : m[a]){
        cout << s.getStudentName() << " (" << s.getStudentCode() << ")\n";
    }
}

/**
 * @brief Get the number of students in a specific UC-Class.
 *
 * This function returns the number of students enrolled in a specific UC-Class specified by the provided UC code and Class code.
 *
 * @param ucCode The UC code (e.g., "UC001") of the target UC.
 * @param classCode The Class code (e.g., "C101") of the target Class.
 * @param m A map that associates UC-Classes (UC) with sets of students (Student).
 *
 * @return The number of students in the specified UC-Class.
 *
 * Time Complexity: O(1).
 */
int Data::numberOfStudentsInUCClass(const string &ucCode, const string &classCode, std::map<UC, std::set<Student>> m) {
    UC a = UC(ucCode,classCode);
    return (int) m[a].size();
}




