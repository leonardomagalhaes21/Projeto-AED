#include "UC.h"
using namespace std;
/**
 * @brief Default constructor for the UC class.
 *
 * This constructor initializes a UC object with default values. It does not perform any significant operations.
 *
 * Time Complexity: O(1), constant time for object initialization.
 */
UC::UC(){
    numberStudents_ = 0;
}

/**
 * @brief Static attribute 'capacity_' for the UC class.
 *
 * This is a static attribute that has a fixed value of 26, representing the capacity of UCs.
 *
 * Time Complexity: O(1), constant time for static attribute initialization.
 */
int UC::capacity_ = 26;

/**
 * @brief Constructor for the UC class with a specified UC code.
 *
 * This constructor creates a UC object with the given UC code and initializes the attributes accordingly.
 *
 *@param ucCode: The unique code for the UC.
 *
 * @param ucCode: The unique code for the UC.
 * @param classCode: The class code for the UC.
 *
 * Time Complexity: O(1), constant time for object initialization and attribute assignment.
 */
UC::UC(string ucCode){
    numberStudents_ = 0;
    ucCode_ = ucCode;
}

/**
 * @brief Constructor for the UC class with specified UC code and class code.
 *
 * This constructor creates a UC object with the given UC code and class code, initializing the attributes accordingly.
 *
 * Time Complexity: O(1), constant time for object initialization and attribute assignment.
 */
UC::UC(string ucCode,string classCode){
    ucCode_= ucCode;
    classCode_ = classCode;
    numberStudents_ = 0;
}

/**
 * @brief Constructor for the UC class with specified UC code, class code, and a list of lessons.
 *
 * This constructor creates a UC object with the given UC code, class code, and a list of lessons. It initializes the attributes accordingly.
 *
 * @param ucCode: The unique code for the UC.
 * @param classCode: The class code for the UC.
 * @param lesson: A list of lessons associated with the UC.
 *
 * Time Complexity: O(1), constant time for object initialization and attribute assignment.
 */
UC::UC(string ucCode, string classCode, list<Lesson> lesson) : ucCode_(ucCode), classCode_(classCode), lesson_(lesson) {
    numberStudents_ = 0;
}

/**
 * @brief Get the UC code of the UC.
 *
 * This function returns the UC code of the UC.
 *
 * Time Complexity: O(1), constant time to return the attribute.
 */
string UC::getUCCode() const {
    return ucCode_;
}

/**
 * @brief Get the class code of the UC.
 *
 * This function returns the class code of the UC.
 *
 * Time Complexity: O(1), constant time to return the attribute.
 */
string UC::getClassCode() const {
    return classCode_;
}

/**
 * @brief Get the number of students registered for the UC.
 *
 * This function returns the number of students registered for the UC.
 *
 * Time Complexity: O(1), constant time to return the attribute.
 */
int UC::getNumberStudents() const {
    return numberStudents_;
}

/**
 * @brief Set the number of students registered for the UC.
 *
 * This function sets the number of students registered for the UC to the specified value.
 *
 * @param newValue: The new number of students registered for the UC.
 *
 * Time Complexity: O(1), constant time to assign the attribute.
 */
void UC::setNumberStudents(int newValue){
    numberStudents_=newValue;
}

/**
 * @brief Add a lesson to the UC.
 *
 * This function adds a lesson to the list of lessons associated with the UC. It appends the lesson to the list.
 *
 * @param lesson: The lesson to be added to the UC.
 *
 * Time Complexity: O(1), constant time to append a lesson to the list.
 */
void UC::addLesson(const Lesson& lesson) {
    lesson_.push_back(lesson);
}

/**
 * @brief Get the list of lessons associated with the UC.
 *
 * This function returns the list of lessons associated with the UC.
 *
 * Time Complexity: O(1), constant time to return the attribute.
 */
list<Lesson> UC::getLessons() const{
    return lesson_;
}

/**
 * @brief Compare two UCs for ordering based on their UC code and class code.
 *
 * This function compares two UC objects based on their UC code and class code. It is used for sorting and ordering purposes.
 *
 * @param UC: The UC object to be compared to.
 *
 * Time Complexity: O(1), constant time for comparison.
 */
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

/**
 * @brief Add lessons to the UC based on a list of UC-lesson pairs.
 *
 * This function adds lessons to the UC based on the provided list of UC-lesson pairs. It checks if the UC code and class code match and adds the corresponding lessons.
 *
 * @param l1: A list of UC-lesson pairs to add to the UC.
 *
 * Time Complexity: O(n), linear time complexity where 'n' is the number of UC-lesson pairs in the input list.
 */
void UC::addClassLessons(const std::list<std::pair<UC, Lesson>>& l1){
    for (const auto& c : l1){
        if (c.first.ucCode_ == ucCode_ && c.first.classCode_ == classCode_){
            addLesson(c.second);
        }
    }
}

/**
 * @brief Print the list of lessons for the UC.
 *
 * This function prints the list of lessons for the UC, including details such as weekday, start time, duration, and lesson type.
 *
 * @param None
 *
 * Time Complexity: O(n), linear time complexity where 'n' is the number of lessons in the list.
 */
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

/**
 * @brief Convert a floating-point hour value to a string representation.
 *
 * This function converts a floating-point hour value to a string representation in the format "HH:MM".
 *
 * @param hour: The hour value to be converted.
 *
 * @return A string representation of the hour in "HH:MM" format.
 *
 * Time Complexity: O(1), constant time to perform the conversion.
 */
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

/**
 * @brief Get the schedule of lessons for the UC based on a list of UC-lesson pairs.
 *
 * This function creates a schedule of lessons for the UC based on a list of UC-lesson pairs. Lessons are added to the schedule if they match the UC code.
 *
 * @param l1: A list of UC-lesson pairs used to create the schedule.
 * @return A Schedule object containing the lessons scheduled for the UC.
 *
 * Time Complexity: O(n), linear time complexity where 'n' is the number of UC-lesson pairs in the input list.
 */
Schedule UC::getSchedule(const std::list<std::pair<UC, Lesson>>& l1) {
    Schedule s = Schedule();
    for (const auto& c : l1){
        if (c.first.ucCode_ == ucCode_){
            s.addLesson(c.first,c.second);
        }
    }
    return s;
}
