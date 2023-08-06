#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <ifaddrs.h>

#ifndef NI_MAXHOST
#define NI_MAXHOST 1025
#endif

#ifndef NI_NUMERICHOST
#define NI_NUMERICHOST 1
#endif

void get_network_info() {
    struct ifaddrs *ifaddr, *ifa;
    char host[NI_MAXHOST];
    int family, s;

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    printf("Información actual de red:\n");

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) continue;

        family = ifa->ifa_addr->sa_family;

        if (family == AF_INET || family == AF_INET6) {
            s = getnameinfo(ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
                            host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

            if (s != 0) {
                printf("Error al obtener la dirección: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }

            printf("Interfaz: %s\tDirección IP: %s\n", ifa->ifa_name, host);
        }
    }

    freeifaddrs(ifaddr);
}

int main() {
    // https://stackoverflow.com/a/13035344
    // force stdout to be line-buffered
    setvbuf(stdout, NULL, _IOLBF, 0);

    get_network_info();
    return 0;
}
