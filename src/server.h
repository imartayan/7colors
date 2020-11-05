#ifndef SERVER_H
#define SERVER_H

# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>

#define error(cond, msg)        \
  if(cond){                     \
    fprintf(stderr, "%s", msg); \
    exit(1);                    \
  }

void create_socket();
void create_binding();
void create_server_queue();
void open_server();

void accept_spec();

void close_server();
#endif
