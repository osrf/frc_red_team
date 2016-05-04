#include "gazebo/common/Plugin.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/transport/transport.hh"

namespace gazebo
{
  /// \brief A plugin that simulates buoyancy of an object immersed in fluid.
  class GAZEBO_VISIBLE Launcher : public ModelPlugin
  {
    /// \brief Constructor.
    public: Launcher();

    /// \brief Read the model SDF to compute volume and center of volume for
    /// each link, and store those properties in volPropsMap.
    public: virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);

    private: void OnUp(ConstIntPtr &_msg);
    private: void OnDown(ConstIntPtr &_msg);
    private: void OnScoopDown(ConstIntPtr &_msg);
    private: void OnScoopUp(ConstIntPtr &_msg);

    /// \brief Pointer to model containing the plugin.
    private: physics::ModelPtr model;
    private: physics::JointPtr liftJoint1;
    private: physics::JointPtr liftJoint2;
    private: physics::JointPtr scoopJoint;

    /// \brief Node used to establish communication with gzserver.
    private: transport::NodePtr node;
    private: transport::SubscriberPtr upSub;
    private: transport::SubscriberPtr downSub;
    private: transport::SubscriberPtr scoopDownSub;
    private: transport::SubscriberPtr scoopUpSub;
  };
}
