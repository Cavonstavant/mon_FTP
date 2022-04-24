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


ftp_data_t *exec_cmd(ftp_data_t *data)
{
    ftp_data_t *ret = data;

    ret->reply_code = memset_ftp_rply_code(ret->reply_code, 331);
    return (ret);
}

void exec_ftp_cmd(tcp_server_t *srv, fd_set *tmp_reafds, fd_set *tmp_writefds)
{
    peer_t *tmp = NULL;

    CIRCLEQ_FOREACH(tmp, &srv->peers_head, peers) {
        if (FD_ISSET(tmp->sock_fd, tmp_reafds)) {
            if (read_from_client(tmp) == -1) {
                FD_CLR(tmp->sock_fd, &srv->read_fds);
                close(tmp->sock_fd);
                srv->sockets_to_be_removed[tmp->sock_fd] = 1;
                return;
            }
        }
        if (FD_ISSET(tmp->sock_fd, tmp_writefds)) {
            if (write_to_client(tmp) == -1) {
                FD_CLR(tmp->sock_fd, &srv->write_fds);
                close(tmp->sock_fd);
                srv->sockets_to_be_removed[tmp->sock_fd] = 1;
                return;
            }
        }
    }
    remove_unused_sockets(&srv->peers_head, srv->sockets_to_be_removed);
}
