/*
** EPITECH PROJECT, 2022
** FTP-BOOTSTRAP
** File description:
** reply_codes
*/

/// \file src/server/reply_codes.c

#include "reply_codes.h"
#include <stdlib.h>

static const ftp_rply_code known_reply_codes[] = {
    {.reply_code = 120,
        .msg = "120 Service ready in %3d minutes.\r\n"},
    {.reply_code = 125,
        .msg = "125 Data connection already open; transfer starting.\r\n"},
    {.reply_code = 150,
        .msg = "150 File status okay; about to open data connection.\r\n"},
    {.reply_code = 200,
        .msg = "200 ROGER ROGER.\r\n"},
    {.reply_code = 241,
        .msg = "241 Help message.\nOn how to use the server "
            "or the meaning of a "
            "particular "
            "non-standard command.\n"
            "This reply is useful only to the human user.\r\n"},
    {.reply_code = 220,
        .msg = "220 Service ready for new user.\r\n"},
    {.reply_code = 221,
        .msg = "Service closing control connection.\n "
            "Logged out if appropriate.\r\n"},
    {.reply_code = 226,
        .msg = "226 Closing data connection. "
            "Requested file action successful (for example, file transfer or "
            "file abort).\r\n"},
    {.reply_code = 227,
        .msg = "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n"},
    {.reply_code = 230,
        .msg = "230 User logged in, proceed.\r\n"},
    {.reply_code = 250,
        .msg = "250 Requested file action okay, completed.\r\n"},
    {.reply_code = 257,
        .msg = "257 \"%s\" created."},
    {.reply_code = 331,
        .msg = "331 User name okay, need password.\r\n"},
    {.reply_code = 332,
        .msg = "332 Need account for login.\r\n"},
    {.reply_code = 501,
        .msg = "501 Syntax error in parameters or arguments.\r\n"},
    {0, 0, 0}
};

ftp_rply_code get_rply_code_template(int reply_code)
{
    int i;

    for (i = 0; known_reply_codes[i].msg; i++)
        if (known_reply_codes[i].reply_code == reply_code)
            return (known_reply_codes[i]);
    return (known_reply_codes[i]);
}

ftp_rply_code *memset_ftp_rply_code(ftp_rply_code *reply_code,
    int code)
{
    ftp_rply_code rply_template = get_rply_code_template(code);

    reply_code = malloc(sizeof(reply_code));
    reply_code->reply_code = code;
    reply_code->msg = rply_template.msg;
    reply_code->args = rply_template.args;
    return (reply_code);
}
