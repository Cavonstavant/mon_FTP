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
#include "myftp.h"


ftp_data_t *exec_cmd(tcp_server_t *src, peer_t *client)
{
    ftp_data_t *ret = client->data;

    if (ret->cmd == NULL) {
        ret->reply_code = memset_ftp_rply_code(ret->reply_code, 501);
        return (ret);
    }
    if (ret->cmd->func)
        ret->cmd->func(src, client);
    return (ret);
}

static int exec_read(tcp_server_t *srv, peer_t *client, fd_set *read_fds)
{
    if (FD_ISSET(client->sock_fd, read_fds)) {
        if (read_from_client(client) == -1) {
            FD_CLR(client->sock_fd, &srv->read_fds);
            close(client->sock_fd);
            srv->sockets_to_be_removed[client->sock_fd] = 1;
            return (1);
        }
    }
    return (0);
}

static int exec_write(tcp_server_t *srv, peer_t *client, fd_set *write_fds)
{
    if (FD_ISSET(client->sock_fd, write_fds)) {
        if (write_to_client(srv, client) == -1) {
            FD_CLR(client->sock_fd, &srv->write_fds);
            close(client->sock_fd);
            srv->sockets_to_be_removed[client->sock_fd] = 1;
            return (1);
        }
    }
    return (0);
}

void exec_ftp_cmd(tcp_server_t *srv, fd_set *tmp_reafds, fd_set *tmp_writefds)
{
    peer_t *tmp = NULL;
    ftp_data_t *data = NULL;

    CIRCLEQ_FOREACH(tmp, &srv->peers_head, peers) {
        if (exec_read(srv, tmp, tmp_reafds))
            continue;
        data = tmp->data;
        printf("Command: %s\n", data->cmd->cmd);
        for (int i = 0; data->cmd->args[i]; i++)
            printf("\tArg %d: %s\n", i, data->cmd->args[i]);
        if (exec_write(srv, tmp, tmp_writefds))
            continue;
    }
    remove_unused_sockets(&srv->peers_head, srv->sockets_to_be_removed);
}
