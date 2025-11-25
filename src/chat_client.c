#include "chat.h"
#include "message.h"
#include "ipc.h"

int main() {
    printf("=== Chat Client ===\n");

    // Conectar al servidor (ejemplo con UNIX socket)
    int client_fd = setup_unix_socket_client(SOCKET_PATH);
    if (client_fd < 0) {
        perror("Failed to connect to server");
        exit(EXIT_FAILURE);
    }

    char username[USERNAME_MAX];
    printf("Username: ");
    fgets(username, USERNAME_MAX, stdin);
    username[strcspn(username, "\n")] = '\0';

    // Enviar nombre de usuario al servidor
    message_t join_msg = {MSG_JOIN, "", "", "", time(NULL), 0};
    strncpy(join_msg.from_user, username, USERNAME_MAX);
    send_message(client_fd, &join_msg);

    // Bucle principal del cliente
    char input[MSG_MAX_SIZE];
    while (1) {
        printf("%s> ", username);
        fgets(input, MSG_MAX_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/quit") == 0) {
            break;
        }

        // Enviar mensaje al servidor
        message_t msg = {MSG_BROADCAST, "", "", "", time(NULL), 0};
        strncpy(msg.from_user, username, USERNAME_MAX);
        strncpy(msg.text, input, MSG_MAX_SIZE);
        send_message(client_fd, &msg);
    }

    close(client_fd);
    printf("[SYSTEM] Goodbye!\n");
    return 0;
}
