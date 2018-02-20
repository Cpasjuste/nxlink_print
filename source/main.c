#include <string.h>
#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <zconf.h>

static int sock = -1;

int nx_net_init(const char *ip, int port) {

    struct sockaddr_in srv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&srv_addr, sizeof srv_addr);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons((uint16_t) port);

    inet_pton(AF_INET, ip, &(srv_addr.sin_addr));

    return connect(sock, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
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
    }
}
