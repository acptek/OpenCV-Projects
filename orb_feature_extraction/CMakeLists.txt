cmake_minimum_required(VERSION 3.10)
project(Orb)
project(HandOrb)
project(SelfOrb)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

add_executable(Orb main.cpp)
add_executable(HandOrb handorb.cpp)
add_executable(SelfOrb orb_self.cpp)

target_link_libraries(Orb ${OpenCV_LIBS})
target_link_libraries(HandOrb ${OpenCV_LIBS})
target_link_libraries(SelfOrb ${OpenCV_LIBS})