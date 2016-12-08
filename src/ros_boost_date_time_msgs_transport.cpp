#include <boost_date_time_msgs/boost/Ptime.h>
#include <boost_date_time_msgs/boost/TimeDuration.h>

#include <rtt_roscomm/rtt_rostopic_ros_msg_transporter.hpp>
#include <rtt_roscomm/rtt_rostopic.h>
#include <rtt/types/TransportPlugin.hpp>
#include <rtt/types/TypekitPlugin.hpp>

namespace rtt_roscomm {
  using namespace RTT;
    struct ROSboost_date_time_msgsPlugin
      : public types::TransportPlugin
    {
      bool registerTransport(std::string name, types::TypeInfo* ti)
      {
          if(name == "boost.posix_time.ptime") { return ti->addProtocol(ORO_ROS_PROTOCOL_ID,new RosMsgTransporter<boost::posix_time::ptime>());} else
          if(name == "boost.posix_time.time_duration") { return ti->addProtocol(ORO_ROS_PROTOCOL_ID,new RosMsgTransporter<boost::posix_time::time_duration>());} else
          { }
          return false;
      }
      
      std::string getTransportName() const {
          return "ros";
      }
      
      std::string getTypekitName() const {
          return std::string("ros-")+"boost_date_time_msgs";
      }
      std::string getName() const {
          return std::string("rtt-ros-") + "boost_date_time_msgs" + "-transport";
      }

    };
}

ORO_TYPEKIT_PLUGIN( rtt_roscomm::ROSboost_date_time_msgsPlugin )
