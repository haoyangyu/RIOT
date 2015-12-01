/*
* Description: This file is the format of neighbor discovery table hold by different node
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/

#ifndef NEIGHBOR_TABLE_H_
#define NEIGHBOR_TABLE_H_

#include <stdint.h>
#include "kernel_types.h"
#include "mutex.h"

/**
 * @brief Container descriptor for a NBD table entry
 */
typedef struct nbd_table_entry_t {
	// interface id
	kernel_pid_t iface_id;
	// short global unique id
	uint16_t guid;
	// long global 802.15.4 address
	uint64_t gHWaddr;
	// lifetime of this entry (an absolute time-point stored here)
	uint64_t lifetime;
}nbd_table_entry_t;

/**
 * @brief Meta information about the FIB table
 */
typedef struct {
	// array holding the NBD table entries
    nbd_table_entry_t *entries;  
    // number of entries in the table
    size_t size;           
    // access mutex to control exclusive operations on calls
    mutex_t mtx_access;     
} nbd_table_t;