#include "chat.h"
#include "message.h"
#include "ipc.h"
#include <signal.h>
#include <sys/select.h>

volatile sig_atomic_t running = 1;

void handle_signal(__attribute__((unused)) int sig) {
    running = 0;
}

int main() {
    signal(SIGINT, handle_signal);

    printf("[SERVER] Chat server started on %s\n", SOCKET_PATH);

    int server_fd = setup_unix_socket_server(SOCKET_PATH);
    if (server_fd < 0) {
        perror("Failed to setup server socket");
        exit(EXIT_FAILURE);
    }

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(server_fd, &readfds);
    int max_fd = server_fd;

    while (running) {
        fd_set tempfds = readfds;
        if (select(max_fd + 1, &tempfds, NULL, NULL, NULL) < 0) {
            perror("select");
            break;
        }

        // Aceptar nuevas conexiones
        if (FD_ISSET(server_fd, &tempfds)) {
            int client_fd = accept(server_fd, NULL, NULL);
            if (client_fd < 0) {
                perror("accept");
            } else {
                printf("[INFO] New client connected (FD: %d)\n", client_fd);
                FD_SET(client_fd, &readfds);
                if (client_fd > max_fd) {
                    max_fd = client_fd;
                }
            }
        }

        // Leer mensajes de los clientes
        for (int fd = 0; fd <= max_fd; fd++) {
            if (FD_ISSET(fd, &tempfds) && fd != server_fd) {
                message_t msg;
                ssize_t bytes_read = read(fd, &msg, sizeof(message_t));
                if (bytes_read <= 0) {
                    printf("[INFO] Client (FD: %d) disconnected\n", fd);
                    close(fd);
                    FD_CLR(fd, &readfds);
                } else {
                    printf("[MSG] %s: %s\n", msg.from_user, msg.text);
                }
            }
        }
    }

    close(server_fd);
    unlink(SOCKET_PATH);
    printf("[SERVER] Shutting down...\n");
    return 0;
}
