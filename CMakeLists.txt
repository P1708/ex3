cmake_minimum_required(VERSION 3.23)
project(ex3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex3
        HealthPointsExampleTest.cpp
        QueueExampleTests.cpp
        TestMain.cpp
        TestUtils.h HealthPoints.cpp Queue.h)
