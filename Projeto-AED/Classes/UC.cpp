#include "UC.h"
using namespace std;

UC::UC(){
    numberStudents_ = 0;
}
int UC::capacity_ = 26;

UC::UC(string ucCode){
    numberStudents_ = 0;
    ucCode_ = ucCode;
}


UC::UC(string ucCode,string classCode){
    ucCode_= ucCode;
    classCode_ = classCode;
    numberStudents_ = 0;
}

UC::UC(string ucCode, string classCode, list<Lesson> lesson) : ucCode_(ucCode), classCode_(classCode), lesson_(lesson) {
    numberStudents_ = 0;
}


string UC::getUcCode() const {
    return ucCode_;
}

string UC::getClassCode() const {
    return classCode_;
}
int UC::getNumberStudents() const {
    return numberStudents_;
}
void UC::setNumberStudents(int newValue){
    numberStudents_=newValue;
}
void UC::addLesson(const Lesson& lesson) {
    lesson_.push_back(lesson);
}
list<Lesson> UC::getLessons() const{
    return lesson_;
}

bool UC::operator<(const UC& UC) const{
    if(ucCode_ < UC.ucCode_){
        return true;
    }
    else if(ucCode_ == UC.ucCode_){
        if(classCode_ < UC.classCode_){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}

void UC::addClassLessons(const std::list<std::pair<UC, Lesson>>& l1){
    for (const auto& c : l1){
        if (c.first.ucCode_ == ucCode_ && c.first.classCode_ == classCode_){
            addLesson(c.second);
        }
    }
}

void UC::printLessons() const {
    map<int, string> NumToWeekday = {
            {1, "Monday"},
            {2, "Tuesday"},
            {3, "Wednesday"},
            {4, "Thursday"},
            {5, "Friday"}
    };
    map<string, string> UcCodeToName = {
            {"L.EIC001", "ALGA"},
            {"L.EIC002", "AMI"},
            {"L.EIC003", "FP"},
            {"L.EIC004", "FSC"},
            {"L.EIC005", "MD"},
            {"L.EIC006", "AC"},
            {"L.EIC007", "AMII"},
            {"L.EIC008", "FI"},
            {"L.EIC009", "P"},
            {"L.EIC010", "TC"},
            {"L.EIC011", "AED"},
            {"L.EIC012", "BD"},
            {"L.EIC013", "FII"},
            {"L.EIC014", "LDTS"},
            {"L.EIC015", "SO"},
            {"L.EIC016", "DA"},
            {"L.EIC017", "ES"},
            {"L.EIC018", "LC"},
            {"L.EIC019", "LTW"},
            {"L.EIC020", "ME"},
            {"L.EIC021", "FSI"},
            {"L.EIC022", "IPC"},
            {"L.EIC023", "LBAW"},
            {"L.EIC024", "PFL"},
            {"L.EIC025", "RC"},
            {"UP001", "PUP"}
    };
    cout << UcCodeToName[ucCode_] << ":\n";
    list<Lesson> l = lesson_;
    l.sort();
    for (const Lesson& lesson : l) {
        cout << "\t" << NumToWeekday[lesson.getWeekday()] << "| Start: " << toTime(lesson.getStartHour());
        if (lesson.getDuration() == 1){
            cout << " -> " << toTime(lesson.getStartHour() + lesson.getDuration()) << " hours " << "(" << toTime(lesson.getDuration()) << " hour" << ")"  "| ";
        }
        else{
            cout << " -> " << toTime(lesson.getStartHour() + lesson.getDuration()) << " hours " << "(" << toTime(lesson.getDuration()) << " hours" << ")"  "| ";
        }
        cout << lesson.getType() << endl;
    }
}

std::string UC::toTime(float hour) {
    int hrs = (int) hour;
    int mins = (int) ((hour-hrs)*60);
    if (mins > 10){
        return to_string(hrs) + ":" + to_string(mins);
    }
    else{
        return to_string(hrs) + ":" + "0" + to_string(mins);
    }
}

Schedule UC::getSchedule(const std::list<std::pair<UC, Lesson>>& l1) {
    Schedule s = Schedule();
    for (const auto& c : l1){
        if (c.first.ucCode_ == ucCode_){
            s.addLesson(c.first,c.second);
        }
    }
    return s;
}
