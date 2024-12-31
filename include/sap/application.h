#ifndef SAP_APPLICATION_H
#define SAP_APPLICATION_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  struct s_error_t;
  struct s_flag_t;

  struct s_application_t {
    struct s_flag_t* flag;
    size_t flags_length;

    void (*error_callback) (const struct s_error_t* error, void* data);
    void* error_callback_data;

    void (*value_callback) (const char* value, void* data);
    void* value_callback_data;
  };
  typedef struct s_application_t s_application_t;

  extern void s_application_parse(const s_application_t* application, int argc, const char* argv[]);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SAP_APPLICATION_H
