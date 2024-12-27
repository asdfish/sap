#include <sap/flag.hpp>

#include <utility>

sap::Flag::Flag(
  std::string&& i_id_long,
  char i_id_short,
  bool i_take_argument,
  std::optional<std::function<void(std::optional<std::string>&&)>>&& i_argument_handler
):
  id_long(std::move(i_id_long)),
  id_short(i_id_short),
  take_argument(i_take_argument),
  argument_handler(std::move(i_argument_handler)) {
}
