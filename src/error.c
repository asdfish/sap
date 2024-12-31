#include <sap/error.h>

#include <stdio.h>

static inline void s_error_print_invalid_parameter(const s_error_t* error);
static inline void s_error_print_null_parameter(const s_error_t* error);

void s_error_print(const s_error_t* error) {
  switch(error->type) {
  case ERROR_TYPE_INVALID_PARAMETER:
    s_error_print_invalid_parameter(error);
    break;
  case ERROR_TYPE_NULL_PARAMETER:
    s_error_print_null_parameter(error);
    break;
  }
}

static inline void s_error_print_invalid_parameter(const s_error_t* error) {
  fprintf(stderr, "Invalid parameter at %s, %s:\n%s\n",
	  error->description.invalid_parameter.function_name,
	  error->description.invalid_parameter.parameter_name,
	  error->description.invalid_parameter.reason);
  fflush(stderr);
}
static inline void s_error_print_null_parameter(const s_error_t* error) {
  fprintf(stderr, "Null parameter at %s, %s\n",
	  error->description.null_parameter.function_name,
	  error->description.null_parameter.parameter_name);
  fflush(stderr);
}
