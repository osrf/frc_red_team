Installation
============
 * sudo apt-get install python-catkin-tools python-wstool python-rosinstall-generator ros-jade-gazebo7-ros-pkgs
 * (temporary workaround) Install ignition-transport from default
 * export ROS\_DISTRO=jade
 * mkdir -p ${HOME}/frc\_ws/src
 * cd ${HOME}/frc\_ws/src
 * wget https://bitbucket.org/osrf/frc\_red\_team/raw/default/frcred.rosinstall -O ./.rosinstall
 * wstool update
 * cd ${HOME}/frc\_ws

 * catkin init
 * catkin build
 * source install/setup.sh
 * source install/share/frc2016\_competition/setup.sh

Subdirectories
==============

 * **frcred\_gazebo** ROS package for simulation
 * **gazebo\_models** gazebo models and plugins

rosdep gazebo7 remap
====================

 * sudo rosdep init
 * sudo wget https://raw.githubusercontent.com/osrf/osrf-rosdep/master/gazebo7/00-gazebo7.list -O /etc/ros/rosdep/sources.list.d/00-gazebo7.list
 * rosdep update
