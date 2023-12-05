// Generated by gencpp from file ros_can_interface/master_acknowledgSignal.msg
// DO NOT EDIT!


#ifndef ROS_CAN_INTERFACE_MESSAGE_MASTER_ACKNOWLEDGSIGNAL_H
#define ROS_CAN_INTERFACE_MESSAGE_MASTER_ACKNOWLEDGSIGNAL_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ros_can_interface
{
template <class ContainerAllocator>
struct master_acknowledgSignal_
{
  typedef master_acknowledgSignal_<ContainerAllocator> Type;

  master_acknowledgSignal_()
    : master_acknowledgeSignal(false)  {
    }
  master_acknowledgSignal_(const ContainerAllocator& _alloc)
    : master_acknowledgeSignal(false)  {
  (void)_alloc;
    }



   typedef uint8_t _master_acknowledgeSignal_type;
  _master_acknowledgeSignal_type master_acknowledgeSignal;





  typedef boost::shared_ptr< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> const> ConstPtr;

}; // struct master_acknowledgSignal_

typedef ::ros_can_interface::master_acknowledgSignal_<std::allocator<void> > master_acknowledgSignal;

typedef boost::shared_ptr< ::ros_can_interface::master_acknowledgSignal > master_acknowledgSignalPtr;
typedef boost::shared_ptr< ::ros_can_interface::master_acknowledgSignal const> master_acknowledgSignalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator1> & lhs, const ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator2> & rhs)
{
  return lhs.master_acknowledgeSignal == rhs.master_acknowledgeSignal;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator1> & lhs, const ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace ros_can_interface

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db74e876059988b41de2c46733c73690";
  }

  static const char* value(const ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdb74e876059988b4ULL;
  static const uint64_t static_value2 = 0x1de2c46733c73690ULL;
};

template<class ContainerAllocator>
struct DataType< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ros_can_interface/master_acknowledgSignal";
  }

  static const char* value(const ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool master_acknowledgeSignal\n"
;
  }

  static const char* value(const ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.master_acknowledgeSignal);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct master_acknowledgSignal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ros_can_interface::master_acknowledgSignal_<ContainerAllocator>& v)
  {
    s << indent << "master_acknowledgeSignal: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.master_acknowledgeSignal);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROS_CAN_INTERFACE_MESSAGE_MASTER_ACKNOWLEDGSIGNAL_H
