/* Pan/tilt camera teleop plugin
 * Hotkeys configurable (?)
 * Defaults:
 * translate in Z:
 * -z: i
 * +z: k
 * pan (rotate about z axis):
 * -p: j
 * +p: l
 * tilt (rotate about x axis):
 * -t: u (or maybe I)
 * +t: o (or maybe K)
 */

#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>

#include <gazebo_plugins/gazebo_ros_utils.h>

// ROS
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>

typedef struct {
  double z_translate = 0;
  double pan = 0;
  double tilt = 0;
} PanTiltTranslate;

namespace gazebo
{
  class CameraTeleopPlugin : public ModelPlugin
  {
    // ROS listeners:
    // subscribe to twist message "camera_pan_tilt_teleop"
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
    {
      ROS_INFO("Loading Gazebo model");
      joint_controller_ = _parent->GetJointController();
      gazebo::common::PID shaft_pid(700, 0, 100);
      gazebo::common::PID camera_pid(10, 0, 0);
      shaft_joint_name_ = _parent->GetJoint("shaft_joint")->GetScopedName();
      camera_joint_name_ = _parent->GetJoint("camera_joint")->GetScopedName();

      joint_controller_->AddJoint(_parent->GetJoint("shaft_joint"));
      joint_controller_->AddJoint(_parent->GetJoint("camera_joint"));

      joint_controller_->SetPositionPID(shaft_joint_name_, shaft_pid);
      joint_controller_->SetPositionPID(camera_joint_name_, camera_pid);

      this->gazebo_ros_ = GazeboRosPtr(new GazeboRos(_parent, _sdf, "CameraTeleop"));

      // TODO Namespacing
      cam_teleop_sub_ = gazebo_ros_->node()->subscribe("/camera_pan_tilt/cmd_vel", 1000, &CameraTeleopPlugin::cmdCallback, this);

      // Store the pointer to the model
      this->model = _parent;
    }

    void cmdCallback(const geometry_msgs::Pose::ConstPtr & cmd_msg) {
      ROS_INFO("Setting joint positions to %f", cmd_msg->position.z);
      // Position control: hold the command
      // we are abusing the Twist command quite a bit here
      //joint_controller_->SetJointPosition(shaft_joint_name_, cmd_msg->position.z);
      joint_controller_->SetPositionTarget(shaft_joint_name_, cmd_msg->position.z);
      //joint_controller_->("shaft_joint", cmd_msg->position.z);

      // ohhhh boy
      auto ros_q = cmd_msg->orientation;
      gazebo::math::Vector3 euler_angles = gazebo::math::Quaternion(ros_q.w, ros_q.x, ros_q.y, ros_q.z).GetAsEuler();
      command.pan = euler_angles[2];
      command.tilt = euler_angles[0];

      //command.pan = cmd_msg->angular.z;
      //command.tilt = cmd_msg->angular.x;

      //joint_controller_->SetJointPosition(camera_joint_name_, command.pan);
      // TODO Fix the model for tilt
    }

    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;

    PanTiltTranslate command;
    ros::Subscriber cam_teleop_sub_;
    GazeboRosPtr gazebo_ros_;
    std::string shaft_joint_name_;
    std::string camera_joint_name_;

    gazebo::physics::JointControllerPtr joint_controller_;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(CameraTeleopPlugin)
}
