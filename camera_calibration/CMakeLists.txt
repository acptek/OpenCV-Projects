cmake_minimum_required(VERSION 3.10)
project(camera_calibration)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

add_executable(image_capture image_capture.cpp)
target_link_libraries(image_capture ${OpenCV_LIBS})

add_executable(image_creator image_creator.cpp)
target_link_libraries(image_creator ${OpenCV_LIBS})

add_executable(imagelist_creator imagelist_creator.cpp)
target_link_libraries(imagelist_creator ${OpenCV_LIBS})

add_executable(calibration calibration.cpp)
target_link_libraries(calibration ${OpenCV_LIBS})

add_executable(camera_calibration main.cpp)