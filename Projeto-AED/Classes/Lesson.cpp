#include "Lesson.h"


using namespace std;


/**
 * @brief Default constructor for Lesson.
 */
Lesson::Lesson(){};

/**
 * @brief Constructor for Lesson with specified attributes.
 *
 * @param weekday The day of the week when the lesson occurs.
 * @param duration The duration of the lesson in hours.
 * @param start_hour The starting hour of the lesson.
 * @param type The type of lesson (e.g., "Lecture" or "Lab").
 *
 * Time Complexity: O(1)
 */
Lesson::Lesson(int weekday, float duration, float start_hour, string type){
    weekday_=weekday;
    duration_ = duration;
    start_hour_ = start_hour;
    type_=type;
}

/**
 * @brief Get the weekday of the lesson.
 *
 * @return The day of the week when the lesson occurs.
 *
 * Time Complexity: O(1)
 */
int Lesson::getWeekday() const{
   return weekday_;
}

/**
 * @brief Get the duration of the lesson.
 *
 * @return The duration of the lesson in hours.
 *
 * Time Complexity: O(1)
 */
float Lesson::getDuration() const{
    return duration_;
}

/**
 * @brief Get the starting hour of the lesson.
 *
 * @return The starting hour of the lesson.
 *
 * Time Complexity: O(1)
 */
float Lesson::getStartHour() const{
    return start_hour_;
}

/**
 * @brief Get the type of the lesson.
 *
 * @return The type of the lesson (e.g., "T", "TP" or "Lab").
 *
 * Time Complexity: O(1)
 */
string Lesson::getType() const{
    return type_;
}

/**
 * @brief Check if this lesson coincides with another lesson.
 *
 * @detail This function checks if the current lesson coincides with another lesson by comparing their types, weekdays, and time slots.
 *
 * @param lesson The lesson to check for coincidence with.
 * @return True if the lessons coincide, false otherwise.
 *
 * Time Complexity: O(1)
 */
bool Lesson::coincideT(const Lesson& lesson) const{
    if (type_ == lesson.getType()) {
        if (weekday_ == lesson.getWeekday()) {
            if (start_hour_ + duration_ > getStartHour() && start_hour_ + duration_ <= getStartHour() + getDuration()){
                return true;
            }
            if(getStartHour() + getDuration() > start_hour_ && getStartHour() + getDuration() <= start_hour_ + duration_)
                return true;
        }
    }
    return false;
}

/**
 * @brief Compare two lessons for sorting purposes.
 *
 * @detail This operator compares two lessons for sorting purposes based on their weekdays and starting hours.
 *
 * @param a The lesson to compare with.
 * @return True if the current lesson is less than the provided lesson, false otherwise.
 *
 * Time Complexity: O(1)
 */
bool Lesson::operator<(Lesson a) const {
    if (weekday_ < a.getWeekday()){
        return true;
    }
    else if (weekday_ > a.getWeekday()){
        return false;
    }
    else return (start_hour_ < a.getStartHour());
}


