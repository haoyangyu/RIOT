/*
* Description: This file is for providing the neighbor discovering functional features
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/

#ifndef NEIGHBOR_DISCOVER_H_
#define NEIGHBOR_DISCOVER_H_

#include <stdint.h>
//haoyang: header defined
 #include "net/mf_lite/neighbordiscovery/neighbor_table.h"

/**
 * @brief Adds a new entry in the corresponding neighbor table for finding the hwaddr based on GUID
 *
 * @param[in] table          the fib table the entry should be added to
 * @param[in] iface_id       the interface ID
 * @return 0 on success
 *         -ENOMEM if the entry cannot be created due to insufficient RAM
 *         -EFAULT if dst and/or next_hop is not a valid pointer
 */
 int neighbor_table_add_entry(nbd_table_t *table, kernel_pid_t iface_id,
 							uint16_t guid, uint64_t gHWaddr, uint32_t lifetime);

 /**
 * @brief Adds a new entry in the corresponding neighbor table for finding the hwaddr based on GUID
 *
 * @param[in] table          the fib table the entry should be added to
 * @return 0 on success
 *         -ENOMEM if the entry cannot be created due to insufficient RAM
 *         -EFAULT if dst and/or next_hop is not a valid pointer
 */
 int neighbor_table_update_entry(nbd_table_t *table, uint16_t guid, uint64_t gHWaddr, uint32_t lifetime);

 /**
 * @brief removes an entry from the corresponding FIB table
 *
 * @param[in] table         the fib table containing the entry to remove
 * @param[in] dst           the destination address
 * @param[in] dst_size      the destination address size
 */
void neighbor_table_remove_entry(nbd_table_t *table, uint16_t guid);

/**
 * @brief removes an entry from the corresponding FIB table
 *
 * @param[in] table         the fib table containing the entry to remove
 * @param[in] dst           the destination address
 * @param[in] dst_size      the destination address size
 */
uint64_t neighbor_table_get_gHWaddr(nbd_table_t *table, kernel_pid_t *iface_id,
                     uint16_t guid);

 /**
 * @brief Prints the FIB content (does not print the entries)
 *
 * @param[in] table         the fib instance to print
 */
void print_nbd_table(nbd_table_t *table);
