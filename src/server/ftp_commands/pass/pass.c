/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** pass
*/

#include "net_utils.h"
#include "myftp.h"
#include "commands.h"
#include "reply_codes.h"

static inline bool check_if_uname_set(peer_t **client)
{
    ftp_data_t *data = (*client)->data;

    return (data->auth->username != NULL);
}

void exec_pass(tcp_server_t **srv __attribute__((unused)),
    peer_t **client __attribute__((unused)))
{
    ftp_data_t *data = (*client)->data;

    if (!data->auth){
        data->auth = create_user(NULL,
            data->cmd->args[0] ? data->cmd->args[0] : "");
    }
    if (data->auth->logged_in)
        return;
    if (!check_if_uname_set(client))
        data->reply_code = memset_ftp_rply_code(data->reply_code, 332);
    else {
        data->reply_code = memset_ftp_rply_code(data->reply_code, 230);
        data->auth->logged_in = true;
    }
    (*client)->data = data;
}
