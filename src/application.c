#include <sap/application.h>
#include <sap/flag.h>

#include <assert.h>
#include <string.h>

enum s_argument_type_t {
  S_ARGUMENT_TYPE_FLAG_LONG,
  S_ARGUMENT_TYPE_FLAG_SHORT,
  S_ARGUMENT_TYPE_SEPARATOR,
  S_ARGUMENT_TYPE_VALUE,
};
typedef enum s_argument_type_t s_argument_type_t;

static ssize_t get_flag_index_id_long(const char* id_long, const s_application_t* application);
static ssize_t get_flag_index_id_short(char id_short, const s_application_t* application);
static s_argument_type_t get_argument_type(const char* argument);
static inline void validate_parameters(const s_application_t* application, int argc, const char* argv[]);

void s_application_parse(const s_application_t* application, int argc, const char* argv[]) {
  validate_parameters(application, argc, argv);

  bool passed_separator = false;
  for(int i = 1; i < argc; i ++) {
#define CALL_VALUE_CALLBACK \
    if(application->value_callback)                                     \
      application->value_callback(argv[i], application->value_callback_data);

    if(passed_separator) {
      CALL_VALUE_CALLBACK

      continue;
    }

    bool has_next = (i < argc - 1);

    switch(get_argument_type(argv[i])) {
      case S_ARGUMENT_TYPE_FLAG_LONG:
        {
          ssize_t flag_index = get_flag_index_id_long(argv[i] + 2, application);
          if(flag_index < 0) {
            if(application->unknown_flag_long_callback)
              application->unknown_flag_long_callback(argv[i] + 2, application->unknown_flag_long_callback_data);

            break;
          }

          const char* value = strstr(argv[i], "=");
          if(value)
            application->flags[flag_index].callback(value + 1, application->flags[flag_index].callback_data);
          else if(has_next) {
	    i ++;
            application->flags[flag_index].callback(argv[i], application->flags[flag_index].callback_data);
          } else
            application->flags[flag_index].callback(NULL, application->flags[flag_index].callback_data);
        }

        break;
      case S_ARGUMENT_TYPE_FLAG_SHORT:
        {
          size_t argument_length = strlen(argv[i]);
          for(size_t j = 1; j < argument_length; j ++) {
            char id = argv[i][j];

            ssize_t flag_index = get_flag_index_id_short(id, application);
            if(flag_index < 0) {
              if(application->unknown_flag_short_callback)
                application->unknown_flag_short_callback(id, application->unknown_flag_short_callback_data);

              continue;
            }

            if(application->flags[flag_index].take_argument) {
              const char* argument = NULL;
              char next_char = argv[i][j + 1];

              if(next_char == '=')
                argument = argv[i] + j + 2;
              else if(next_char == '\0') {
                if(has_next) {
		  i ++;
                  argument = argv[i];
		}
              } else
                argument = argv[i] + j + 1;

              application->flags[flag_index].callback(argument, application->flags[flag_index].callback_data);
              break;
            } else
              application->flags[flag_index].callback(NULL, application->flags[flag_index].callback_data);
          }
        }
        break;
      case S_ARGUMENT_TYPE_SEPARATOR:
        passed_separator = true;
        break;
      case S_ARGUMENT_TYPE_VALUE:
        CALL_VALUE_CALLBACK
        break;
    }
  }
}

static s_argument_type_t get_argument_type(const char* argument) {
  if(strncmp(argument, "--", 2) == 0) {
    if(strlen(argument) == 2)
      return S_ARGUMENT_TYPE_SEPARATOR;

    return S_ARGUMENT_TYPE_FLAG_LONG;
  }

  if(argument[0] == '-')
    return S_ARGUMENT_TYPE_FLAG_SHORT;

  return S_ARGUMENT_TYPE_VALUE;
}
static ssize_t get_flag_index_id_long(const char* id_long, const s_application_t* application) {
  const char* equals = strstr(id_long, "=");
  ssize_t compare_n = -1;
  if(equals)
    compare_n = equals - id_long;

  for(size_t i = 0; i < application->flags_length; i ++)
    if(compare_n > 0) {
      if(strncmp(id_long, application->flags[i].id_long, compare_n) == 0)
	return i;
    }
    else if(strcmp(id_long, application->flags[i].id_long) == 0)
	return i;

  return -1;
}
static ssize_t get_flag_index_id_short(char id_short, const s_application_t* application) {
  for(size_t i = 0; i < application->flags_length; i ++)
    if(id_short == application->flags[i].id_short)
      return i;

  return -1;
}
static inline void validate_parameters(const s_application_t* application, int argc, const char* argv[]) {
  assert(argc > 0);
  assert(argv);
  for(int i = 0; i < argc; i ++)
    assert(argv[i]);

  assert(application);
  assert(application->flags);
  assert(application->flags_length);

  for(size_t i = 0; i < application->flags_length; i ++)
    assert(application->flags[i].callback);
}
