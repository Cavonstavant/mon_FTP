/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** ftp
*/

#include "myftp.h"
#include "commands.h"
#include "reply_codes.h"

static peer_t *accept_client(tcp_server_t *srv)
{
    peer_t *new_client = NULL;
    int client_fd = 0;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    client_fd = accept(srv->sock_fd,
        (struct sockaddr *)&client_addr,
        &client_addr_size);
    if (client_fd < 0)
        HANDLE_ERROR("accept");
    new_client = new_peer(client_fd, client_addr);
    if (new_client == NULL)
        HANDLE_ERROR("peer_create");
    FD_SET(client_fd, &srv->read_fds);
    new_client->data = malloc(sizeof(ftp_data_t));
    return (new_client);
}

static int read_from_client (int client_fd)
{
    char msg[MAX_MSG];
    int to_read;

    to_read = read(client_fd, msg, MAX_MSG);
    if (to_read < 0){
        perror("read");
        return (-1);
    }
    else if (to_read == 0)
        return -1;
    else {
        printf("Client answer: %s", msg);
        return (0);
    }
}

static void exec_ftp_cmd(tcp_server_t *srv)
{
    peer_t *tmp = NULL;

    CIRCLEQ_FOREACH(tmp, &srv->peers_head, peers) {
        if (FD_ISSET(tmp->sock_fd, &srv->read_fds)) {
            if (read_from_client(tmp->sock_fd) == -1) {
                FD_CLR(tmp->sock_fd, &srv->read_fds);
                close(tmp->sock_fd);
                srv->sockets_to_be_removed[tmp->sock_fd] = 1;
                return;
            }
        }
    }
    remove_unused_sockets(&srv->peers_head, srv->sockets_to_be_removed);
}

int run_server(tcp_server_t *srv)
{
    fd_set tmp_read_fd_set, tmp_write_fd_set;
    peer_t *new_peer = NULL;

    while (srv->state == RUNNING) {
        tmp_read_fd_set = srv->read_fds;
        if (pselect(FD_SETSIZE, &tmp_read_fd_set,
            NULL, NULL, NULL, NULL) < 0)
            HANDLE_ERROR("pselect");
        if (FD_ISSET(srv->sock_fd, &tmp_read_fd_set)) {
            new_peer = accept_client(srv);
            if (new_peer == NULL){
                fprintf(stderr, "Internal Error: could not accept client.\n");
                continue;
            } else
                dprintf(new_peer->sock_fd, get_rply_code_template(220).msg);
            CIRCLEQ_INSERT_HEAD(&srv->peers_head, new_peer, peers);
        } else
            exec_ftp_cmd(srv);
    }
    return (0);
}