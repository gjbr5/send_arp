#include "infinfo.h"

void getIP(const char *interface, uint8_t ip[4])
{
    struct ifreq ifr;
    strncpy(ifr.ifr_name, interface, sizeof(interface) - 1);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0 || ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
        return;
    }
    close(sock);

    for (int i = 0; i < 4; i++)
        ip[i] = static_cast<uint8_t>(ifr.ifr_addr.sa_data[i + 2]);
}

void getMac(const char *interface, uint8_t mac[6])
{
    struct ifreq ifr;
    strncpy(ifr.ifr_name, interface, sizeof(interface) - 1);

    int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock < 0 || ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
        return;
    }
    close(sock);

    for (int i = 0; i < 6; i++)
        mac[i] = static_cast<uint8_t>(ifr.ifr_hwaddr.sa_data[i]);
}
