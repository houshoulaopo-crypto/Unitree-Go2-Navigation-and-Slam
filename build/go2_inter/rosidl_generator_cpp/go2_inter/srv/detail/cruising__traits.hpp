// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from go2_inter:srv/Cruising.idl
// generated code does not contain a copyright notice

#ifndef GO2_INTER__SRV__DETAIL__CRUISING__TRAITS_HPP_
#define GO2_INTER__SRV__DETAIL__CRUISING__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "go2_inter/srv/detail/cruising__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace go2_inter
{

namespace srv
{

inline void to_flow_style_yaml(
  const Cruising_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: flag
  {
    out << "flag: ";
    rosidl_generator_traits::value_to_yaml(msg.flag, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Cruising_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "flag: ";
    rosidl_generator_traits::value_to_yaml(msg.flag, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Cruising_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace go2_inter

namespace rosidl_generator_traits
{

[[deprecated("use go2_inter::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const go2_inter::srv::Cruising_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  go2_inter::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use go2_inter::srv::to_yaml() instead")]]
inline std::string to_yaml(const go2_inter::srv::Cruising_Request & msg)
{
  return go2_inter::srv::to_yaml(msg);
}

template<>
inline const char * data_type<go2_inter::srv::Cruising_Request>()
{
  return "go2_inter::srv::Cruising_Request";
}

template<>
inline const char * name<go2_inter::srv::Cruising_Request>()
{
  return "go2_inter/srv/Cruising_Request";
}

template<>
struct has_fixed_size<go2_inter::srv::Cruising_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<go2_inter::srv::Cruising_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<go2_inter::srv::Cruising_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'point'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace go2_inter
{

namespace srv
{

inline void to_flow_style_yaml(
  const Cruising_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: point
  {
    out << "point: ";
    to_flow_style_yaml(msg.point, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Cruising_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: point
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "point:\n";
    to_block_style_yaml(msg.point, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Cruising_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace go2_inter

namespace rosidl_generator_traits
{

[[deprecated("use go2_inter::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const go2_inter::srv::Cruising_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  go2_inter::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use go2_inter::srv::to_yaml() instead")]]
inline std::string to_yaml(const go2_inter::srv::Cruising_Response & msg)
{
  return go2_inter::srv::to_yaml(msg);
}

template<>
inline const char * data_type<go2_inter::srv::Cruising_Response>()
{
  return "go2_inter::srv::Cruising_Response";
}

template<>
inline const char * name<go2_inter::srv::Cruising_Response>()
{
  return "go2_inter/srv/Cruising_Response";
}

template<>
struct has_fixed_size<go2_inter::srv::Cruising_Response>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value> {};

template<>
struct has_bounded_size<go2_inter::srv::Cruising_Response>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value> {};

template<>
struct is_message<go2_inter::srv::Cruising_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<go2_inter::srv::Cruising>()
{
  return "go2_inter::srv::Cruising";
}

template<>
inline const char * name<go2_inter::srv::Cruising>()
{
  return "go2_inter/srv/Cruising";
}

template<>
struct has_fixed_size<go2_inter::srv::Cruising>
  : std::integral_constant<
    bool,
    has_fixed_size<go2_inter::srv::Cruising_Request>::value &&
    has_fixed_size<go2_inter::srv::Cruising_Response>::value
  >
{
};

template<>
struct has_bounded_size<go2_inter::srv::Cruising>
  : std::integral_constant<
    bool,
    has_bounded_size<go2_inter::srv::Cruising_Request>::value &&
    has_bounded_size<go2_inter::srv::Cruising_Response>::value
  >
{
};

template<>
struct is_service<go2_inter::srv::Cruising>
  : std::true_type
{
};

template<>
struct is_service_request<go2_inter::srv::Cruising_Request>
  : std::true_type
{
};

template<>
struct is_service_response<go2_inter::srv::Cruising_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // GO2_INTER__SRV__DETAIL__CRUISING__TRAITS_HPP_
