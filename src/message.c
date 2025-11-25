#include "message.h"

void send_message(int fd, message_t *msg) {
    if (write(fd, msg, sizeof(message_t)) < 0) {
        perror("write");
    }
}

void receive_message(int fd, message_t *msg) {
    if (read(fd, msg, sizeof(message_t)) < 0) {
        perror("read");
    }
}

void print_message(message_t *msg) {
    switch (msg->type) {
        case MSG_BROADCAST:
            printf("[%s] %s\n", msg->from_user, msg->text);
            break;
        case MSG_PRIVATE:
            printf("[%s -> %s] %s\n", msg->from_user, msg->to_user, msg->text);
            break;
        case MSG_JOIN:
            printf("[SYSTEM] %s joined the chat\n", msg->from_user);
            break;
        case MSG_LEAVE:
            printf("[SYSTEM] %s left the chat\n", msg->from_user);
            break;
        default:
            printf("[UNKNOWN] Message type\n");
    }
}
