#include <iostream>
#include "JoyToJoints.hh"

using namespace gazebo;

GZ_REGISTER_MODEL_PLUGIN(JoyToJoints)

/////////////////////////////////////////////////
JoyToJoints::JoyToJoints()
{
}

/////////////////////////////////////////////////
JoyToJoints::~JoyToJoints()
{
  this->alive = false;
  this->callbackQueue.clear();
  this->callbackQueue.disable();
  this->gazeboRos->node()->shutdown();
  this->callbackQueueThread.join();
}

/////////////////////////////////////////////////
void JoyToJoints::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
  this->model = _model;
  auto controller = this->model->GetJointController();

  // Load params from SDF
  if (_sdf->HasElement("map"))
  {
    auto mapElem = _sdf->GetElement("map");
    while (mapElem)
    {
      auto jointName = mapElem->Get<std::string>("joint");
      auto joint = this->model->GetJoint(jointName);
      if (!joint)
      {
        gzwarn << "Can't find joint [" << jointName << "]" << std::endl;
      }
      else
      {
        ButtonInfo info;
        info.button = mapElem->Get<int>("button");
        info.joint = joint;
        info.scale = mapElem->Get<double>("scale");
        info.type = mapElem->Get<std::string>("type");

        double kp = mapElem->Get<double>("kp");
        double ki = mapElem->Get<double>("ki");
        double kd = mapElem->Get<double>("kd");

        common::PID pid(kp, ki, kd);
        if (info.type == "position")
          controller->SetPositionPID(info.joint->GetScopedName(), pid);
        else if (info.type == "velocity")
          controller->SetVelocityPID(info.joint->GetScopedName(), pid);

        this->buttons.push_back(info);
      }

      mapElem = mapElem->GetNextElement("map");
    }
  }

  // ROS transport
  this->gazeboRos = GazeboRosPtr(new GazeboRos(_model, _sdf, "JoyToJoint"));
  this->gazeboRos->isInitialized();

  // TODO: ugly ugly hack. look into the problem with ns later
  auto subOpts = ros::SubscribeOptions::create<sensor_msgs::Joy>("/red_team/robynder_robot/joy", 1,
              boost::bind(&JoyToJoints::OnJoy, this, _1),
              ros::VoidPtr(), &this->callbackQueue);

  this->joySub = this->gazeboRos->node()->subscribe(subOpts);

  this->callbackQueueThread =
      std::thread(std::bind(&JoyToJoints::QueueThread, this));

  this->alive = true;
}

/////////////////////////////////////////////////
void JoyToJoints::OnJoy(const sensor_msgs::Joy::ConstPtr &_msg)
{
  for (auto &button : this->buttons)
  {
    bool buttonPressed = _msg->buttons[button.button];
    if (!buttonPressed)
      continue;

    auto controller = this->model->GetJointController();

    if (button.type == "position")
    {
      auto currPos = button.joint->GetAngle(0).Radian();
      controller->SetPositionTarget(button.joint->GetScopedName(),
          currPos + button.scale);
    }
    else if (button.type == "velocity")
    {
      controller->SetVelocityTarget(button.joint->GetScopedName(),
          button.scale);
    }
    else if (button.type == "force")
    {
      button.joint->SetForce(0, button.scale);
    }
  }
}

/////////////////////////////////////////////////
void JoyToJoints::QueueThread()
{
  static const double timeout = 0.01;

  while (this->alive && this->gazeboRos->node()->ok())
  {
    this->callbackQueue.callAvailable(ros::WallDuration(timeout));
  }
}
