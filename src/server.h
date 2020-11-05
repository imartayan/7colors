#ifndef SERVER_H
#define SERVER_H

# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

#define error(cond, msg)        \
  if(cond){                     \
    fprintf(stderr, "%s", msg); \
    exit(1);                    \
  }

int create_socket();
void create_binding(int sfd);
void create_server_queue(int sfd);
int open_server();

int accept_spec(int sfd);

void close_server(int sfd);
#endif
