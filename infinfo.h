#ifndef INFINFO_H
#define INFINFO_H

#include <arpa/inet.h>
#include <cstdint>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

void getIP(const char *interface, uint8_t ip[4]);
void getMac(const char *interface, uint8_t mac[6]);

#endif // INFINFO_H
