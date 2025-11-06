#ifndef BOT_PARSER_H_
#define BOT_PARSER_H_

struct Response_t;

typedef struct Response_t *response;

extern response response_new(void);
extern char *set_method(char *method);
extern void bot_http(char *url, response json);
extern void free_response(response r);
extern char *json_string(response json);
#endif // BOT_PARSER_H_
