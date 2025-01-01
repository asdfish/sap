#ifndef SAP_FLAG_H
#define SAP_FLAG_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  struct s_flag_t {
    char id_short;
    const char* id_long;

    bool take_argument;

    // argument may be null
    void (*callback) (const char* argument, void* data);
    void* callback_data;
  };
  typedef struct s_flag_t s_flag_t;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SAP_FLAG_H
