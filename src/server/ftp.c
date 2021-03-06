/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** ftp
*/

#include "myftp.h"
#include "commands.h"
#include "reply_codes.h"

static ftp_data_t* fill_client_data(void *data)
{
    ftp_data_t *ftp_data = NULL;

    if (!(ftp_data = (ftp_data_t*)malloc(sizeof(ftp_data_t))))
        HANDLE_ERROR("malloc");
    ftp_data->cmd = NULL;
    ftp_data->reply_code = NULL;
    ftp_data->auth = NULL;
    ftp_data->cwd = (char*)data;
    return (ftp_data);
}

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
    new_client->data = fill_client_data(srv->arbitrary_data);
    return (new_client);
}

static bool manage_new_conn(tcp_server_t *srv, fd_set *read_fs, peer_t *new)
{
    new = accept_client(srv);
    if (new == NULL){
        fprintf(stderr, "Internal Error: could not accept client.\n");
        return (false);
    } else {
        dprintf(new->sock_fd, get_rply_code_template(220).msg);
    }
    CIRCLEQ_INSERT_HEAD(&srv->peers_head, new, peers);
}

bool cwd_exists(char *path)
{
    if (!path)
        return (false);
    if (access(path, F_OK | W_OK | R_OK) == -1)
        HANDLE_ERROR("access");
    return (true);
}

int run_server(tcp_server_t *srv)
{
    fd_set tmp_rfds, tmp_wfds;
    peer_t *new_peer = NULL;

    cwd_exists((char*)srv->arbitrary_data);
    while (srv->state == RUNNING) {
        restore_fd_sets(&tmp_rfds, &tmp_wfds, &srv->read_fds, &srv->write_fds);
        if (pselect(FD_SETSIZE, &tmp_rfds, &tmp_wfds,
            NULL, NULL, NULL) < 0)
            HANDLE_ERROR("pselect");
        if (FD_ISSET(srv->sock_fd, &tmp_rfds)) {
            if (!manage_new_conn(srv, &tmp_rfds, new_peer))
                continue;
        } else
            exec_ftp_cmd(srv, &tmp_rfds, &tmp_wfds);
    }
    return (0);
}
