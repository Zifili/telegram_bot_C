// -*- Mode : C -*-

// main.c

#ifndef MAIN_I

#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>

#include "API.h"

int main() {
  response r = response_new();
  signed long int *array;
  get_update(r);
  // printf("%s", response_string(r));
  array = get_chat_ids(r);
  for (int i = 0; i < 3; i++)
    printf("%ld\n", array[i]);

  /*send_message(
      group_id,
      "Anche quando il tablet non collabora, o la formula sembra uno 'sgorbio "
      "che non ha assolutamente senso', tu devi continuare a lottare! Ricorda: "
      "basta 'addomesticare' la tesi e alla fine, *ecco, abbiamo finito!* La "
      "vittoria sulla logica è più dolce di una congiunzione duale.",
      r);*/
}

#endif // MAIN_I

// main.c ends here.
