cmake_minimum_required(VERSION 3.26)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project main.cpp
        Classes/Lesson.cpp
        Classes/Lesson.h
        Classes/UC.cpp
        Classes/UC.h
        Classes/Schedule.cpp
        Classes/Schedule.h
        Classes/Student.cpp
        Classes/Student.h
        Classes/Data.cpp
        Classes/Data.h
)
