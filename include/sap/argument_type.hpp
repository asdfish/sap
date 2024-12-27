#ifndef SAP_ARGUMENT_TYPE_HPP
#define SAP_ARGUMENT_TYPE_HPP

#include <cstring>

namespace sap {

enum ArgumentType {
  ARGUMENT_TYPE_FLAG_LONG,
  ARGUMENT_TYPE_FLAG_SHORT,
  ARGUMENT_TYPE_ERROR_NULL_ARGUMENT,
  ARGUMENT_TYPE_SEPARATOR,
  ARGUMENT_TYPE_VALUE,
};

constexpr ArgumentType get_argument_type(const char* argument) {
  if(!argument)
    return ARGUMENT_TYPE_ERROR_NULL_ARGUMENT;

  if(argument[0] != '-')
    return ARGUMENT_TYPE_VALUE;

  std::size_t argument_length = strlen(argument);
  if(argument_length == 1)
    return ARGUMENT_TYPE_VALUE;

  if(argument_length == 2 && strncmp(argument, "--", 2) == 0)
    return ARGUMENT_TYPE_SEPARATOR;

  if(argument[1] != '-')
    return ARGUMENT_TYPE_FLAG_SHORT;

  return ARGUMENT_TYPE_FLAG_LONG;
}

constexpr const char* get_past_argument_flag(const char* argument, ArgumentType argument_type) {
  switch(argument_type) {
    case ARGUMENT_TYPE_FLAG_LONG:
      return argument + 2;
    case ARGUMENT_TYPE_FLAG_SHORT:
      return argument + 1;
    default:
      return argument;
  }
}

};

#endif // SAP_ARGUMENT_TYPE_HPP
