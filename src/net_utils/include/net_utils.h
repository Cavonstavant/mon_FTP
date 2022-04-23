#ifndef NET_UTILS_H
#define NET_UTILS_H

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
    #include "net_utils/auth/user.h"

    #define LISTEN_BACKLOG 50
    #define MAX_MSG 55555

    #define STOPPED false
    #define RUNNING true

/// \brief Represents a client connection
typedef struct peer_s {
    /// A file descriptor for the socket.
    int sock_fd;
    /// The address of the client.
    struct sockaddr_in peer_addr;
    // A pointer to a generic data type.
    void *data;
    /// A pointer to the next/prev peer.
    CIRCLEQ_ENTRY(peer_s) peers;
} peer_t;

/// \brief Initializes a circular queue of peers
CIRCLEQ_HEAD(peers_head, peer_s);

/// \brief Initializes a circular queue of users
CIRCLEQ_HEAD(users_head, user_s);

/// \brief Represents a basic tcp server
typedef struct tcp_server_s {
    int sock_fd;
    uint16_t port;
    struct sockaddr_in self;
    struct peers_head peers_head;
    struct users_head users_head;
    fd_set read_fds;
    fd_set write_fds;
    int sockets_to_be_removed[FD_SETSIZE];
    bool state;
} tcp_server_t;

#define HANDLE_ERROR(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while(0)

/// \brief Creates a new client
/// \param sock_fd The client file descriptor
/// \param peer_addr The client address informations
peer_t *new_peer(int fd, struct sockaddr_in addr);

/// \brief remove a peer from the collection of peers
/// \param peers the head of the collection of peers created with CIRCLEQ_INIT
/// \param tbr to be removed peers with <b>tbr[peer->sock_fd] == 1</b>
void remove_unused_sockets(struct peers_head *peers, int tbr[FD_SETSIZE]);

void display_clients(struct peers_head *peers_head);

/// \brief Create a TCP server
/// \param port Port to listen on
tcp_server_t *create_tcp_server(long port);

#endif //NET_UTILS_H