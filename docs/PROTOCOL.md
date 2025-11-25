# Message Protocol

## Message Types
- `MSG_JOIN`: Client joining the chat.
- `MSG_LEAVE`: Client leaving the chat.
- `MSG_BROADCAST`: Broadcast message to all clients.
- `MSG_PRIVATE`: Private message to a specific client.
- `MSG_LIST_USERS`: Request to list online users.
- `MSG_USER_LIST`: Response with list of online users.
- `MSG_ERROR`: Error message.
- `MSG_PING`: Keep-alive ping.
- `MSG_PONG`: Keep-alive pong.

## Message Structure
```c
typedef struct {
    message_type_t type;
    char from_user[USERNAME_MAX];
    char to_user[USERNAME_MAX];
    char text[MSG_MAX_SIZE];
    time_t timestamp;
    int client_id;
} message_t;

---

### **`docs/ARCHITECTURE.md`**
```markdown
# System Architecture

## Components
- **Server**: Manages clients, messages, and commands.
- **Client**: Connects to server, sends/receives messages.
- **IPC**: UNIX sockets and message queues for communication.

## Workflow
1. Server starts and listens for connections.
2. Clients connect and send their username.
3. Clients send messages to the server.
4. Server broadcasts messages to all clients or routes private messages.
