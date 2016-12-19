#include "pipe_networking.h"

int server_handshake(int *from_client) {
  // STEP #1 - Server creates FIFO (Well Known Pipe)
  printf("[SERVER] Created WKP...\n");
  mkfifo(wkp, 0644);
    
  // STEP #2 - Sever waits for a connection
  printf("[SERVER] Waiting for a client to connect...\n");
  *from_client = open(wkp, O_RDONLY);
    
  // STEP #6 - Server receives client's message and removes the WKP
  char clientmsg[MESSAGE_BUFFER_SIZE];
  read(*from_client, clientmsg, MESSAGE_BUFFER_SIZE);
  printf("[SERVER] Received private FIFO name %s \n", clientmsg);
  remove(wkp);

  // STEP #7 - Server connects to client FIFO, sending an initial acknowledgement
  int clientfifo = open(clientmsg, O_WRONLY);
  printf("[SERVER] Connected to client FIFO %s.\n", clientmsg);
  write(clientfifo, servergreet, strlen(servergreet));
    
  // STEP #9 - Get confirmation from client
  read(*from_client, clientmsg, MESSAGE_BUFFER_SIZE);
  printf("[SERVER] Received client response: %s\n", clientmsg);

  return clientfifo;
}

int client_handshake(int *to_server) {

  // STEP #3 - Client creates a "private" FIFO
  char privateFIFO[MESSAGE_BUFFER_SIZE];
  sprintf(privateFIFO, "%d", getpid()); //the private fifo name
  printf("[CLIENT] Created private FIFO %s.\n", privateFIFO);
  mkfifo(privateFIFO, 0644);

  // STEP #4 - Client connects to server and sends the private FIFO name
  *to_server = open(wkp, O_WRONLY);
  write(*to_server, privateFIFO, strlen(privateFIFO));
  printf("[CLIENT] Connected to WKP and sent private FIFO %s!\n", privateFIFO);

  // STEP #5 - Client waits for a message from the server 
  printf("[CLIENT] Waiting for server response...\n");
  int clientfifo = open(privateFIFO, O_RDONLY);
    
  // STEP #8 - Client receives server's message, removes its private FIFO 
  char servermsg[MESSAGE_BUFFER_SIZE];
  read(clientfifo, servermsg, MESSAGE_BUFFER_SIZE);
  printf("[CLIENT] Received server message: %s\n", servermsg);
  remove(privateFIFO);
    
  // STEP #9 - Client sends a message, verifying the connection
  write(*to_server, clientgreet, strlen(clientgreet));
  printf("[CLIENT] Sent message to server.\n");
  printf("[CLIENT] Connection established with server!\n");
  
  return clientfifo;
}

int server_handshake1(char *buffer){
  // Making the Well Known Pipe
  int fifo = mkfifo(wkp, 0644);
    
  // Error checking 
  if (fifo >= 0){
    printf("[SERVER] Created WKP... \n");
  }
  else{
    printf("[SERVER] Error: %s\n", strerror(errno));
  }

  int wkpfd = open(wkp, O_RDONLY);
  read(wkpfd, buffer, sizeof(buffer));
  remove(wkp);
  printf("[SERVER] Received private FIFO name: %s\n", buffer);

  return wkpfd;
}

int server_handshake2(char *buffer, int from_client){
  int pfifo = open(buffer, O_WRONLY);
  printf("[SERVER] connected to client's WKP\n");
  write(pfifo, "connected to client WKP", 23);
    
  //receive client's message, verifying connection
  char msg2[MESSAGE_BUFFER_SIZE];
  read(from_client, msg2, MESSAGE_BUFFER_SIZE);
  printf("[SERVER] Received client response: %s\n", msg2);
  
  return pfifo;
}
  
