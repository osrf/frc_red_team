#include <iostream>
#include "Launcher.hh"

using namespace gazebo;

GZ_REGISTER_MODEL_PLUGIN(Launcher)

/////////////////////////////////////////////////
Launcher::Launcher()
{
}

/////////////////////////////////////////////////
void Launcher::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
  this->model = _model;

  // Joints
  this->liftJoint1 = this->model->GetJoint("rev_A_0_left");
  this->liftJoint2 = this->model->GetJoint("rev_A_0_right");
  this->scoopJoint = this->model->GetJoint("scoop");

  // Transport
  this->node = transport::NodePtr(new transport::Node());
  this->node->Init();

  this->upSub =
    this->node->Subscribe("~/Robordion/lift_up", &Launcher::OnUp, this);
  this->downSub =
    this->node->Subscribe("~/Robordion/lift_down", &Launcher::OnDown, this);
  this->scoopDownSub =
    this->node->Subscribe("~/Robordion/scoop_down", &Launcher::OnScoopDown, this);
  this->scoopUpSub =
    this->node->Subscribe("~/Robordion/scoop_up", &Launcher::OnScoopUp, this);
}

/////////////////////////////////////////////////
void Launcher::OnUp(ConstIntPtr &/*_msg*/)
{
  this->liftJoint1->SetForce(0, 500);
  this->liftJoint2->SetForce(0, 500);
}

/////////////////////////////////////////////////
void Launcher::OnDown(ConstIntPtr &/*_msg*/)
{
  this->liftJoint1->SetForce(0, -500);
  this->liftJoint2->SetForce(0, -500);
}

/////////////////////////////////////////////////
void Launcher::OnScoopDown(ConstIntPtr &/*_msg*/)
{
  this->scoopJoint->SetVelocity(0, -1);
}

/////////////////////////////////////////////////
void Launcher::OnScoopUp(ConstIntPtr &/*_msg*/)
{
  this->scoopJoint->SetVelocity(0, 1);
}
