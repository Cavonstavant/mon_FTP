/*
** EPITECH PROJECT, 2022
** FTP-BOOTSTRAP
** File description:
** reply_codes
*/

/// \file src/server/reply_codes.h

#ifndef REPLY_CODES_H
#define REPLY_CODES_H

/// \brief maps a ftp reply code to a message
/// \note Base values are declared inside reply_codes.c
/// msg is a printf formatted string
/// args are the args that will be passed and casted inside msg
typedef struct reply_codes_s {
    int reply_code;
    char *msg;
    void *args;
} fpt_rply_code;

/// \brief get a reply code template by it's reply_code
/// \param reply_code the reply code to fetch with
fpt_rply_code get_rply_code_template(int reply_code);

#endif /* REPLY_CODES_H */
