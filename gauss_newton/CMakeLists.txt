cmake_minimum_required(VERSION 3.14)
project(gauss)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 REQUIRED)
include_directories(${Eigen_INCLUDE_DIRS})
find_package(OpenCV REQUIRED)

add_executable(gauss main.cpp)

target_link_libraries(gauss Eigen3::Eigen)
target_link_libraries(gauss ${OpenCV_LIBS})