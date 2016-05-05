  cmake_minimum_required(VERSION 2.8.3)
project(frcred_gazebo)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
  COMPONENTS
  gazebo_plugins
)

catkin_package(
    LIBRARIES
      teleop_gazebo_plugin
      launcher_gazebo_plugin
    CATKIN_DEPENDS
      gazebo_plugins
)

include_directories(${catkin_LIBRARIES})

install(
  DIRECTORY
   launch
   worlds
   models
  DESTINATION
   ${CATKIN_PACKAGE_SHARE_DESTINATION}
)


install(
  PROGRAMS
    scripts/diffy_teleop.py
 DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# Add folders to be run by python nosetests
add_subdirectory(src)
