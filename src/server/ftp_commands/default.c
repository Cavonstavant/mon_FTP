/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** default
*/

#include "myftp.h"
#include "commands.h"
#include "reply_codes.h"

void default_cmd(tcp_server_t *srv __attribute__((unused)),
    peer_t *client __attribute__((unused)))
{
    ftp_data_t *data = client->data;

    data->reply_code = memset_ftp_rply_code(data->reply_code, 501);
}