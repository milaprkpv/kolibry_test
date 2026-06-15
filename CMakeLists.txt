cmake_minimum_required(VERSION 3.16)


project(BinaryModifier)


set(CMAKE_CXX_STANDARD 17)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)



find_package(Qt6 REQUIRED COMPONENTS Widgets)



add_executable(BinaryModifier

main.cpp


mainwindow.cpp
mainwindow.h
mainwindow.ui


fileworker.cpp
fileworker.h


filescanner.cpp
filescanner.h


configmanager.cpp
configmanager.h


taskqueue.cpp
taskqueue.h


resumemanager.cpp
resumemanager.h

)



target_link_libraries(
BinaryModifier
Qt6::Widgets
)
