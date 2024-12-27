#ifndef SAP_ARGUMENT_CONTENTS_HPP
#define SAP_ARGUMENT_CONTENTS_HPP

#include <cstring>

namespace sap {

enum ArgumentContents {
  ARGUMENT_CONTENTS_ERROR_NULL_ARGUMENT,
  ARGUMENT_CONTENTS_NONE,
  ARGUMENT_CONTENTS_VALID,
};

constexpr ArgumentContents get_argument_contents(const char* argument, std::size_t* contents = nullptr) {
  if(!argument)
    return ARGUMENT_CONTENTS_ERROR_NULL_ARGUMENT;

  const char* equals_char = strstr(argument, "=");
  if(!equals_char)
    return ARGUMENT_CONTENTS_NONE;

  if(contents)
    *contents = equals_char + 1 - argument;
  return ARGUMENT_CONTENTS_VALID;
}

};

#endif // SAP_ARGUMENT_CONTENTS_HPP
