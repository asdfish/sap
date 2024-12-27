#ifndef SAP_FLAG_HPP
#define SAP_FLAG_HPP

namespace sap {

class Flag {
public:
  const char* id_long;
  char id_short;

  bool take_argument;
  void (*argument_callback) (const char* argument, void* user_data);
  void* user_data;

  constexpr Flag(
    const char* i_id_long,
    char i_id_short,
    bool i_take_argument = false,
    void (*i_argument_callback) (const char* argument, void* user_data) = nullptr,
    void* i_user_data = nullptr
  ):
    id_long(i_id_long),
    id_short(i_id_short),
    take_argument(i_take_argument),
    argument_callback(i_argument_callback),
    user_data(i_user_data) {}
  constexpr void call_argument_callback(const char* argument) const {
    if(argument_callback)
      argument_callback(argument, user_data);
  }
};

};

#endif // SAP_FLAG_HPP
