/* netq.h -- Simple packet queue
 *
 * Copyright (C) 2010--2012 Olaf Bergmann <bergmann@tzi.org>
 *
 * This file is part of the library tinyDTLS. Please see the file
 * LICENSE for terms of use.
 */

#ifndef _NETQ_H_
#define _NETQ_H_

#include "tinydtls.h"
#include "global.h"
#include "peer.h"
#include "dtls_time.h"

/**
 * \defgroup netq Network Packet Queue
 * The netq utility functions implement an ordered queue of data packets
 * to send over the network and can also be used to queue received packets
 * from the network.
 * @{
 */
#ifndef NETQ_MAXCNT
#if defined(DTLS_ECC) || defined(DTLS_X509)
#define NETQ_MAXCNT 5 /**< maximum number of elements in netq structure */
#elif defined(DTLS_PSK)
#define NETQ_MAXCNT 3 /**< maximum number of elements in netq structure */
#endif
#endif

/** 
 * Datagrams in the netq_t structure have a fixed maximum size of
 * DTLS_MAX_BUF to simplify memory management on constrained nodes. */ 
typedef unsigned char netq_packet_t[DTLS_MAX_BUF];

SLIST_HEAD(dtls_peer_list, dtls_peer_s);
typedef struct dtls_peer_list dtls_peer_list_t;

typedef struct netq_s {
  SLIST_ENTRY(netq_s) next;

  clock_time_t t;	        /**< when to send PDU for the next time */
  unsigned int timeout;		/**< randomized timeout value */

  //SLIST_HEAD(, dtls_peer_t) peer;  //struct dtls_peer_t *peer;		/**< remote address */

  dtls_peer_t *peer;

  uint16_t epoch;
  uint8_t type;
  unsigned char retransmit_cnt;	/**< retransmission counter, will be removed when zero */

  size_t length;		/**< actual length of data */
  uint8_t *data;//struct os_mbuf *data;  //netq_packet_t data;		/**< the datagram to send */
  
} netq_t;

SLIST_HEAD(node_queue_s, netq_s);
typedef struct node_queue_s netq_list_t;

void netq_init();

/** 
 * Adds a node to the given queue, ordered by their time-stamp t.
 * This function returns @c 0 on error, or non-zero if @p node has
 * been added successfully.
 *
 * @param queue A pointer to the queue head where @p node will be added.
 * @param node  The new item to add.
 * @return @c 0 on error, or non-zero if the new item was added.
 */
//int netq_insert_node(list_t queue, netq_t *node);
int netq_insert_node(netq_list_t *queue, netq_t *node);

/** Destroys specified node and releases any memory that was allocated
 * for the associated datagram. */
void netq_node_free(netq_t *node);

/** Removes all items from given queue and frees the allocated storage */
void netq_delete_all(netq_list_t *nqueue);

/** Creates a new node suitable for adding to a netq_t queue. */
netq_t *netq_node_new(size_t size);

/**
 * Returns a pointer to the first item in given queue or NULL if
 * empty. 
 */
netq_t *netq_head(netq_list_t *queue);

netq_t *netq_next(netq_t *p);
void netq_remove(netq_list_t *queue, netq_t *p);

/**
 * Removes the first item in given queue and returns a pointer to the
 * removed element. If queue is empty when netq_pop_first() is called,
 * this function returns NULL.
 */
netq_t *netq_pop_first(netq_list_t *queue);

/**@}*/

#endif /* _DTLS_NETQ_H_ */
