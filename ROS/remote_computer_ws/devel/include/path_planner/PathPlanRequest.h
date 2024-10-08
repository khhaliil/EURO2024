// Generated by gencpp from file path_planner/PathPlanRequest.msg
// DO NOT EDIT!


#ifndef PATH_PLANNER_MESSAGE_PATHPLANREQUEST_H
#define PATH_PLANNER_MESSAGE_PATHPLANREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Pose2D.h>

namespace path_planner
{
template <class ContainerAllocator>
struct PathPlanRequest_
{
  typedef PathPlanRequest_<ContainerAllocator> Type;

  PathPlanRequest_()
    : current_pose()
    , target_point()
    , obstacle()  {
    }
  PathPlanRequest_(const ContainerAllocator& _alloc)
    : current_pose(_alloc)
    , target_point(_alloc)
    , obstacle(_alloc)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::Pose2D_<ContainerAllocator>  _current_pose_type;
  _current_pose_type current_pose;

   typedef  ::geometry_msgs::Pose2D_<ContainerAllocator>  _target_point_type;
  _target_point_type target_point;

   typedef  ::geometry_msgs::Pose2D_<ContainerAllocator>  _obstacle_type;
  _obstacle_type obstacle;





  typedef boost::shared_ptr< ::path_planner::PathPlanRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::path_planner::PathPlanRequest_<ContainerAllocator> const> ConstPtr;

}; // struct PathPlanRequest_

typedef ::path_planner::PathPlanRequest_<std::allocator<void> > PathPlanRequest;

typedef boost::shared_ptr< ::path_planner::PathPlanRequest > PathPlanRequestPtr;
typedef boost::shared_ptr< ::path_planner::PathPlanRequest const> PathPlanRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::path_planner::PathPlanRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::path_planner::PathPlanRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::path_planner::PathPlanRequest_<ContainerAllocator1> & lhs, const ::path_planner::PathPlanRequest_<ContainerAllocator2> & rhs)
{
  return lhs.current_pose == rhs.current_pose &&
    lhs.target_point == rhs.target_point &&
    lhs.obstacle == rhs.obstacle;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::path_planner::PathPlanRequest_<ContainerAllocator1> & lhs, const ::path_planner::PathPlanRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace path_planner

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::path_planner::PathPlanRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::path_planner::PathPlanRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::path_planner::PathPlanRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::path_planner::PathPlanRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::path_planner::PathPlanRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::path_planner::PathPlanRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::path_planner::PathPlanRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ef3014d0c5a51d27ddb6567b5cbf3205";
  }

  static const char* value(const ::path_planner::PathPlanRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xef3014d0c5a51d27ULL;
  static const uint64_t static_value2 = 0xddb6567b5cbf3205ULL;
};

template<class ContainerAllocator>
struct DataType< ::path_planner::PathPlanRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "path_planner/PathPlanRequest";
  }

  static const char* value(const ::path_planner::PathPlanRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::path_planner::PathPlanRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Current robot position and angle\n"
"geometry_msgs/Pose2D current_pose\n"
"\n"
"# Target point\n"
"geometry_msgs/Pose2D target_point\n"
"\n"
"# Presented obstacle position\n"
"geometry_msgs/Pose2D obstacle\n"
"\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose2D\n"
"# Deprecated\n"
"# Please use the full 3D pose.\n"
"\n"
"# In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.\n"
"\n"
"# If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.\n"
"\n"
"\n"
"# This expresses a position and orientation on a 2D manifold.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 theta\n"
;
  }

  static const char* value(const ::path_planner::PathPlanRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::path_planner::PathPlanRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.current_pose);
      stream.next(m.target_point);
      stream.next(m.obstacle);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PathPlanRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::path_planner::PathPlanRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::path_planner::PathPlanRequest_<ContainerAllocator>& v)
  {
    s << indent << "current_pose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose2D_<ContainerAllocator> >::stream(s, indent + "  ", v.current_pose);
    s << indent << "target_point: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose2D_<ContainerAllocator> >::stream(s, indent + "  ", v.target_point);
    s << indent << "obstacle: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose2D_<ContainerAllocator> >::stream(s, indent + "  ", v.obstacle);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PATH_PLANNER_MESSAGE_PATHPLANREQUEST_H
