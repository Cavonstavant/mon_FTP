/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** read_write
*/

#include "myftp.h"
#include "reply_codes.h"
#include "commands.h"

int read_from_client(peer_t *client)
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

int write_to_client(peer_t *client)
{
    ftp_data_t *data = client->data;
    char *reply_msg = NULL;

    reply_msg = data->reply_code->msg;
    dprintf(client->sock_fd, reply_msg);
    return (0);
}