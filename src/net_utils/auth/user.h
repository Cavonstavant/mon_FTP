/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** user
*/

/// \file src/server/include/auth/user.h

#ifndef USER_H
#define USER_H

    #include <unistd.h>
    #include <sys/queue.h>

typedef struct user_s {
    char *username;
    char *password;
    CIRCLEQ_ENTRY(user_s) users;
} user_t;

user_t *create_user(char *username, char *password);

#endif /* USER_H */
