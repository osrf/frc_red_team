cmake_minimum_required(VERSION 2.8.3)
project(frcred_gazebo)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)

catkin_package(
    LIBRARIES
      teleop_gazebo_plugin
      launcher_gazebo_plugin
)

install(
  DIRECTORY
   launch
   worlds
   models
  DESTINATION
   ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

add_subdirectory(src)
