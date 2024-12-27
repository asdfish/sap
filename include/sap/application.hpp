#ifndef SAP_APPLICATION_HPP
#define SAP_APPLICATION_HPP

#include <cstdlib>
#include <cstring>

#include <sap/argument_contents.hpp>
#include <sap/argument_type.hpp>
#include <sap/flag.hpp>

namespace sap {

  enum ParsingError {
    PARSING_ERROR_FLAG_SHORT_NOT_FOUND = 0,
    PARSING_ERROR_FLAG_LONG_NOT_FOUND = 1,
    PARSING_ERROR_NULL_ARGUMENT = 2,
  };

  class Application {
    Flag* flags;
    std::size_t flags_length;
    void (*error_callback) (const char* offending_argument, ParsingError error, void* user_data);
    void* error_callback_user_data;
    void (*value_callback) (const char* value, void* user_data);
    void* value_callback_user_data;

    constexpr void call_error_callback(const char* offending_argument, ParsingError error) const {
      if(error_callback)
	error_callback(offending_argument, error, error_callback_user_data);
    }
    constexpr void call_value_callback(const char* value) const {
      if(value_callback)
	value_callback(value, value_callback_user_data);
    }
    constexpr bool flags_contains(char key, std::size_t* flag = nullptr) const {
      for(std::size_t i = 0; i < flags_length; i ++)
	if(this->flags[i].id_short == key) {
	  if(flag)
	    *flag = i;

	  return true;
	}

      return false;
    }
    constexpr bool flags_contains(const char* key, std::size_t* flag = nullptr) const {
      for(std::size_t i = 0; i < flags_length; i ++)
	if(std::strcmp(this->flags[i].id_long, key) == 0) {
	  if(flag)
	    *flag = i;
	  return true;
	}

      return false;
    }

  public:
    constexpr Application(
      Flag* i_flags,
      std::size_t i_flags_length,
      void (*i_error_callback) (const char* offending_argument, ParsingError error, void* user_data) = nullptr,
      void* i_error_callback_user_data = nullptr,
      void (*i_value_callback) (const char* value, void* user_data) = nullptr,
      void* i_value_callback_user_data = nullptr
    ):
      flags(i_flags),
      flags_length(i_flags_length),
      error_callback(i_error_callback),
      error_callback_user_data(i_error_callback_user_data),
      value_callback(i_value_callback),
      value_callback_user_data(i_value_callback_user_data) {}
    void parse(int argc, const char* argv[]) {
      bool passed_separator = false;

      for(std::size_t i = 1; i < (std::size_t) argc; i ++) {
	if(passed_separator) {
	  call_value_callback(argv[i]);
          continue;
        }

	switch(get_argument_type(argv[i])) {
        case ARGUMENT_TYPE_FLAG_LONG:
          {
            const char* flag_string = argv[i] + 2;
            std::size_t flag_index = 0;

            if(!flags_contains(flag_string, &flag_index))
              call_error_callback(argv[i], PARSING_ERROR_FLAG_LONG_NOT_FOUND);

            const Flag& flag = flags[flag_index];

            if(flag.take_argument) {
              std::size_t contents = 0;
              switch(get_argument_contents(flag_string, &contents)) {
              // impossible
              case ARGUMENT_CONTENTS_ERROR_NULL_ARGUMENT: ;
                break;
              case ARGUMENT_CONTENTS_NONE:
                i ++;
                if(i >= (std::size_t) argc)
                  call_error_callback(argv[i - 1], PARSING_ERROR_NULL_ARGUMENT);
                else
                  flag.call_argument_callback(argv[i]);
                break;
              case ARGUMENT_CONTENTS_VALID:
                flag.call_argument_callback(argv[i] + contents + 2);
                break;
              }
            } else
              flag.call_argument_callback(argv[i]);
          }
          break;
        case ARGUMENT_TYPE_FLAG_SHORT:
          {
            const char* flag_string = argv[i] + 1;
            std::size_t flag_string_length = strlen(flag_string);

            for(std::size_t j = 0; j < flag_string_length; j ++) {
              std::size_t flag_index = 0;
              if(!flags_contains(argv[i][j + 1], &flag_index)){
                call_error_callback(argv[i], PARSING_ERROR_FLAG_SHORT_NOT_FOUND);
                break;
              }

              const Flag& flag = flags[flag_index];

              if(flag.take_argument) {
                char next_char = argv[i][j + 2];
                if(next_char == '=')
                  flag.call_argument_callback(argv[i] + j + 3);
                else if (next_char == '\0') {
                  i ++;
                  if(i >= (std::size_t) argc) {
                    call_error_callback(argv[i - 1], PARSING_ERROR_NULL_ARGUMENT);
                    break;
                  }
                  flag.call_argument_callback(argv[i]);
                } else
                  flag.call_argument_callback(argv[i] + j + 2);
                break;
              } else
                flag.call_argument_callback(nullptr);
            }
          }
          break;
	case ARGUMENT_TYPE_ERROR_NULL_ARGUMENT:
	  call_error_callback(argv[i], PARSING_ERROR_NULL_ARGUMENT);
	  break;
	case ARGUMENT_TYPE_SEPARATOR:
	  passed_separator = true;
	  break;
	case ARGUMENT_TYPE_VALUE:
	  call_value_callback(argv[i]);
	  break;
	}

      }
    }
  };

};

#endif // SAP_APPLICATION_HPP
