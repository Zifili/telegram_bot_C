#ifndef BOT_PARSER_H_
#define BOT_PARSER_H_

#include <stdlib.h>
struct Response_t;

typedef struct Response_t *response;

//---- BASE FUNCTIONS -----
extern response response_new(void);
extern char *set_method(char *method);
extern void bot_http(char *url, response r);
extern void free_response(response r);
extern char *response_string(response r);

#endif // BOT_PARSER_H_
