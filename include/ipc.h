#ifndef IPC_H
#define IPC_H

#include "chat.h"

int setup_unix_socket_server(const char *socket_path);
int setup_unix_socket_client(const char *socket_path);
int setup_message_queue_server(const char *mq_name);
int setup_message_queue_client(const char *mq_name);

#endif // IPC_H
