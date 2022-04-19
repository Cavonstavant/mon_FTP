#include "net_utils.h"
#include <signal.h>

#define LISTEN_BACKLOG 50
#define MAX_MSG 55555


void sig_handler(void)
{
    // if (signo == SIGINT) {
        printf("Exiting...");
        exit(1);
    // }
}

void display_start_message(struct sockaddr_in addr)
{
    char *host_repr = malloc(sizeof(char) * 16);

    memset(host_repr, 0, sizeof(char) * 16);
    inet_ntop(AF_INET, &addr.sin_addr, host_repr, 16);
    printf("Server started on port %s:%hu.\n", host_repr, ntohs(addr.sin_port));
    free(host_repr);
}

int read_from_client (int client_fd)
{
    char msg[MAX_MSG];
    int to_read;

    to_read = read(client_fd, msg, MAX_MSG);
    if (to_read < 0)
        HANDLE_ERROR("read");
    else if (to_read == 0)
        return -1;
    else {
        printf("Client answer: %s", msg);
        return (0);
    }
}

int main(int ac, char **av)
{
    int sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    int conn_fd;
    fd_set read_fd_set, active_fd_set;
    struct sockaddr_in srv_addr, peer_addr;
    socklen_t peer_addr_size;
    uint16_t port;
    uint32_t host = htonl(INADDR_ANY);
    sigset_t sigmask;
    struct peers_head peers_head;
    peer_t *new_peer = NULL;
    peer_t *tmp = NULL;
    int sockets_to_be_removed[FD_SETSIZE] = {0};

    // char *buff = strdup("AAAAAAAAAAAAAAAAAAA");
    sigaddset(&sigmask, SIGINT);
    if (ac != 2) {
        fprintf(stderr, "Usage: %s <port>\n", av[0]);
        exit(EXIT_FAILURE);
    }
    CIRCLEQ_INIT(&peers_head);
    port = htons(atoi(av[1]));
    host = INADDR_ANY;
    if (sock_fd < 0)
        HANDLE_ERROR("socket");
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = port;
    srv_addr.sin_addr.s_addr = host;
    if (bind(sock_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0)
        HANDLE_ERROR("bind");
    if (listen(sock_fd, LISTEN_BACKLOG) < 0)
        HANDLE_ERROR("listen");
    display_start_message(srv_addr);
    FD_ZERO(&active_fd_set);
    FD_SET(sock_fd, &active_fd_set);
    while (true){
        read_fd_set = active_fd_set;
        if (pselect(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL, &sigmask) < 0)
            HANDLE_ERROR("select");
        if (FD_ISSET(sock_fd, &read_fd_set)){
            peer_addr_size = sizeof(peer_addr);
            conn_fd = accept(sock_fd, (struct sockaddr *)&peer_addr, &peer_addr_size);
            if (conn_fd < 0)
                HANDLE_ERROR("accept");
            FD_SET(conn_fd, &active_fd_set);
            printf("Connection from %s:%hu.\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
            if (!(new_peer = malloc(sizeof(struct peer_s))))
                HANDLE_ERROR("malloc");
            new_peer->peer_addr = peer_addr;
            new_peer->sock_fd = conn_fd;
            CIRCLEQ_INSERT_HEAD(&peers_head, new_peer, peers);
        } else {
            printf("reading from clients\n");
            // display_clients(&peers_head);
            CIRCLEQ_FOREACH(tmp, &peers_head, peers) {
                if (tmp && FD_ISSET(tmp->sock_fd, &read_fd_set)) {
                    if (read_from_client(tmp->sock_fd) < 0) {
                        FD_CLR(tmp->sock_fd, &active_fd_set);
                        close(tmp->sock_fd);
                        sockets_to_be_removed[tmp->sock_fd] = 1;
                    }
                }
            }
        }
        remove_unused_sockets(&peers_head, sockets_to_be_removed);
    }
    return (0);
}

