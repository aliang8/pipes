#define HANDSHAKE_BUFFER_SIZE 1024
#define MESSAGE_BUFFER_SIZE 1024
#define servergreet "Bonjour!" 
#define clientgreet "Ni hao ma?" // the response
#define wkp "luigi"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int server_handshake(int *);
int client_handshake(int *);
int server_handshake1 (char *buffer);
int server_handshake2 (char *buffer, int from_client);
