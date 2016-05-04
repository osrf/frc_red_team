Installation
============
 * sudo apt-get install libignition-msgs-dev python-catkin-tools python-wstool python-rosinstall-generator ros-jade-gazebo7-ros-pkgs
 * (temporary workaround) Install ignition-transport from default
 * . /opt/ros/jade/setup.bash
 * mkdir -p ${HOME}/frc\_ws/src
 * cd ${HOME}/frc\_ws/src
 * wget https://bitbucket.org/osrf/frc\_red\_team/raw/default/frcred.rosinstall -O ./.rosinstall
 * wstool update
 * cd ${HOME}/frc\_ws
 * catkin init

Build
=====
 * catkin build --make-args install
 * source install/setup.sh
 * source install/share/frc2016\_competition/setup.sh

Remember to run `catkin build` when changing any code, including launch files

Fun!
====
 * diffy launch: roslaunch `frcred_gazebo diffy_frc2016_scenario.launch`

Subdirectories
==============

 * **frcred\_gazebo** ROS package for simulation
 * **gazebo\_models** gazebo models and plugins

[optional] rosdep gazebo7 remap
===============================

Don't need to use it unless you are using ROS packages that are resolving the
gazebo key to gazebo5.

 * sudo rosdep init
 * sudo wget https://raw.githubusercontent.com/osrf/osrf-rosdep/master/gazebo7/00-gazebo7.list -O /etc/ros/rosdep/sources.list.d/00-gazebo7.list
 * rosdep update
