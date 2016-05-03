Installation
============
 
 * sudo apt-get install python-catkin-tools python-wstool python-rosinstall-generator ros-jade-gazebo7-ros-pkgs
 * export ROS_DISTRO=jade
 * mkdir -p ${HOME}/frc_ws/src
 * cd ${HOME}/frc_ws/src
 * wget https://bitbucket.org/osrf/frc_red_team/raw/default/frcred.rosinstall > .rosinstall
 * wstool update
 * cd ${HOME}/frc_ws
 * catkin init
