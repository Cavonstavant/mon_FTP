#include "net_utils.h"

int main(int ac, char **av)
{
    int sock_fd, conn_fd;
    struct sockaddr_in serv_addr, peer_addr;
    socklen_t peer_addr_size;
    char *buff = malloc(sizeof(char) * 500);
    size_t msg_len = 0;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(av[1]);
    serv_addr.sin_port = htons(atoi(av[2]));
    memset(buff, 0, sizeof(char) * 500);
    if ((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        HANDLE_ERROR("socket");
    if (ac != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", av[0]);
        exit(EXIT_FAILURE);
    }
    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        HANDLE_ERROR("connect");
    else
        printf("Connected to %s:%hu\n", av[1], atoi(av[2]));
    for(;;) {
        getline(&buff, &msg_len, stdin);
        if (write(sock_fd, buff, msg_len) < 0)
            HANDLE_ERROR("write");
    }
    free(buff);
    return (0);
}