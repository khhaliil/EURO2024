// Generated by gencpp from file path_planner/PathPlanResponse.msg
// DO NOT EDIT!


#ifndef PATH_PLANNER_MESSAGE_PATHPLANRESPONSE_H
#define PATH_PLANNER_MESSAGE_PATHPLANRESPONSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose2D.h>

namespace path_planner
{
template <class ContainerAllocator>
struct PathPlanResponse_
{
  typedef PathPlanResponse_<ContainerAllocator> Type;

  PathPlanResponse_()
    : new_path()  {
    }
  PathPlanResponse_(const ContainerAllocator& _alloc)
    : new_path(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::geometry_msgs::Pose2D_<ContainerAllocator> , typename std::allocator_traits<ContainerAllocator>::template rebind_alloc< ::geometry_msgs::Pose2D_<ContainerAllocator> >> _new_path_type;
  _new_path_type new_path;





  typedef boost::shared_ptr< ::path_planner::PathPlanResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::path_planner::PathPlanResponse_<ContainerAllocator> const> ConstPtr;

}; // struct PathPlanResponse_

typedef ::path_planner::PathPlanResponse_<std::allocator<void> > PathPlanResponse;

typedef boost::shared_ptr< ::path_planner::PathPlanResponse > PathPlanResponsePtr;
typedef boost::shared_ptr< ::path_planner::PathPlanResponse const> PathPlanResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::path_planner::PathPlanResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::path_planner::PathPlanResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::path_planner::PathPlanResponse_<ContainerAllocator1> & lhs, const ::path_planner::PathPlanResponse_<ContainerAllocator2> & rhs)
{
  return lhs.new_path == rhs.new_path;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::path_planner::PathPlanResponse_<ContainerAllocator1> & lhs, const ::path_planner::PathPlanResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace path_planner

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::path_planner::PathPlanResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::path_planner::PathPlanResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::path_planner::PathPlanResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::path_planner::PathPlanResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::path_planner::PathPlanResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::path_planner::PathPlanResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::path_planner::PathPlanResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "60d0cf4e7774342781ba2023adea4661";
  }

  static const char* value(const ::path_planner::PathPlanResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x60d0cf4e77743427ULL;
  static const uint64_t static_value2 = 0x81ba2023adea4661ULL;
};

template<class ContainerAllocator>
struct DataType< ::path_planner::PathPlanResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "path_planner/PathPlanResponse";
  }

  static const char* value(const ::path_planner::PathPlanResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::path_planner::PathPlanResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
"# Array of intermediate points for the new path\n"
"geometry_msgs/Pose2D[] new_path\n"
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

  static const char* value(const ::path_planner::PathPlanResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::path_planner::PathPlanResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.new_path);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PathPlanResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::path_planner::PathPlanResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::path_planner::PathPlanResponse_<ContainerAllocator>& v)
  {
    s << indent << "new_path[]" << std::endl;
    for (size_t i = 0; i < v.new_path.size(); ++i)
    {
      s << indent << "  new_path[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::Pose2D_<ContainerAllocator> >::stream(s, indent + "    ", v.new_path[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // PATH_PLANNER_MESSAGE_PATHPLANRESPONSE_H
