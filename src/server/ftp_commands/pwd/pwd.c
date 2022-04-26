/*
** EPITECH PROJECT, 2022
** *
** File description:
** pwd
*/

#include "net_utils.h"
#include "myftp.h"
#include "commands.h"
#include "reply_codes.h"

void exec_pwd(tcp_server_t **srv __attribute__((unused)),
    peer_t **client __attribute__((unused)))
{
    ftp_data_t *data = (*client)->data;

    if (!data->auth && !data->auth->logged_in) {
        data->reply_code = memset_ftp_rply_code(data->reply_code, 530);
        return;
    }
    data->reply_code = memset_ftp_rply_code(data->reply_code, 257);
    sprintf(data->reply_code->msg,
        "\"%s\"", data->cwd);
}