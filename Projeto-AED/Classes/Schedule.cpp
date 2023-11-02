#include "Schedule.h"
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

/**
 * @brief Default constructor for the Schedule class.
 *
 * Time Complexity: O(1), constant time for object initialization.
 */
Schedule::Schedule(){
}

/**
* @brief Constructor for the Schedule class that initializes the schedule vector.
*
* @param schedule Vector of pairs (UC, Lesson) representing the class schedule.
*
* Time Complexity: O(n), where 'n' is the number of elements in the input vector.
*/
Schedule::Schedule(vector<pair<UC,Lesson>> schedule) : schedule_(schedule) {
}

/**
 * @brief Get the class schedule vector.
 *
 * @return A vector of pairs (UC, Lesson) representing the class schedule.
 *
 * Time Complexity: O(1)
 */
vector<pair<UC,Lesson>> Schedule::getSchedule() {
    return schedule_;
}

/**
 * @brief Set the class schedule vector.
 *
 * @detail This function replaces the current class schedule with a new one provided as an argument.
 *
 * @param schedule Vector of pairs (UC, Lesson) representing the class schedule.
 *
 * Time Complexity: O(n), where 'n' is the number of elements in the input vector.
 */
void Schedule::setSchedule(vector<pair<UC,Lesson>> schedule) {
    schedule_=schedule;
}

/**
 * @brief Add a Lesson to the schedule of a UC.
 *
 * @detail This function adds a new lesson to the class schedule by creating a pair of UC and Lesson and pushing it
 * to the schedule vector.
 *
 * @param uc UC object representing the course.
 * @param lesson Lesson object representing the class.
 *
 * Time Complexity: O(1) as it simply adds an element to the end of the vector.
 */
void Schedule::addLesson(const UC& uc,const Lesson& lesson) {
    pair<UC,Lesson> p = {uc, lesson};
    schedule_.push_back(p);
}

/**
 * @brief Comparison function used to sort classes by weekday and start time.
 *
 * @detail This function is used to sort the vector of classes.
 *
 * @param a First pair (UC, Lesson) to be compared.
 * @param b Second pair (UC, Lesson) to be compared.
 * @return true if class 'a' occurs before class 'b', false otherwise.
 *
 * Time Complexity: O(n log n), where 'n' is the number of classes.
 */
struct compareLessons {
    bool operator()(const pair<UC, Lesson> &a, const pair<UC, Lesson> &b) {
        if (a.second.getWeekday() < b.second.getWeekday()) {
            return true;
        }
        else if (a.second.getWeekday() > b.second.getWeekday()) {
            return false;
        }
        else return (a.second.getStartHour() < b.second.getStartHour());
    }
};

/**
 * @brief Print the class schedule in a tabular format.
 *
 * @detail This function prints the class schedule, organized by weekday, in a tabular format with columns for weekday,
 * UC (University Course) code and name, class code, class time with duration, and the type of the class. It sorts the
 * schedule based on weekday and start hour before printing.
 *
 * Time Complexity: O(n log n), where 'n' is the number of lessons in the schedule, due to the sorting operation.
 */
void Schedule::printSchedule() {

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

    map<int, string> NumToWeekday = {
            {1, "Monday"},
            {2, "Tuesday"},
            {3, "Wednesday"},
            {4, "Thursday"},
            {5, "Friday"}
    };

    sort(schedule_.begin(), schedule_.end(), compareLessons());

    cout << "--------------------------------------------------------------------" << endl;
    cout << "Weekday | UC Code (Name) (Class Code) | Class Time (Duration) | Type" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    for (const auto &p : schedule_) {
        UC uc = p.first;
        Lesson l = p.second;
        cout << NumToWeekday[l.getWeekday()] << " | ";
        cout << uc.getUCCode() <<" (" << UcCodeToName[uc.getUCCode()] << ")" << " (" << uc.getClassCode() << ") | ";
        cout << toTime(l.getStartHour()) << " hours";
        if (l.getDuration() == 1.0){
            cout << " -> " << toTime(l.getStartHour() + l.getDuration()) << " hours " << "(" << toTime(l.getDuration()) << " hour" << ")"  "| " << l.getType() << endl;
        }
        else{
            cout << " -> " << toTime(l.getStartHour() + l.getDuration()) << " hours " << "(" << toTime(l.getDuration()) << " hours" << ")"  "| " << l.getType() << endl;
        }
    }

    cout << "--------------------------------------------------------------------" << endl;
}

/**
 * @brief Convert a floating-point hour value to a formatted string (hh:mm).
 *
 * @detail This function takes a floating-point hour value, such as 9.5 (9:30), and converts it to a formatted time string
 * in the "hh:mm" format. It ensures that minutes are zero-padded if less than 10.
 *
 * @param hour The floating-point hour value.
 * @return A string in the "hh:mm" format.
 *
 * Time Complexity: O(1) as it performs a fixed number of operations.
 */
std::string Schedule::toTime(float hour) {
    int hrs = (int) hour;
    int mins = (int) ((hour-hrs)*60);
    if (mins > 10){
        return to_string(hrs) + ":" + to_string(mins);
    }
    else{
        return to_string(hrs) + ":" + "0" + to_string(mins);
    }
}





