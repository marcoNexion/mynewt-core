/* netq.h -- Simple packet queue
 *
 * Copyright (C) 2010--2012 Olaf Bergmann <bergmann@tzi.org>
 *
 * This file is part of the library tinyDTLS. Please see the file
 * LICENSE for terms of use.
 */

#include <assert.h>
#include "../include/tinydtls/dtls_config.h"
#include "../include/tinydtls/debug.h"
#include "../include/tinydtls/netq.h"
#include "../include/tinydtls/t_list.h"

//#include "util/oc_memb.h"
static struct os_mempool netq_storage_pool;    //OC_MEMB(netq_storage, netq_t, NETQ_MAXCNT);               
static uint8_t netq_storage_area[OS_MEMPOOL_BYTES(NETQ_MAXCNT,
      sizeof(netq_t))];

static inline netq_t *
netq_malloc_node(size_t size) {
  //return (netq_t *)oc_memb_alloc(&netq_storage);
  return (netq_t *)os_memblock_get(&netq_storage_pool);
}

static inline void
netq_free_node(netq_t *node) {
  //oc_memb_free(&netq_storage, node);
  os_memblock_put(&netq_storage_pool, node);
}

void
netq_init() {
  //oc_memb_init(&netq_storage);
  os_mempool_init(&netq_storage_pool, NETQ_MAXCNT,
      sizeof(netq_t), netq_storage_area, "netq_storage");
}

int 
netq_insert_node(netq_list_t *queue, netq_t *node) {
  netq_t *p;

  assert(queue);
  assert(node);

  p = (netq_t *)list_head(queue);
  
  while(p && p->t <= node->t && list_item_next(p))
    p = list_item_next(p);

  if (p)
    list_insert(p, node, next);  //
  else
    list_push(queue, node);       //SLIST_INSERT_HEAD


  /*SLIST_FOREACH(p, queue, next) {
    if(p->t > node->t){
      list_insert(queue, p, node);
    }
  }
  if(p==NULL){
    list_push(queue, node);
  }*/

  return 1;
}

netq_t *
netq_head(netq_list_t *queue) {
  if (!queue)
    return NULL;

  return list_head(queue);
}

netq_t *
netq_next(netq_t *p) {
  if (!p)
    return NULL;

  return list_item_next(p);
}

void
netq_remove(netq_list_t *queue, netq_t *p) {
  if (!queue || !p)
    return;

  list_remove(queue, p);
}

netq_t *netq_pop_first(netq_list_t *queue) {
  if (!queue)
    return NULL;

  return list_pop(queue);
}

netq_t *
netq_node_new(size_t size) {
  netq_t *node;
  node = netq_malloc_node(size);

#ifndef NDEBUG
  if (!node)
    dtls_warn("netq_node_new: malloc\n");
#endif

  if (node)
    memset(node, 0, sizeof(netq_t));

  return node;  
}

void 
netq_node_free(netq_t *node) {
  if (node)
    netq_free_node(node);
}

void 
netq_delete_all(netq_list_t *nqueue) {

  netq_t *node;

  SLIST_FOREACH(node, nqueue, next) {
    netq_free_node(node);
  }
  
}

