#include <switch.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "nxnetprint.h"

static int sock = -1;

int nx_net_init(const char *ip, short port) {

    struct sockaddr_in srv_addr;

    int ret = socketInitializeDefault();
    if (ret != 0) {
        printf("nx_net_init: socketInitialize error: %i\n", ret);
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (!sock) {
        printf("nx_net_init: socket error: %i (%s)\n", errno, strerror(errno));
        socketExit();
        return -1;
    }

    bzero(&srv_addr, sizeof srv_addr);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons((uint16_t) port);

    inet_aton(ip, &srv_addr.sin_addr);

    ret = connect(sock, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
    if (ret != 0) {
        printf("nx_net_init: connect error: %i (%s)\n", errno, strerror(errno));
        nx_net_exit();
        return -1;
    }

    // redirect stdout
    fflush(stdout);
    dup2(sock, STDOUT_FILENO);

    return ret;
}

void nx_net_exit() {

    if (sock) {
        shutdown(sock, SHUT_RDWR);
        sock = -1;
        socketExit();
    }
}
