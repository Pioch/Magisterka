cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(SetPose)

find_package(roscpp REQUIRED)
find_package(std_msgs REQUIRED)
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(${std_msgs_INCLUDE_DIRS})

find_package(gazebo REQUIRED)
include_directories(SYSTEM ${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

add_library(SetPose SHARED SetPose.cc dzialanie_grupowe.cpp f_alpha.cpp Init.cpp kinematyka.cpp liczenie_H.cpp liczenie_R.cpp liczenie_u.cpp odwrotnosc_g.cpp trajektoria.cpp liczenie_u_punkt.cpp omijanie_przeszkod.cpp)
target_link_libraries(SetPose ${GAZEBO_LIBRARIES})
