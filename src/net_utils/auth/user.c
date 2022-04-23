/*
** EPITECH PROJECT, 2022
** mon_FTP
** File description:
** user
*/

/// \file src/server/auth/user.c

#include "user.h"
#include <stdlib.h>
#include <string.h>

user_t *create_user(char *username, char *password)
{
    user_t *user = malloc(sizeof(user_t));

    if (!user)
        return (NULL);
    user->username = strdup(username);
    user->password = strdup(password);
    return (user);
}