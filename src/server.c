# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>
#include <string.h>


void create_socket(){
  int sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  error(sfd == -1, "socket creation failure");
  int on = 1;
  error(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, & on, sizeof(on)), "socket configuration failure");
  #ifdef SO_REUSEPORT
  error(setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)), "socket configuration failure");
  #endif
}

void create_binding(){
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(atoi(7777));

  error(bind(sfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1, "binding failure");
}

void create_server_queue(){
    error(listen(sfd, SOMAXCONN) == -1, "listen failure");
}

void open_server(){
  create_socket();
  create_binding();
  create_server_queue();
}

void accept_spec(){
  int clilen = sizeof(struct sockaddr_in);
  struct sockaddr_in client_addr;
  int client_socket = accept(sfd, (struct sockaddr *)&client_addr, (socklen_t *) &clilen);
  error(client_socket == -1, "accept failure");

  fprintf(stdin, "client adress : %s", inet_ntoa(*(struct in_addr *)&client_addr));
  res = recv(client_socket, msg, 2048, 0);
  error(res  == -1, "recieve failure");
  msg[res] = '\0';
  fprintf(stderr, "message reçu : %s", msg);
  res = send(client_socket, msg, 2048, 0);
  error(res  == -1, "send failure");


}

void close_server(){
  shutdown(client_socket, SHUT_RDWR);
  close(client_socket);
}
