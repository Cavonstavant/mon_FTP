#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/queue.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#pragma once

typedef struct peer_s {
    int sock_fd;
    struct sockaddr_in peer_addr;
    CIRCLEQ_ENTRY(peer_s) peers;
} peer_t;

CIRCLEQ_HEAD(peers_head, peer_s);

#define HANDLE_ERROR(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while(0)

/// \brief Create a basic listening socket that binds of INNARD_ANY
/// \param port Port to listen on
int make_socket(uint16_t port);

/// \brief remove a peer from the collection of peers
/// \param peers the head of the collection of peers created with CIRCLEQ_INIT
/// \param tbr to be removed peers with <b>tbr[peer->sock_fd] == 1</b>
void remove_unused_sockets(struct peers_head *peers, int tbr[FD_SETSIZE]);

void display_clients(struct peers_head *peers_head);
