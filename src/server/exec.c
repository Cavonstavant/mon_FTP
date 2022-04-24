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

static void set_arg(ftp_data_t *data, char *token)
{
    int i;

    if(!data->cmd) {
        data->cmd = malloc(sizeof(ftp_cmd_t));
        bzero(data->cmd, sizeof(ftp_cmd_t));
        data->cmd = memset_ftp_cmd(data->cmd, token);
        data->cmd->args = malloc(sizeof(char*) * (data->cmd->max_args + 1));
        if (!data->cmd->args)
            HANDLE_ERROR("malloc");
        bzero(data->cmd->args, sizeof(char*) * (data->cmd->max_args + 1));
    } else {
        for (i = 0; data->cmd->args[i]; i++);
        data->cmd->args[i] = strdup(token);
        if (!data->cmd->args[i])
            HANDLE_ERROR("strdup");
    }
}


static ftp_data_t *exec_cmd(ftp_data_t *data)
{
    ftp_data_t *ret = data;

    ret->reply_code = memset_ftp_rply_code(ret->reply_code, 331);
    return (ret);
}

static ftp_data_t *parse_cmd_line(char *cmd)
{
    ftp_data_t *data = NULL;
    char *token = NULL;
    char *sep = " \r\n";

    if (!(data = malloc(sizeof(ftp_data_t))))
        return (NULL);
    bzero(data, sizeof(ftp_data_t));
    token = strtok(cmd, sep);
    set_arg(data, token);
    for (int i = 0; (token = strtok(NULL, sep)); i++) {
        if (i > data->cmd->max_args) {
            fprintf(stderr, data->cmd->err_msg);
            data->reply_code = memset_ftp_rply_code(data->reply_code, 501);
            return (data);
        }
        set_arg(data, token);
        if (!data->cmd)
            return (data);
    }
    return (exec_cmd(data));
}

static int read_from_client(peer_t *client)
{
    char *line = NULL;
    size_t to_read;
    ssize_t read_size;
    FILE *client_stream = fdopen(client->sock_fd, "r");
    ftp_data_t *data = client->data;

    read_size = getdelim(&line, &to_read, '\r', client_stream);
    if (read_size < 0){
        perror("read");
        return (-1);
    }
    if (read_size == 0)
        return -1;
    else {
        data = parse_cmd_line(line);
        if (!data->cmd->cmd) {
            dprintf(client->sock_fd, data->cmd->err_msg);
            return (-1);
        }
    }
    return (0);
}

void exec_ftp_cmd(tcp_server_t *srv)
{
    peer_t *tmp = NULL;

    CIRCLEQ_FOREACH(tmp, &srv->peers_head, peers) {
        if (FD_ISSET(tmp->sock_fd, &srv->read_fds)) {
            if (read_from_client(tmp) == -1) {
                FD_CLR(tmp->sock_fd, &srv->read_fds);
                close(tmp->sock_fd);
                srv->sockets_to_be_removed[tmp->sock_fd] = 1;
                return;
            }
        }
    }
    remove_unused_sockets(&srv->peers_head, srv->sockets_to_be_removed);
}
