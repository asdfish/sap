#ifndef SAP_ERROR_H
#define SAP_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  enum s_error_type_t {
    ERROR_TYPE_NULL_ARGUMENT,
  };
  typedef enum s_error_type_t s_error_type_t;

  struct s_error_description_null_argument_t {
    const char* function_name;
    const char* parameter_name;
  };
  typedef struct s_error_description_null_argument_t s_error_description_null_argument_t;

  union s_error_description_t {
    s_error_description_null_argument_t null_argument;
  };
  typedef union s_error_description_t s_error_description_t;

  struct s_error_t {
    s_error_description_t description;
    s_error_type_t type;
  };
  typedef struct s_error_t s_error_t;

  extern void s_error_print(const s_error_t* error);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SAP_ERROR_H
