cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#find_package (Qt4)
find_package(Protobuf REQUIRED)
find_package(gazebo REQUIRED)

#include (${QT_USE_FILE})
#add_definitions(${QT_DEFINITIONS})

include_directories(SYSTEM ${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

#QT4_WRAP_CPP(headers_MOC Teleop.hh)

#add_library(teleop_gazebo_plugin SHARED ${headers_MOC}
#  Teleop.cc)
#target_link_libraries(teleop_gazebo_plugin ${GAZEBO_LIBRARIES}
#    ${OGRE_LIBRARIES}
#    ${OGRE-Terrain_LIBRARIES}
#    ${QT_LIBRARIES}
#    ${PROTOBUF_LIBRARIES})

#add_library(launcher_gazebo_plugin SHARED Launcher.cc)
#target_link_libraries(launcher_gazebo_plugin ${GAZEBO_LIBRARIES})

#install(
#  TARGETS
#    teleop_gazebo_plugin
#    launcher_gazebo_plugin
#  LIBRARY DESTINATION
#    ${CATKIN_PACKAGE_LIB_DESTINATION}
#)

add_subdirectory(joy_to_joints)
