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
