//
// Created by cpasjuste on 20/02/18.
//

#ifndef NXNETPRINT_H
#define NXNETPRINT_H

#ifdef __cplusplus
extern "C" {
#endif

int nx_net_init(const char *ip, short port);

void nx_net_exit();

#ifdef __cplusplus
}
#endif

#endif //NXNETPRINT_H
