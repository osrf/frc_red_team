Installation
============
 * sudo apt-get install ros-jade-joy libignition-msgs-dev python-catkin-tools python-wstool python-rosinstall-generator ros-jade-gazebo7-ros-pkgs
 * (temporary workaround) Install ignition-transport from default
 * . /opt/ros/jade/setup.bash
 * mkdir -p ${HOME}/frc\_ws/src
 * cd ${HOME}/frc\_ws/src
 * wget https://bitbucket.org/osrf/frc\_red\_team/raw/default/frcred.rosinstall -O ./.rosinstall
 * wstool update
 * cd ${HOME}/frc\_ws
 * catkin init

Joystick setup
==============

http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick

Build
=====
 * catkin build --make-args install
 * source install/setup.sh
 * source install/share/frc2016\_competition/setup.sh
 * source src/frc_red_team/texture_setup.bash

Remember to run `catkin build` when changing any code, including launch files

Fun!
====
 * contest server: `roslaunch frcred_gazebo contest.launch`
 * laptop operating robordion: `roslaunch frcred_gazebo operator_robordion.launch`
 * laptop operating launcher: `roslaunch frcred_gazebo operator_launcher.launch`
 * laptop operating loader: `roslaunch frcred_gazebo operator_loader.launch`

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
