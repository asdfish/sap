#ifndef SAP_ERROR_H
#define SAP_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  struct s_error_t {
    union {
      struct {
	const char* function_name;
	const char* parameter_name;
	const char* reason;
      } invalid_parameter;
      struct {
	const char* function_name;
	const char* parameter_name;
      } null_parameter;
    } description;
    enum {
      ERROR_TYPE_INVALID_PARAMETER,
      ERROR_TYPE_NULL_PARAMETER,
    } type;
  };
  typedef struct s_error_t s_error_t;

  extern void s_error_print(const s_error_t* error);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SAP_ERROR_H
