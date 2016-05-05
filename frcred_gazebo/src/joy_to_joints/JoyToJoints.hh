#include <thread>
#include <gazebo_plugins/gazebo_ros_utils.h>

#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <sensor_msgs/Joy.h>

#include "gazebo/common/Plugin.hh"

namespace gazebo
{
  struct ButtonInfo
  {
    int button;
    physics::JointPtr joint;
    double scale;
    std::string type;
  };

  /// \brief A plugin that simulates buoyancy of an object immersed in fluid.
  class GAZEBO_VISIBLE JoyToJoints : public ModelPlugin
  {
    /// \brief Constructor.
    public: JoyToJoints();
    public: ~JoyToJoints();

    /// \brief Read the model SDF to compute volume and center of volume for
    /// each link, and store those properties in volPropsMap.
    public: virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);

    private: void OnJoy(const sensor_msgs::Joy::ConstPtr &_msg);

    private: GazeboRosPtr gazeboRos;
    private: ros::Subscriber joySub;

    private: ros::CallbackQueue callbackQueue;
    private: std::thread callbackQueueThread;
    private: void QueueThread();

    private: std::vector<ButtonInfo> buttons;
    private: physics::ModelPtr model;
    private: bool alive;
  };
}
