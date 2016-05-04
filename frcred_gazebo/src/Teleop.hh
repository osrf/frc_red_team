#include <string>

#include <gazebo/common/Plugin.hh>
#include <gazebo/gui/GuiPlugin.hh>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829
# include <gazebo/transport/transport.hh>
# include <gazebo/gui/gui.hh>
#endif

namespace gazebo
{
  class GAZEBO_VISIBLE Teleop : public GUIPlugin
  {
    Q_OBJECT

    /// \brief Constructor
    public: Teleop();

    /// \brief Destructor
    public: virtual ~Teleop();

    private slots: void OnFront();
    private slots: void OnBack();
    private slots: void OnRight();
    private slots: void OnLeft();

    private slots: void OnLiftUp();
    private slots: void OnLiftDown();
    private slots: void OnScoopUp();
    private slots: void OnScoopDown();

    /// \brief Node used to establish communication with gzserver.
    private: transport::NodePtr node;

    private: transport::PublisherPtr diffDrivePub;
    private: transport::PublisherPtr liftUpPub;
    private: transport::PublisherPtr liftDownPub;
    private: transport::PublisherPtr scoopUpPub;
    private: transport::PublisherPtr scoopDownPub;
  };
}
