// -*- Mode : C -*-

// API.c

#include <stdio.h>
#ifndef API_I

#include <cjson/cJSON.h>
#include <curl/curl.h>

#include "API.h"
#include "bot_parser.h"

//------ API CALLS ------
void get_update(response r) {
  if (r == NULL) {
    fprintf(stderr, "invalid response struct");
  }
  char *update = "getUpdates";
  bot_http(set_method(update), r);
}
signed long int *get_chat_ids(response update) {
  signed long int *ids = malloc(sizeof(signed long int) * 10);
  if (update == NULL) {
    fprintf(stderr, " : update is NULL");
    return NULL;
  }

  cJSON *json = cJSON_Parse(response_string(update));
  if (!json) {
    fprintf(stderr, ": failed to parse JSON\n");
    return NULL;
  }
  cJSON *result = cJSON_GetObjectItem(json, "result");
  if (!cJSON_IsArray(result)) {
    fprintf(stderr, " : no results found");
    return NULL;
  }
  cJSON *item = NULL;
  int i = 0;
  cJSON_ArrayForEach(item, result) {
    cJSON *message = cJSON_GetObjectItem(item, "message");
    if (!cJSON_IsObject(message))
      continue;
    cJSON *chat = cJSON_GetObjectItem(message, "chat");
    if (!cJSON_IsObject(chat))
      continue;
    cJSON *id = cJSON_GetObjectItem(chat, "id");
    if (!cJSON_IsNumber(id)) {
      fprintf(stderr, ": couldn't find id");
      return NULL;
    }
    ids[i++] = (signed long int)id->valuedouble;
  }
  cJSON_Delete(json);
  return ids;
}

void send_message(size_t chat_id, char *text, response r) {
  if (r == NULL) {
    r = response_new();
  }
  CURL *curl = curl_easy_init();
  if (!curl)
    return;

  char *encoded_text = curl_easy_escape(curl, text, 0);
  if (!encoded_text) {
    fprintf(stderr, "Failed to URL-encode text.\n");
    curl_easy_cleanup(curl);
    return;
  }
  char *format = "sendMessage?chat_id=%ld&text=%s";
  int needed = snprintf(NULL, 0, format, chat_id, encoded_text) + 1;
  char *message = malloc(needed);
  snprintf(message, needed, format, chat_id, encoded_text);
  printf("Calling Telegram Api sendMessage...\n");
  printf("%s\n", message);

  bot_http(set_method(message), r);
}

#endif // API_I

// API.c ends here.
