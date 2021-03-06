cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(Protobuf REQUIRED)
find_package(gazebo REQUIRED)

include_directories(SYSTEM ${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

add_library(joy_to_joints_gazebo_plugin SHARED JoyToJoints.cc)
target_link_libraries(joy_to_joints_gazebo_plugin ${GAZEBO_LIBRARIES})

add_library(joy_to_joints_gazebo_plugin_canon SHARED JoyToJointsCanon.cc)
target_link_libraries(joy_to_joints_gazebo_plugin_canon ${GAZEBO_LIBRARIES})

add_library(joy_to_joints_gazebo_plugin_loader SHARED JoyToJointsLoader.cc)
target_link_libraries(joy_to_joints_gazebo_plugin_canon ${GAZEBO_LIBRARIES})


install(
  TARGETS
    joy_to_joints_gazebo_plugin
    joy_to_joints_gazebo_plugin_canon
    joy_to_joints_gazebo_plugin_loader
  LIBRARY DESTINATION
    ${CATKIN_PACKAGE_LIB_DESTINATION}
)
