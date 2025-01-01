#include <sap/application.h>
#include <sap/flag.h>

#include <iostream>

#define ARRAY_LENGTH(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))

int main(void) {
  s_flag_t flags[] = {
    {
      'h', "help", false,
      [] (const char* arg, void* data) {
	std::cout << "help\n";
      }, nullptr
    },
    {
      'o', "output", true,
      [] (const char* arg, void* data) {
	std::cout << arg << "\n";
      }, nullptr
    },
  };

  s_application_t app;
  app.flags = flags;
  app.flags_length = ARRAY_LENGTH(flags);

  app.unknown_flag_long_callback = nullptr;
  app.unknown_flag_short_callback = nullptr;
  app.value_callback = nullptr;

  const char* argv[] = {
    "test", "-ho=asdf",
  };
  s_application_parse(&app, ARRAY_LENGTH(argv), argv);

  return 0;
}
