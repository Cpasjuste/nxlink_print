//
// Created by cpasjuste on 20/02/18.
//

#ifndef NXNETPRINT_H
#define NXNETPRINT_H

int nx_net_init(const char *ip, int port);

void nx_net_print(const char *str, ...);

void nx_net_exit();

#endif //NXNETPRINT_H
