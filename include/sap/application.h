#ifndef SAP_APPLICATION_H
#define SAP_APPLICATION_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  struct s_flag_t;

  struct s_application_t {
    struct s_flag_t* flags;
    size_t flags_length;

    void (*unknown_flag_long_callback) (const char* flag_long, void* data);
    void* unknown_flag_long_callback_data;
    void (*unknown_flag_short_callback) (char flag_short, void* data);
    void* unknown_flag_short_callback_data;

    void (*value_callback) (const char* value, void* data);
    void* value_callback_data;
  };
  typedef struct s_application_t s_application_t;

  extern void s_application_parse(const s_application_t* application, int argc, const char* argv[]);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SAP_APPLICATION_H
