#ifndef MESSAGE_H
#define MESSAGE_H

#include "chat.h"

void send_message(int fd, message_t *msg);
void receive_message(int fd, message_t *msg);
void print_message(message_t *msg);

#endif // MESSAGE_H
