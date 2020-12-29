/* t_list -- tinydtls lists
 *
 * Copyright (C) 2012 Olaf Bergmann <bergmann@tzi.org>
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

/**
 * @file t_list.h
 * @brief Wrappers for list structures and functions
 */

#ifndef _DTLS_LIST_H_
#define _DTLS_LIST_H_

#include "tinydtls.h"
#include "util/oc_list.h"

typedef oc_list_t list_t;

#define list_item_next(item)            SLIST_NEXT(item, next)               //(oc_list_item_next(item))
#define list_head(list)                 SLIST_FIRST(list)                    //(oc_list_head(list))
#define list_insert(list, prev, new)    SLIST_INSERT_AFTER(list, prev, new)  //(oc_list_insert(list, prev, new))
#define list_remove(list, item)         SLIST_REMOVE(list, item, netq_s, next)              //(oc_list_remove(list, item))
#define list_pop(list)                  SLIST_FIRST(list)                     //(oc_list_pop(list))
#define list_push(list, item)           SLIST_INSERT_HEAD(list, item, next)   //(oc_list_push(list, item))

#endif /* _DTLS_LIST_H_ */

