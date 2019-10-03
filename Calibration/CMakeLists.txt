cmake_minimum_required(VERSION 3.14)
project(Calibration)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

add_executable(Create createChess.cpp)
target_link_libraries(Create ${OpenCV_LIBS})


add_executable(Calibration calibration.cpp)
target_link_libraries(Calibration ${OpenCV_LIBS})

add_executable(Main main.cpp)
target_link_libraries(Main ${OpenCV_LIBS})