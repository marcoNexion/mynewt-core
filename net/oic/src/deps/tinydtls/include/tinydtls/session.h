/* dtls -- a very basic DTLS implementation
 *
 * Copyright (C) 2011--2014 Olaf Bergmann <bergmann@tzi.org>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _DTLS_SESSION_H_
#define _DTLS_SESSION_H_

#include <string.h>
#include <os/mynewt.h>
#include "C:\Dev\balisegps\repos\apache-mynewt-core\net\ip\mn_socket\include\mn_socket\mn_socket.h"
//#include <mn_socket/mn_socket.h>

#include "tinydtls.h"
#include "global.h"

#if defined(WITH_CONTIKI) || defined(WITH_OCF) || defined(MYNEWT)
#ifdef WITH_CONTIKI
#include "ip/uip.h"
typedef struct {
  unsigned char size;
  uip_ipaddr_t addr;
  unsigned short port;
  int ifindex;
} session_t;
#else /* WITH_CONTIKI */
#include "port/oc_connectivity.h"
typedef struct {
  unsigned char size;
  oc_endpoint_t addr;
} session_t;
#endif /* WITH_OCF */
#else /* WITH_CONTIKI || WITH_OCF */

#if 0 /*replaced by myNewt porting below*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
  socklen_t size;		/**< size of addr */
  union {
    struct sockaddr     sa;
    struct sockaddr_storage st;
    struct sockaddr_in  sin;
    struct sockaddr_in6 sin6;
  } addr;
  uint8_t ifindex;
} session_t;
#endif  //0

typedef uint8_t sa_family_t;

struct mn_sockaddr_storage {
  uint8_t       s2_len;
  sa_family_t   ss_family;
  char          s2_data1[2];
  uint32_t      s2_data2[3];
#if LWIP_IPV6
  uint32_t      s2_data3[3];
#endif /* LWIP_IPV6 */
};

typedef struct {
  uint32_t size;		/**< size of addr */
  union {
    struct mn_sockaddr     sa;
    struct mn_sockaddr_storage st;
    struct mn_sockaddr_in  sin;
    struct mn_sockaddr_in6 sin6;
  } addr;
  uint8_t ifindex;
} session_t;

#endif /* !(WITH_CONTIKI || WITH_OCF) */

/** 
 * Resets the given session_t object @p sess to its default
 * values.  In particular, the member rlen must be initialized to the
 * available size for storing addresses.
 * 
 * @param sess The session_t object to initialize.
 */
void dtls_session_init(session_t *sess);

/**
 * Compares the given session objects. This function returns @c 0
 * when @p a and @p b differ, @c 1 otherwise.
 */
int dtls_session_equals(const session_t *a, const session_t *b);

#endif /* _DTLS_SESSION_H_ */
