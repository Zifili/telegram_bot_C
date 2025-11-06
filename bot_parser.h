#ifndef BOT_PARSER_H_
#define BOT_PARSER_H_

struct Response_t;

typedef struct Response_t *response;

extern char *set_method(char *method);
extern response bot_http(char *url);

#endif // BOT_PARSER_H_
