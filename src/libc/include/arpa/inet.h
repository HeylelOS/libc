#ifndef _ARPA_INET_H
#define _ARPA_INET_H

/* arpa/inet.h - definitions for internet operations */

/* As in <netinet/in.h> */
#include <_definitions/in_port_t.h>
#include <_definitions/in_addr_t.h>
#include <_definitions/in_addr.h>
#include <_definitions/INET_ADDRSTRLEN.h>
#include <_definitions/INET6_ADDRSTRLEN.h>

/* As in <inttypes.h> */
#include <_definitions/uint32_t.h>
#include <_definitions/uint16_t.h>

uint32_t htonl(uint32_t);
uint16_t htons(uint16_t);
uint32_t ntohl(uint32_t);
uint16_t ntohs(uint16_t);

in_addr_t   inet_addr(const char *);
char       *inet_ntoa(struct in_addr);
const char *inet_ntop(int, const void *restrict, char *restrict, socklen_t);
int         inet_pton(int, const char *restrict, void *restrict);

/* _ARPA_INET_H */
#endif
