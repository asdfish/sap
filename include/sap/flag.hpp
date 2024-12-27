#ifndef FLAG_HPP
#define FLAG_HPP

#include <functional>
#include <optional>
#include <string>

namespace sap {

class Flag {
public:
  std::string id_long;
  char id_short;

  bool take_argument = false;
  std::optional<std::function<void(std::optional<std::string>&&)>> argument_handler = std::nullopt;

  Flag(
    std::string&& id_long,
    char id_short,
    bool take_argument = false,
    std::optional<std::function<void(std::optional<std::string>&&)>>&& argument_handler = std::nullopt
  );
};

};

#endif // FLAG_HPP
