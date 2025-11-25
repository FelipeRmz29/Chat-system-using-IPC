#ifndef CHAT_H
#define CHAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <mqueue.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>

#define MAX_CLIENTS 100
#define USERNAME_MAX 32
#define MSG_MAX_SIZE 256
#define SOCKET_PATH "/tmp/chat.sock"
#define MQ_NAME "/chat_queue"

typedef enum {
    MSG_JOIN,
    MSG_LEAVE,
    MSG_BROADCAST,
    MSG_PRIVATE,
    MSG_LIST_USERS,
    MSG_USER_LIST,
    MSG_ERROR,
    MSG_PING,
    MSG_PONG
} message_type_t;

typedef struct {
    message_type_t type;
    char from_user[USERNAME_MAX];
    char to_user[USERNAME_MAX];
    char text[MSG_MAX_SIZE];
    time_t timestamp;
    int client_id;
} message_t;

#endif // CHAT_H
