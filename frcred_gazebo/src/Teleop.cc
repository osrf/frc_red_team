#include <sstream>
#include <gazebo/msgs/msgs.hh>
#include "Teleop.hh"

using namespace gazebo;

// Register this plugin with the simulator
GZ_REGISTER_GUI_PLUGIN(Teleop)

/////////////////////////////////////////////////
Teleop::Teleop()
  : GUIPlugin()
{
  // Set the frame background and foreground colors
  this->setStyleSheet(
      "QFrame { background-color : rgba(100, 100, 100, 255); color : white; }");

  // Front
  auto front = new QPushButton(tr("Front"));
  front->setShortcut(Qt::Key_Up);
  this->connect(front, SIGNAL(clicked()), this, SLOT(OnFront()));

  // Back
  auto back = new QPushButton(tr("Back"));
  back->setShortcut(Qt::Key_Down);
  this->connect(back, SIGNAL(clicked()), this, SLOT(OnBack()));

  // Right
  auto right = new QPushButton(tr("Right"));
  right->setShortcut(Qt::Key_Right);
  this->connect(right, SIGNAL(clicked()), this, SLOT(OnRight()));

  // Left
  auto left = new QPushButton(tr("Left"));
  left->setShortcut(Qt::Key_Left);
  this->connect(left, SIGNAL(clicked()), this, SLOT(OnLeft()));

  // Lift Up
  auto liftUp = new QPushButton(tr("Lift Up"));
  liftUp->setShortcut(tr("W"));
  this->connect(liftUp, SIGNAL(clicked()), this, SLOT(OnLiftUp()));

  // Lift Down
  auto liftDown = new QPushButton(tr("Lift Down"));
  liftDown->setShortcut(tr("S"));
  this->connect(liftDown, SIGNAL(clicked()), this, SLOT(OnLiftDown()));

  // Scoop Up
  auto scoopUp = new QPushButton(tr("Scoop Up"));
  scoopUp->setShortcut(tr("D"));
  this->connect(scoopUp, SIGNAL(clicked()), this, SLOT(OnScoopUp()));

  // Scoop Down
  auto scoopDown = new QPushButton(tr("Scoop Down"));
  scoopDown->setShortcut(tr("A"));
  this->connect(scoopDown, SIGNAL(clicked()), this, SLOT(OnScoopDown()));

  // Create the layout that sits inside the frame
  auto frameLayout = new QGridLayout();
  frameLayout->addWidget(front, 0, 1);
  frameLayout->addWidget(back, 1, 1);
  frameLayout->addWidget(right, 1, 0);
  frameLayout->addWidget(left, 1, 2);
  frameLayout->addWidget(liftUp, 0, 3);
  frameLayout->addWidget(liftDown, 1, 3);
  frameLayout->addWidget(scoopUp, 0, 4);
  frameLayout->addWidget(scoopDown, 1, 4);

  // Create the frame to hold all the widgets
  QFrame *mainFrame = new QFrame();
  mainFrame->setLayout(frameLayout);

  // Create the main layout
  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(mainFrame);

  // Remove margins to reduce space
  frameLayout->setContentsMargins(4, 4, 4, 4);
  mainLayout->setContentsMargins(0, 0, 0, 0);

  this->setLayout(mainLayout);

  // Position and resize this widget
  this->move(10, 10);
  this->resize(400, 100);

  // Create a node for transportation
  this->node = transport::NodePtr(new transport::Node());
  this->node->Init("default");
  this->diffDrivePub =
      this->node->Advertise<msgs::Pose>("~/Robordion/vel_cmd");

  this->liftUpPub = this->node->Advertise<msgs::Int>("~/Robordion/lift_up");
  this->liftDownPub = this->node->Advertise<msgs::Int>("~/Robordion/lift_down");
  this->scoopUpPub = this->node->Advertise<msgs::Int>("~/Robordion/scoop_up");
  this->scoopDownPub = this->node->Advertise<msgs::Int>("~/Robordion/scoop_down");
}

/////////////////////////////////////////////////
Teleop::~Teleop()
{
}

/////////////////////////////////////////////////
void Teleop::OnFront()
{
  ignition::math::Pose3d pose(-2, 0, 0, 0, 0, 0);

  msgs::Pose msg;
  msgs::Set(&msg, pose);

  this->diffDrivePub->Publish(msg);
}

/////////////////////////////////////////////////
void Teleop::OnBack()
{
  ignition::math::Pose3d pose(2, 0, 0, 0, 0, 0);

  msgs::Pose msg;
  msgs::Set(&msg, pose);

  this->diffDrivePub->Publish(msg);
}

/////////////////////////////////////////////////
void Teleop::OnRight()
{
  ignition::math::Pose3d pose(0, 0, 0, 0, 0, -2);

  msgs::Pose msg;
  msgs::Set(&msg, pose);

  this->diffDrivePub->Publish(msg);
}

/////////////////////////////////////////////////
void Teleop::OnLeft()
{
  ignition::math::Pose3d pose(0, 0, 0, 0, 0, 2);

  msgs::Pose msg;
  msgs::Set(&msg, pose);

  this->diffDrivePub->Publish(msg);
}

/////////////////////////////////////////////////
void Teleop::OnLiftUp()
{
  msgs::Int msg;
  msg.set_data(0);

  this->liftUpPub->Publish(msg);
}

/////////////////////////////////////////////////
void Teleop::OnLiftDown()
{
  msgs::Int msg;
  msg.set_data(0);

  this->liftDownPub->Publish(msg);
}

/////////////////////////////////////////////////
void Teleop::OnScoopUp()
{
  msgs::Int msg;
  msg.set_data(0);

  this->scoopUpPub->Publish(msg);
}

/////////////////////////////////////////////////
void Teleop::OnScoopDown()
{
  msgs::Int msg;
  msg.set_data(0);

  this->scoopDownPub->Publish(msg);
}


