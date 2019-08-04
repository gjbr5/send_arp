#ifndef ARPCTL_H
#define ARPCTL_H

#include "packet.h"
#include <arpa/inet.h>
#include <pcap.h>

void send_arp(const char *interface,
              const uint8_t dmac[MAC_LEN],
              const uint8_t smac[MAC_LEN],
              const uint8_t sm[MAC_LEN],
              const uint8_t si[IP_LEN],
              const uint8_t tm[MAC_LEN],
              const uint8_t ti[IP_LEN],
              const uint16_t opcode,
              uint8_t reqmac[MAC_LEN] = nullptr);

#endif // ARPCTL_H
