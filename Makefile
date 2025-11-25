CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

TARGET_SERVER = $(BIN_DIR)/chat_server
TARGET_CLIENT = $(BIN_DIR)/chat_client

SRC_SERVER = $(SRC_DIR)/chat_server.c $(SRC_DIR)/ipc_sockets.c $(SRC_DIR)/message.c $(SRC_DIR)/utils.c
SRC_CLIENT = $(SRC_DIR)/chat_client.c $(SRC_DIR)/ipc_sockets.c $(SRC_DIR)/message.c $(SRC_DIR)/utils.c

all: $(TARGET_SERVER) $(TARGET_CLIENT)

$(TARGET_SERVER): $(SRC_SERVER)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@

$(TARGET_CLIENT): $(SRC_CLIENT)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@

clean:
	rm -rf $(BIN_DIR)
