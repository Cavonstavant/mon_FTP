/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** ftp
*/

/// \file src/server/ftp.c

#include "net_utils.h"
#include <signal.h>

int main(int ac, char **av)
{
    int conn_fd;
    tcp_server_t *ftp_server;

    if (ac != 3) {
        fprintf(stderr, "Usage: %s <port> <path>\n", av[0]);
        exit(84);
    }
    ftp_server = create_tcp_server((int)strtol(av[1], NULL, 10));
    return (run_server(ftp_server));
    free(ftp_server);
}
