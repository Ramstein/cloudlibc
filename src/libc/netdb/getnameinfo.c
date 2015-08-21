// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <sys/socket.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include <assert.h>
#include <netdb.h>
#include <string.h>

#include "netdb_impl.h"

static_assert(NI_MAXHOST >= INET_ADDRSTRLEN,
              "NI_MAXHOST too small to fit an IPv4 address");
static_assert(NI_MAXHOST >= INET6_ADDRSTRLEN + 11,
              "NI_MAXHOST too small to fit an IPv6 address and scope ID");

int getnameinfo(const struct sockaddr *restrict sa, size_t salen,
                char *restrict node, size_t nodelen, char *restrict service,
                size_t servicelen, int flags) {
  // Validate flags.
  if ((flags & ~(NI_NUMERICSERV | NI_DGRAM)) != 0)
    return EAI_BADFLAGS;
  if (node == NULL && service == NULL)
    return EAI_NONAME;

  // Call inet_ntop() to convert the address.
  in_port_t port;
  switch (sa->sa_family) {
    case AF_INET: {
      if (salen < sizeof(struct sockaddr_in))
        return EAI_FAMILY;
      const struct sockaddr_in *sin = (const struct sockaddr_in *)sa;
      if (node != NULL) {
        if (inet_ntop(AF_INET, &sin->sin_addr, node, nodelen) == NULL)
          return EAI_OVERFLOW;
      }
      port = sin->sin_port;
      break;
    }
    case AF_INET6: {
      if (salen < sizeof(struct sockaddr_in6))
        return EAI_FAMILY;
      const struct sockaddr_in6 *sin6 = (const struct sockaddr_in6 *)sa;
      if (node != NULL) {
        if (inet_ntop(AF_INET6, &sin6->sin6_addr, node, nodelen) == NULL)
          return EAI_OVERFLOW;
        // TODO(ed): Scope!
      }
      port = sin6->sin6_port;
      break;
    }
    default:
      return EAI_FAMILY;
  }

  if (service != NULL) {
    if ((flags & NI_NUMERICSERV) == 0) {
      // Try to obtain the textual service name from the IANA port
      // number database.
      uint8_t protoid = (flags & NI_DGRAM) != 0 ? 2 : 1;
      for (const char *entry = __iana_port_numbers;
           portstr_get_port(entry) != 0; entry = portstr_get_next(entry)) {
        if (portstr_get_port(entry) == port &&
            portstr_match_protoid(entry, protoid)) {
          const char *str = portstr_get_name(entry);
          size_t len = strlen(str) + 1;
          if (len > servicelen)
            return EAI_OVERFLOW;
          memcpy(service, str, len);
          return 0;
        }
      }
    }

    // Fall back to returning the port number.
    char portbuf[6];
    char *portstr = portbuf + sizeof(portbuf);
    *--portstr = '\0';
    port = ntohs(port);
    do {
      *--portstr = port % 10 + '0';
      port /= 10;
    } while (port != 0);
    size_t portstrlen = portbuf + sizeof(portbuf) - portstr;
    if (portstrlen > servicelen)
      return EAI_OVERFLOW;
    memcpy(service, portstr, portstrlen);
  }
  return 0;
}
