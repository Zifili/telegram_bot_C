// -*- Mode : C -*-

// main.c

#ifndef MAIN_I

#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>

#include "bot_parser.h"

int main() {
  response r = response_new();
  char *method = "getUpdates";
  char *url = set_method(method);
  bot_http(url, r);
  // printf("%s\n\n", response_string(r));

  cJSON *json = cJSON_Parse(response_string(r));
  if (json == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      printf("Error: %s\n", error_ptr);
    }
    cJSON_Delete(json);
    return 1;
  }

  // access the JSON data
  cJSON *result = cJSON_GetObjectItemCaseSensitive(json, "result");
  cJSON *res = cJSON_GetArrayItem(result, 0);
  cJSON *msg = cJSON_GetObjectItemCaseSensitive(res, "message");
  cJSON *chat = cJSON_GetObjectItemCaseSensitive(msg, "chat");
  cJSON *id = cJSON_GetObjectItemCaseSensitive(chat, "id");
  // printf("%s\n", cJSON_Print(id));

  // sends the answer to everything
  response pippo = response_new();
  char *sendMsg = "sendMessage?chat_id=%d&text=%s";
  char *text = "42%20is%20the%20answer";
  long chat_id = id->valueint;
  char test[200];
  char *prova;
  snprintf(test, 200, sendMsg, chat_id, text);
  prova = set_method(test);
  bot_http(prova, pippo);
  printf("%s", prova);
  printf("%s", response_string(pippo));

  //  delete the JSON object
  cJSON_Delete(json);
}

#endif // MAIN_I

// main.c ends here.
