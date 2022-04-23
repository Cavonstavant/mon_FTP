/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** exec
*/

/// \file src/server/exec.c

#include "net_utils.h"
#include "commands.h"
#include "reply_codes.h"

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

void exec_ftp_cmd(tcp_server_t *srv)
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