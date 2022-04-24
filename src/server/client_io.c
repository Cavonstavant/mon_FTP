/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** read_write
*/

#include <string.h>
#include <stdlib.h>
#include "myftp.h"
#include "reply_codes.h"
#include "commands.h"

int read_from_client(peer_t *client)
{
    char *line = malloc(sizeof(char) * (MAX_MSG + 1));
    ssize_t read_size;
    ftp_data_t *data = client->data;

    if (!line)
        HANDLE_ERROR("malloc");
    read_size = read(client->sock_fd, line, MAX_MSG);
    if (read_size < 0)
        HANDLE_ERROR("read");
    if (read_size == 0)
        return -1;
    data = parse_cmd_line(strtok(line, "\n"));
    if (!data->cmd->cmd) {
        dprintf(client->sock_fd, data->cmd->err_msg);
        return (-1);
    }
    client->data = data;
    return (0);
}

int write_to_client(tcp_server_t *srv, peer_t *client)
{
    ftp_data_t *data = client->data;

    data = exec_cmd(srv, client);
    client->data = data;
    if (data->reply_code->msg)
        dprintf(client->sock_fd, data->reply_code->msg);
    return (0);
}