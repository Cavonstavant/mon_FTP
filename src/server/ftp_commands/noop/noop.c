/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** noop
*/

#include "net_utils.h"
#include "myftp.h"
#include "commands.h"
#include "reply_codes.h"

void exec_noop(tcp_server_t **srv __attribute__((unused)),
    peer_t **client __attribute__((unused)))
{
    return;
}