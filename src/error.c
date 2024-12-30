#include <sap/error.h>

#include <stdio.h>

static void s_error_print_null_argument(const s_error_t* error) {
  fprintf(stderr, "An unexpected null argument was found at function \"%s\"'s \"%s\"\n",
	  error->description.null_argument.function_name,
	  error->description.null_argument.parameter_name);
  fflush(stderr);
}

void s_error_print(const s_error_t* error) {
  switch(error->type) {
    case ERROR_TYPE_NULL_ARGUMENT:
      s_error_print_null_argument(error);
      break;
  }
}
