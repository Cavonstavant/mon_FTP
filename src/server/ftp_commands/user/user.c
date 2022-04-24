/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** user
*/

#include "net_utils.h"
#include "myftp.h"
#include "commands.h"
#include "reply_codes.h"

static inline bool check_if_passwd_set(peer_t *client)
{
    ftp_data_t *data = client->data;

    return (data->auth->password != NULL);
}

void exec_user(tcp_server_t *srv __attribute__((unused)),
    peer_t *client __attribute__((unused)))
{
    ftp_data_t *data = client->data;

    if (data->cmd->args[0] == NULL) {
        data->reply_code = memset_ftp_rply_code(data->reply_code, 501);
        return;
    }
    if (!data->auth)
        data->auth = create_user(data->cmd->args[0], NULL);
    if (data->auth->logged_in)
        return;
    if (strcmp(data->cmd->args[0], "Anonymous") == 0){
        if (!check_if_passwd_set(client))
            data->reply_code = memset_ftp_rply_code(data->reply_code, 331);
        else {
            data->reply_code = memset_ftp_rply_code(data->reply_code, 230);
            data->auth->logged_in = true;
        }
    } else
        data->reply_code = memset_ftp_rply_code(data->reply_code, 430);
}