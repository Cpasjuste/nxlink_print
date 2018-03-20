#include <switch.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "nxlink_print.h"

static int sock = -1;

int nxlink_print_init() {

    struct sockaddr_in srv_addr;

    int ret = socketInitializeDefault();
    if (ret != 0) {
        printf("nxlink_print_init: socketInitialize error: %i\n", ret);
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (!sock) {
        printf("nxlink_print_init: socket error: %i (%s)\n", errno, strerror(errno));
        socketExit();
        return -1;
    }

    bzero(&srv_addr, sizeof srv_addr);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr = __nxlink_host;
    srv_addr.sin_port = htons(NXLINK_CLIENT_PORT);

    ret = connect(sock, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
    if (ret != 0) {
        printf("nxlink_print_init: connect error: %i (%s)\n", errno, strerror(errno));
        socketExit();
        return -1;
    }

    // redirect stdout
    fflush(stdout);
    dup2(sock, STDOUT_FILENO);

    return ret;
}

void nxlink_print_exit() {
    socketExit();
}
