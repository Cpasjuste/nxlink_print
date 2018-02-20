#include <switch.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <zconf.h>

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
    }
    return ret;
}

void nx_net_print(const char *str, ...) {

    if (sock) {
        va_list valist;
        va_start(valist, str);
        char buf[512];
        size_t len = (size_t) vsnprintf(buf, 512, str, valist);
        send(sock, buf, len, 0);
        va_end(valist);
    }
}

void nx_net_exit() {

    if (sock) {
        shutdown(sock, SHUT_RDWR);
        sock = -1;
        socketExit();
    }
}
