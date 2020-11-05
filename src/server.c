# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"


int create_socket(){
  int sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  error(sfd == -1, "socket creation failure");
  int on = 1;
  error(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, & on, sizeof(on)), "socket configuration failure");
  #ifdef SO_REUSEPORT
  error(setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)), "socket configuration failure");
  #endif
  return sfd;
}

void create_binding(int sfd){
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(atoi("7777"));

  error(bind(sfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1, "binding failure");
}

void create_server_queue(int sfd){
    error(listen(sfd, SOMAXCONN) == -1, "listen failure");
}

int open_server(){
  int sfd = create_socket();
  create_binding(sfd);
  create_server_queue(sfd);
  return sfd;
}

int accept_spec(int sfd){
  int clilen = sizeof(struct sockaddr_in);
  struct sockaddr_in client_addr;
  int client_socket = accept(sfd, (struct sockaddr *)&client_addr, (socklen_t *) &clilen);
  error(client_socket == -1, "accept failure");

  return client_socket;
}

void send_message(int fd, char* buffer, int buffer_size){
  int todo = buffer_size;
  char* p = buffer;
  while(todo > 0){
    int res = send(fd, buffer, todo, 0);
    error(res == -1, "envoi du plateau vers le client impossible");
    todo -= res;
    p += res;
  }
}

void close_socket(int sfd){
  shutdown(sfd, SHUT_RDWR);
  close(sfd);
}
