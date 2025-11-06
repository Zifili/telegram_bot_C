// -*- Mode : C -*-

// main.c

#ifndef MAIN_I

#include <stdio.h>
#include <stdlib.h>

#include "bot_parser.h"

int main() {
  response json = response_new();
  char *method = "getMe";
  char *url = set_method(method);
  bot_http(url, json);
  printf("%s", json_string(json));
}

#endif // MAIN_I

// main.c ends here.
