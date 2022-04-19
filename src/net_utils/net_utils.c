#include "net_utils.h"

int make_socket(uint16_t port)
{
    int socket_fd;
    struct sockaddr_in addr;

    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
        HANDLE_ERROR("socket");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        HANDLE_ERROR("bind");
    return (socket_fd);
}

void remove_unused_sockets(struct peers_head *peers, int tbr[FD_SETSIZE])
{
    peer_t *peer = CIRCLEQ_FIRST(peers);
    peer_t *tmp = NULL;

    while (peer != (void *)&peers) {
        printf("Checking peer with socket: %d\n", peer->sock_fd);
        if (tbr[peer->sock_fd] == 1) {
            tmp = CIRCLEQ_NEXT(peer, peers);
            free(peer);
            peer = tmp;
        } else
            peer = CIRCLEQ_NEXT(peer, peers);
    }
}

void display_clients(struct peers_head *peers_head)
{
    peer_t *tmp = NULL;

    printf("\n\nList of connected client:\n/*----------------------*/\n");
    CIRCLEQ_FOREACH(tmp, peers_head, peers)
        printf("\t- %s:%hu on socket: %d\n", inet_ntoa(tmp->peer_addr.sin_addr),
            ntohs(tmp->peer_addr.sin_port), tmp->sock_fd);
    printf("/*----------------------*/\n");
}