#include "Student.h"
#include <string>
#include <set>

using namespace std;

Student::Student(){

}
Student::Student(int studentCode, string studentName, list<UC> ucs){
    studentCode_ = studentCode;
    studentName_ = studentName;
    ucs_ = ucs;
}

Student::Student(int studentCode, string studentName){
    studentCode_ = studentCode;
    studentName_ = studentName;
}

Student::Student(int studentCode){
    studentCode_ = studentCode;
}


int Student::get_StudentCode() const {
    return studentCode_;
}

string Student::get_StudentName() const {
    return studentName_;
}

string Student::findName(const list<pair<Student, UC>>& listStudents_Classes , int num) {
    for (const auto& c : listStudents_Classes) {
        if (c.first.studentCode_ == num) {
            return c.first.studentName_;
        }
    }
    return "";
}


list<UC> Student::get_Ucs() const {
    return ucs_;
}
void Student::set_StudentCode(int StudentCode) {
    studentCode_ = StudentCode;
}

void Student::set_StudentName(string StudentName) {

    studentName_ = StudentName;
}
void Student::set_Ucs(list<UC> ucs) {
    ucs_ = ucs;
}

bool Student::operator<(const Student &other) const {
    return std::tie(this->studentCode_, this->studentName_) < std::tie(other.studentCode_, other.studentName_);
}

void Student::add_UC(UC uc) {
    ucs_.push_back(uc);
}
bool Student::has_Class(string classCode) const {
    for(UC uc: ucs_){
        if(uc.getClassCode()==classCode){
            return true;
        }
    }
    return false;
}
bool Student::has_Uc(string ucCode) const {
    for(UC uc: ucs_){
        if(uc.getUcCode()==ucCode){
            return true;
        }
    }
    return false;
}

Schedule Student::getStudentSchedule(const std::list<std::pair<Student, UC>>& l1,const std::list<std::pair<UC, Lesson>>& l2) const {
    Schedule s = Schedule();
    set<UC> ucs;

    for (const auto& c : l1){
        if (c.first.get_StudentCode() == studentCode_){
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

void Student::printStudentTableSchedule(int studentCode,const std::list<std::pair<Student, UC>>& l1,const std::list<std::pair<UC, Lesson>>& l2) const {

    cout << studentName_ + " schedule\n";
    string schedule_ = " ________________________________________________________________________________________\n"
                       "|     Hour    |    Monday    |   Tuesday    |   Wednesday  |   Thursday   |    Friday    |\n"
                       "|________________________________________________________________________________________|\n";


    vector<string> scheduleVector;
    for (int i = 0; i < 24 * 5 * 2; i += 2) {
        scheduleVector.push_back("              |");
        scheduleVector.push_back("______________|");
    }

    Schedule s = Schedule();
    set<UC> ucs;

    for (const auto& c : l1){
        if (c.first.get_StudentCode() == studentCode){
            ucs.insert(c.second);
        }
    }

    for (const auto& c : l2){
        if (ucs.find(c.first) != ucs.end()){
            s.addLesson(c.first,c.second);
        }
    }
    for (const UC& ucClass : ucs ){
        for (auto lesson : s.getSchedule()){
            int weekDayPos=lesson.second.getWeekday() -1;
            float duration = lesson.second.getDuration();
            int lessonPosition = 24 * 2 * weekDayPos + (lesson.second.getStartHour() - 8.00) * 4;
            //scheduleVector[lessonPosition]=" "+ucClass.getUcCode()+"("+lesson.getType()+")";
            if ("T" == lesson.second.getType()){
                scheduleVector[lessonPosition] = " "+lesson.first.getUcCode()+"("+lesson.second.getType()+")";
                scheduleVector[lessonPosition] += string(10 - lesson.first.getUcCode().length() - lesson.second.getType().length(), ' ');
            }
            else if((ucClass.getUcCode()) == "UP001"){
                scheduleVector[lessonPosition] = " "+lesson.first.getUcCode()+"("+lesson.second.getType()+")";
                scheduleVector[lessonPosition] += string(9 - lesson.first.getUcCode().length() - lesson.second.getType().length(), ' ');
            }
            else{
                scheduleVector[lessonPosition] = " "+lesson.first.getUcCode()+"("+lesson.second.getType()+")";
                scheduleVector[lessonPosition] += string(11 - lesson.first.getUcCode().length() - lesson.second.getType().length(), ' ');
            }
            scheduleVector[lessonPosition] += "|";

            scheduleVector[++lessonPosition] = "   " + lesson.first.getClassCode() + "    |";

            duration -= 0.5;
            while (duration > 0.5) {
                duration -= 0.5;
                scheduleVector[++lessonPosition] = "              |";
                scheduleVector[++lessonPosition] = "              |";
            }
            scheduleVector[++lessonPosition] = "              |";
        }

    }

    float time = 8.0;
    for (int i = 0; i < 24 * 2; i += 2) {
        if (time < 10 || (time + 0.5 < 10)) schedule_ += "|  ";
        else schedule_ += "| ";

        schedule_ +=to_string(static_cast<int>(time)) + ':' + to_string(static_cast<int>((time - static_cast<int>(time)) * 6)) + "0-";

        time += 0.5;
        if (time-static_cast<int>(time)==0){
            schedule_ += to_string(static_cast<int>(time)) + ':' + to_string(static_cast<int>((time - static_cast<int>(time)) * 6))+ "0";
        }
        else {
            schedule_ += to_string(static_cast<int>(time)) + ':' + to_string(static_cast<int>((time - static_cast<int>(time)) * 6 * 10));
        }
        if (time < 10 && (time - 0.5 < 10)) schedule_ += ' ';
        schedule_ += " |" + scheduleVector[i] + scheduleVector[48 * 1 + i] + scheduleVector[48 * 2 + i] + scheduleVector[48 * 3 + i] + scheduleVector[48 * 4 + i] + '\n';
        schedule_ += "|_____________|" + scheduleVector[i + 1] + scheduleVector[48 * 1 + i + 1] + scheduleVector[48 * 2 + i + 1] + scheduleVector[48 * 3 + i + 1] + scheduleVector[48 * 4 + i + 1] + '\n';
    }
    cout << schedule_;
}





