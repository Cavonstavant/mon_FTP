/*
** EPITECH PROJECT, 2022
** FTP-BOOTSTRAP
** File description:
** commands
*/

/// \file src/server/commands.c

#include "commands.h"
#include <string.h>

static const ftp_cmd_t known_commands[] = {
    {.cmd = "USER", .min_args = 1, .max_args = 1},
    {.cmd = "PASS", .min_args = 1, .max_args = 1},
    {.cmd = "CWD", .min_args = 1, .max_args = 1},
    {.cmd = "CDUP", .min_args = 0, .max_args = 0},
    {.cmd = "QUIT", .min_args = 0, .max_args = 0},
    {.cmd = "PWD", .min_args = 0, .max_args = 0},
    {.cmd = "NOOP", .min_args = 0, .max_args = 0},
    {.cmd = "PASV", .min_args = 0, .max_args = 0},
    {.cmd = "DELE", .min_args = 1, .max_args = 1},
    {.cmd = "PORT", .min_args = 1, .max_args = 1},
    {.cmd = "HELP", .min_args = 0, .max_args = 1},
    {.cmd = "RETR", .min_args = 1, .max_args = 1},
    {.cmd = "STOR", .min_args = 1, .max_args = 1},
    {.cmd = "LIST", .min_args = 0, .max_args = 1},
    {0, 0, 0, 0, 0, 0}
};

ftp_cmd_t get_ftp_cmd_template(char *ftp_cmd)
{
    int i;

    for (i = 0; known_commands[i].cmd; i++)
        if (strcmp(known_commands[i].cmd, ftp_cmd) == 0)
            return (known_commands[i]);
    return (known_commands[i]);
}

ftp_cmd_t *memset_ftp_cmd(ftp_cmd_t *ftp_cmd, char *cmd)
{
    ftp_cmd_t cmd_template = get_ftp_cmd_template(cmd);

    if (cmd_template.cmd == 0){
        bzero(ftp_cmd, sizeof(ftp_cmd_t));
        ftp_cmd->err_msg = strdup("502 Command not found");
        ftp_cmd->reply_code = 502;
        return (ftp_cmd);
    }
    ftp_cmd->cmd = strdup(cmd_template.cmd);
    ftp_cmd->min_args = cmd_template.min_args;
    ftp_cmd->max_args = cmd_template.max_args;
    ftp_cmd->args = NULL;
    ftp_cmd->err_msg = NULL;
    ftp_cmd->reply_code = 0;
    return (ftp_cmd);
}
