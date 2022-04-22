/*
** EPITECH PROJECT, 2022
** FTP-BOOTSTRAP
** File description:
** commands
*/

/// \file src/server/commands.h

#ifndef COMMANDS_H
#define COMMANDS_H

/// \brief Represents an ftp command
/// \note Base values for each command are stored inside commands.c
/// Values that needs to be filled are:
///     - args
///     - err_msg
///     - reply_code
typedef struct ftp_command_s {
    char *cmd;
    int min_args;
    int max_args;
    char **args;
    char *err_msg;
    int reply_code;
} ftp_cmd_t;

/// \brief get a ftp command template by it's command name
/// \param cmd the reply cmd to fetch with
ftp_cmd_t get_ftp_cmd_template(char *ftp_cmd);

#endif /* COMMANDS_H */
