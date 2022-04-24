/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** my_ftp
*/

/// \file src/server/exec.c

#ifndef MYFTP_H
#define MYFTP_H

    #include "net_utils.h"
    #include "commands.h"
    #include "reply_codes.h"
    #include "net_utils/auth/user.h"

/// Repesents the data that will be contained inside peer_t::data
typedef struct ftp_data_s {
    /// The current working directory where the client currently is
    char *cwd;
    /// The current cmd that the client is executing
    ftp_cmd_t *cmd;
    /// The reply code with a message sent to the client after the exec cmd
    ftp_rply_code *reply_code;
    /// The auth data
    user_t *auth;
} ftp_data_t ;

int run_server(tcp_server_t *srv);

void exec_ftp_cmd(tcp_server_t *srv, fd_set *tmp_reafds, fd_set *tmp_writefds);

int read_from_client(peer_t *client);

int write_to_client(tcp_server_t *srv, peer_t *client);

ftp_data_t *parse_cmd_line(char *cmd);

ftp_data_t *exec_cmd(tcp_server_t *srv, peer_t *client);

#endif /* MYFTP_H */
