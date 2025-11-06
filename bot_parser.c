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

static size_t save_response(char *data, size_t size, size_t nmemb,
                            void *clientp) {
  size_t realsize = nmemb;
  struct Response_t *mem = (struct Response_t *)clientp;

  char *ptr = realloc(mem->string, mem->size + realsize + 1);
  if (!ptr)
    return 0; /* out of memory */

  mem->string = ptr;
  memcpy(&(mem->string[mem->size]), data, realsize);
  mem->size += realsize;
  mem->string[mem->size] = 0;

  return realsize;
}

response bot_http(char *url) {
  response json;
  json->string = malloc(1);
  json->size = 0;
  // Making the request
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_response);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&json);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    res = curl_easy_perform(curl);
    // free(json.string);
    curl_easy_cleanup(curl);
  }
  return json;
}

// outputs an url with the chosen method

char *set_method(char *method) {
  // reading the API key
  FILE *fptr = fopen(".secret", "r");
  int secret_lenght = 47;
  char secret[secret_lenght];
  fgets(secret, secret_lenght, fptr);
  fclose(fptr);

  // creating the URL string
  char *prefix = "https://api.telegram.org/bot%s/"; // 29
  int prefix_lenght = 29;
  char *url = malloc((sizeof(char) * prefix_lenght) +
                     (sizeof(char) * secret_lenght) + (sizeof(char) * strlen(method)) + 1); // 29+47+1
  sprintf(url, prefix, secret);
  // printf("%s\n", url);

  // appending method
  sprintf(url, "%s%s", url, method);
  return url;
}

#endif // BOT_PARSER_I
