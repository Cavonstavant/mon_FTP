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
    char *tmp = NULL;

    if (!data->auth && !data->auth->logged_in) {
        data->reply_code = memset_ftp_rply_code(data->reply_code, 530);
        return;
    }
    data->reply_code = memset_ftp_rply_code(data->reply_code, 257);
    tmp = malloc(sizeof(char) * (strlen(data->reply_code->msg)));
    sprintf(tmp,
        data->reply_code->msg, data->cwd);
    data->reply_code->msg = tmp;
}