cmake_minimum_required(VERSION 3.1.0)
project(TrabajoProfesional)

include_directories(/usr/local/Cellar/cppunit/1.14.0/include)
link_directories(/usr/local/Cellar/cppunit/1.14.0/lib)

add_executable(tests TestMain.cpp
        TestCommunicator.h
        ../src/connection/communicator.h
        ../src/connection/communicator.cpp)

target_link_libraries(tests cppunit Qt5::Core Qt5::SerialPort)