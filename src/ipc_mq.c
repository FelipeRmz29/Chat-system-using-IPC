#include "ipc.h"
#include <mqueue.h>

int setup_message_queue_server(const char *mq_name) {
    struct mq_attr attr = {.mq_maxmsg = 10, .mq_msgsize = sizeof(message_t)};
    mqd_t mq = mq_open(mq_name, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return -1;
    }
    return (int)mq;
}

int setup_message_queue_client(const char *mq_name) {
    mqd_t mq = mq_open(mq_name, O_WRONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return -1;
    }
    return (int)mq;
}
