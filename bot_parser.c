#ifndef BOT_PARSER_I
#define BOT_PARSER_I

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bot_parser.h"

struct Response_t {
  char *string;
  size_t size;
};

//------ JSON METHODS ------
response response_new(void) {
  response r = malloc(sizeof(struct Response_t));
  if (!r)
    return NULL;
  r->string = NULL;
  r->size = 0;
  return r;
}

char *response_string(response r) { return r->string; }

void free_response(response r) {
  if (!r)
    return;
  free(r->string);
  free(r);
}

//------ CALLBACK FUNCTION ------
static size_t save_response(char *data, size_t size, size_t nmemb,
                            void *clientp) {
  size_t realsize = nmemb * size;
  response mem = (response)clientp;

  char *ptr = realloc(mem->string, mem->size + realsize + 1);
  if (!ptr)
    return 0; /* out of memory */

  mem->string = ptr;
  memcpy(&(mem->string[mem->size]), data, realsize);
  mem->size += realsize;
  mem->string[mem->size] = 0;

  return realsize;
}

//------ HTTP/GET ------
void bot_http(char *url, response r) {
  if (!r)
    return;

  free(r->string);
  r->string = malloc(1);
  r->string[0] = '\0';
  r->size = 0;

  // Making the request
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_response);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)r);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
  // printf("%s", json->string);
}

//------ API SELECTION ------
// outputs an url with the chosen method
char *set_method(char *method) {
  // reading the API key
  FILE *fptr = fopen(".secret", "r");
  if (!fptr) {
    fprintf(stderr, "Error: could not open .secret file\n");
    return NULL;
  }

  // Read the API key dynamically
  char secret[256]; // temporary stack buffer
  if (!fgets(secret, sizeof(secret), fptr)) {
    fclose(fptr);
    fprintf(stderr, "Error: could not read secret\n");
    return NULL;
  }
  fclose(fptr);

  // Remove trailing newline if present
  secret[strcspn(secret, "\r\n")] = '\0';

  const char *prefix_fmt = "https://api.telegram.org/bot%s/%s";
  size_t needed = snprintf(NULL, 0, prefix_fmt, secret, method) + 1;

  char *url = malloc(needed);
  if (!url) {
    fprintf(stderr, "Error: malloc failed for URL\n");
    return NULL;
  }

  snprintf(url, needed, prefix_fmt, secret, method);
  return url;
}

#endif // BOT_PARSER_I
