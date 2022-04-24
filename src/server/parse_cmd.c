/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** parse_cmd
*/

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

ftp_data_t *parse_cmd_line(char *cmd)
{
    ftp_data_t *data = NULL;
    char *token = NULL;
    char *sep = " ";

    if (!(data = malloc(sizeof(ftp_data_t))))
        return (NULL);
    bzero(data, sizeof(ftp_data_t));
    token = strtok(cmd, sep);
    set_arg(data, token);
    for (int i = 0; (token = strtok(NULL, sep)); i++) {
        printf("%s\n", token);
        if (i > data->cmd->max_args) {
            fprintf(stderr, data->cmd->err_msg);
            data->reply_code = memset_ftp_rply_code(data->reply_code, 501);
            return (data);
        }
        set_arg(data, token);
    }
    return (data);
}
