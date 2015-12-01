/*
* Description: This file is the format of mf routing table
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/

#ifndef MF_ROUTING_TABLE_H_
#define MF_ROUTING_TABLE_H_

#include <stdint.h>
#include "kernel_types.h"
#include "mutex.h" 

// Container descriptor for a MF_ROUTING_entry
typedef struct mf_routing_table_entry{
	// short global unique id for destination
	uint16_t dst_guid;
	// short global unique id for source
	uint16_t nexthop_guid;
	//linked list for next entry
	struct mf_routing_table_entry * next_entry;
	//leave for the future use
	//.........
}mf_routing_table_entry_t;

/*
// Meta information about the MF_ROUTING table
typedef struct {
	// array holding the NBD table entries
    mf_routing_table_entry_t *entries;
    // number of entries in the table
    size_t size;
    // access mutex to control exclusive operations on calls
    mutex_t mtx_access;
} mf_routing_table;
*/
#endif
