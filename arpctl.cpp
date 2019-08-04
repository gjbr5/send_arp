#include "arpctl.h"

void send_arp(const char *interface,
              const uint8_t dmac[MAC_LEN],
              const uint8_t smac[MAC_LEN],
              const uint8_t sm[MAC_LEN],
              const uint8_t si[IP_LEN],
              const uint8_t tm[MAC_LEN],
              const uint8_t ti[IP_LEN],
              const uint16_t opcode,
              uint8_t reqmac[MAC_LEN])
{
    uint8_t packet[sizeof(eth_header) + sizeof(arp_header)];
    eth_header *eth = reinterpret_cast<eth_header *>(packet);
    arp_header *arp = reinterpret_cast<arp_header *>(packet + sizeof(eth_header));

    for (int i = 0; i < MAC_LEN; i++) {
        eth->dmac[i] = dmac[i];
        eth->smac[i] = smac[i];
        arp->sm[i] = sm[i];
        arp->tm[i] = tm[i];
    }

    for (int i = 0; i < IP_LEN; i++) {
        arp->si[i] = si[i];
        arp->ti[i] = ti[i];
    }

    eth->type = htons(ETH_TYPE_ARP);

    arp->htype = htons(ARP_HTYPE_ETH);
    arp->ptype = htons(ARP_PTYPE_IP);
    arp->hlen = ARP_HLEN_ETH;
    arp->plen = ARP_PLEN_IP;
    arp->opcode = htons(opcode);

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_live(interface, BUFSIZ, 1, 1000, errbuf);
    pcap_sendpacket(pcap, packet, sizeof(eth_header) + sizeof(arp_header));
    if (opcode == ARP_OPCODE_REQ) {
        while (true) {
            struct pcap_pkthdr *header;
            const uint8_t *packet;
            int res = pcap_next_ex(pcap, &header, &packet);
            if (res == 0)
                continue;
            if (res == -1 || res == -2)
                break;
            const eth_header *eth = reinterpret_cast<const eth_header *>(packet);
            const arp_header *arp = reinterpret_cast<const arp_header *>(packet
                                                                         + sizeof(eth_header));
            if (ntohs(eth->type) != ETH_TYPE_ARP)
                continue;
            bool match = true;
            for (int i = 0; i < IP_LEN; i++) {
                if (arp->si[i] != ti[i]) {
                    match = false;
                    break;
                }
            }
            if (!match)
                continue;
            for (int i = 0; i < MAC_LEN; i++)
                reqmac[i] = arp->sm[i];
            break;
        }
    }
    pcap_close(pcap);
}
