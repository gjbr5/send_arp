#ifndef PACKET_H
#define PACKET_H

#include <cstdint>

const int MAC_LEN = 6;
const int IP_LEN = 4;
const uint16_t ETH_TYPE_ARP = 0x0806;
const uint8_t BROADCAST_MAC[MAC_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const uint8_t UNKNOWN_MAC[MAC_LEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint16_t ARP_HTYPE_ETH = 1;
const uint16_t ARP_PTYPE_IP = 0x0800;
const uint8_t ARP_HLEN_ETH = 6;
const uint8_t ARP_PLEN_IP = 4;
const uint16_t ARP_OPCODE_REQ = 1;
const uint16_t ARP_OPCODE_REP = 2;

typedef struct eth_header
{
    uint8_t dmac[MAC_LEN];
    uint8_t smac[MAC_LEN];
    uint16_t type;
} eth_header;

typedef struct arp_header
{
    uint16_t htype;
    uint16_t ptype;
    uint8_t hlen;
    uint8_t plen;
    uint16_t opcode;
    uint8_t sm[MAC_LEN];
    uint8_t si[IP_LEN];
    uint8_t tm[MAC_LEN];
    uint8_t ti[IP_LEN];
} arp_header;

typedef struct ip_header
{
    uint8_t vlen;
    uint8_t tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t fragments;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t hdr_cksum;
    uint8_t sip[IP_LEN];
    uint8_t dip[IP_LEN];
} ip_header;

#endif // PACKET_H
