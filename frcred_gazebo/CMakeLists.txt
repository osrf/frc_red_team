  cmake_minimum_required(VERSION 2.8.3)
project(frcred_gazebo)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  gazebo_plugins
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(gazebo REQUIRED)

catkin_package(
  LIBRARIES
   teleop_gazebo_plugin
   launcher_gazebo_plugin
   camera_teleop_plugin
    CATKIN_DEPENDS
      gazebo_plugins
)

include_directories(include
  ${Boost_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS})

add_library(camera_teleop_plugin plugins/CameraTeleopPlugin.cc)
target_link_libraries(camera_teleop_plugin ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})

install(
  DIRECTORY
   launch
   worlds
   models
   scripts
  DESTINATION
   ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(
    TARGETS
   camera_teleop_plugin
 DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

install(
  PROGRAMS
    scripts/diffy_teleop.py
    scripts/teleop_pose_keyboard.py
 DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# Add folders to be run by python nosetests
add_subdirectory(src)
