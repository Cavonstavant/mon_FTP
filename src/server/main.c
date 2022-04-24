/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** ftp
*/

/// \file src/server/ftp.c

#include "myftp.h"
#include <signal.h>

int main(int ac, char **av)
{
    tcp_server_t *ftp_server;

    if (ac != 3) {
        fprintf(stderr, "Usage: %s <port> <path>\n", av[0]);
        exit(84);
    }
    ftp_server = create_tcp_server((int)strtol(av[1], NULL, 10));
    if (!ftp_server) {
        fprintf(stderr, "Failed to create server\n");
        exit(84);
    }
    add_user_to_server(ftp_server, "Anonymous", "");
    ftp_server->arbitrary_data = (void*)av[2];
    return (run_server(ftp_server));
}
