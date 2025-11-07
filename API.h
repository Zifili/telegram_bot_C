#ifndef API_H_
#define API_H_

#include "bot_parser.h"

//---- API FUNCTIONS ----
extern void get_update(response r);
extern void send_message(size_t chat_id, char *text, response r);
extern signed long int *get_chat_ids(response update);

#endif // API_H_
