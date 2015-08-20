// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// <netdb.h> - definitions for network database operations
//
// Extensions:
// - NI_MAXHOST and NI_MAXSERV:
//   Present on most other systems.
// - gai_strerror_l():
//   gai_strerror() always uses the C locale.
//
// Features missing:
// - struct hostent, struct netent, endhostent(), endnetent(),
//   gethostent(), getnetbyaddr(), getnetbyname(), getnetent(),
//   sethostent() and setnetent():
//   System-wide host and network database not available.
// - getprotoent() and getservent():
//   Not thread-safe.
// - AI_ADDRCONFIG:
//   System-wide network configuration is not available.
// - NI_NAMEREQD and NI_NOFQDN:
//   Hostname resolution is not available.
// - IPPORT_RESERVED:
//   Not applicable to sandboxed environment.

#ifndef _NETDB_H_
#define _NETDB_H_

#include <_/types.h>

#ifndef _IN_ADDR_T_DECLARED
typedef __in_addr_t in_addr_t;
#define _IN_ADDR_T_DECLARED
#endif
#ifndef _IN_PORT_T_DECLARED
typedef __in_port_t in_port_t;
#define _IN_PORT_T_DECLARED
#endif
#ifndef _SOCKLEN_T_DECLARED
typedef __size_t socklen_t;
#define _SOCKLEN_T_DECLARED
#endif
#ifndef _UINT32_T_DECLARED
typedef __uint32_t uint32_t;
#define _UINT32_T_DECLARED
#endif

struct protoent {
  char *p_name;      // Official name of the protocol.
  char **p_aliases;  // Alternative protocol names.
  int p_proto;       // The protocol number.
};

struct servent {
  char *s_name;      // Official name of the service.
  char **s_aliases;  // Alternative service names.
  int s_port;        // The port number, in network byte order.
  char *s_proto;     // The name of the protocol to use when contacting.
};

struct addrinfo {
  int ai_flags;              // Input flags.
  int ai_family;             // Address family of socket.
  int ai_socktype;           // Socket type.
  int ai_protocol;           // Protocol of socket.
  __size_t ai_addrlen;       // Length of socket address.
  struct sockaddr *ai_addr;  // Socket address of socket.
  char *ai_canonname;        // Canonical name of service location.
  struct addrinfo *ai_next;  // Pointer to next in list.
};

#define AI_PASSIVE 0x1      // Socket address is intended for bind().
#define AI_CANONNAME 0x2    // Request for canonical name.
#define AI_NUMERICHOST 0x4  // Return numeric host address as name.
#define AI_NUMERICSERV 0x8  // Inhibit service name resolution.
#define AI_V4MAPPED 0x10    // Return IPv4-mapped IPv6 addresses.
#define AI_ALL 0x20         // Query for both IPv4 and IPv6 addresses.

#define NI_NUMERICSERV 0x1  // The numeric port is returned instead.
#define NI_DGRAM 0x2        // Service is a datagram service.

// Flags that are enabled unconditionally.
#define NI_NUMERICHOST 0   // The numeric host is returned instead.
#define NI_NUMERICSCOPE 0  // The numeric scope is returned instead.

#define EAI_AGAIN 1      // Future attempts may succeed.
#define EAI_BADFLAGS 2   // The flags had an invalid value.
#define EAI_FAIL 3       // A non-recoverable error occurred.
#define EAI_FAMILY 4     // Invalid address family or address length.
#define EAI_MEMORY 5     // There was a memory allocation failure.
#define EAI_NONAME 6     // The name does not resolve.
#define EAI_SERVICE 7    // Invalid service for socket type.
#define EAI_SOCKTYPE 8   // Invalid socket type.
#define EAI_SYSTEM 9     // A system error occurred.
#define EAI_OVERFLOW 10  // An argument buffer overflowed.

#define NI_MAXHOST 57  // Largest hostname returned by getnameinfo().
#define NI_MAXSERV 64  // Largest service name returned by getnameinfo().

__BEGIN_DECLS
void endprotoent(void);
void endservent(void);
void freeaddrinfo(struct addrinfo *);
const char *gai_strerror(int);
const char *gai_strerror_l(int, __locale_t);
int getaddrinfo(const char *__restrict, const char *__restrict,
                const struct addrinfo *__restrict,
                struct addrinfo **__restrict);
int getnameinfo(const struct sockaddr *__restrict, __size_t, char *__restrict,
                __size_t, char *__restrict, __size_t, int);
struct protoent *getprotobyname(const char *);
struct protoent *getprotobynumber(int);
struct servent *getservbyname(const char *, const char *);
struct servent *getservbyport(int, const char *);
void setprotoent(int);
void setservent(int);
__END_DECLS

#endif
