// -*- Mode : C -*-

// main.c

#ifndef MAIN_I

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bot_parser.h"

int main() {
  char *method = "getMe";
  char *url = set_method(method);
  // printf("%s", json.string);
}

#endif // MAIN_I

// main.c ends here.
