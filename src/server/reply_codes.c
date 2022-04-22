/*
** EPITECH PROJECT, 2022
** FTP-BOOTSTRAP
** File description:
** reply_codes
*/

/// \file src/server/reply_codes.c

#include "reply_codes.h"

static const fpt_rply_code known_reply_codes[] = {
    {.reply_code = 120,
        .msg = "Service ready in %3d minutes.\n"},
    {.reply_code = 125,
        .msg = "Data connection already open; transfer starting.\n"},
    {.reply_code = 150,
        .msg = "File status okay; about to open data connection.\n"},
    {.reply_code = 200,
        .msg = "Command okay.\n"},
    {.reply_code = 241,
        .msg = "Help message.\nOn how to use the server or the meaning of a \
            particular \
            non-standard command.\n\
            This reply is useful only to the human user.\n"},
    {.reply_code = 220,
        .msg = "Service ready for new user.\n"},
    {.reply_code = 221,
        .msg = "Service closing control connection.\n \
            Logged out if appropriate.\n"},
    {.reply_code = 226,
        .msg = "Closing data connection. \
            Requested file action successful (for example, file transfer or \
            file abort).\n"},
    {.reply_code = 227,
        .msg = "Entering Passive Mode (h1,h2,h3,h4,p1,p2)."},
    {.reply_code = 230,
        .msg = "User logged in, proceed."},
    {.reply_code = 250,
        .msg = "Requested file action okay, completed."},
    {.reply_code = 257,
        .msg = "\"%s\" created."},
    {.reply_code = 331,
        .msg = "User name okay, need password."},
    {.reply_code = 332,
        .msg = "Need account for login."},
    {0, 0, 0}
};

fpt_rply_code get_rply_code_template(int reply_code)
{
    int i;

    for (i = 0; known_reply_codes[i].msg; i++)
        if (known_reply_codes[i].reply_code == reply_code)
            return (known_reply_codes[i]);
    return (known_reply_codes[i]);
}
