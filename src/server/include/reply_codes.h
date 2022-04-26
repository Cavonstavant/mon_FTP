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
} ftp_rply_code;

/// \brief get a reply code template by it's reply_code
/// \param reply_code the reply code to fetch with
ftp_rply_code get_rply_code_template(int reply_code);

/// \brief memset a reply code
ftp_rply_code *memset_ftp_rply_code(ftp_rply_code *rply_code, int code);

#endif /* REPLY_CODES_H */
