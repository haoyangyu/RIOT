/*
* Description: This file is for providing the neighbor discovering functional features
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/

#ifndef NEIGHBOR_DISCOVER_H_
#define NEIGHBOR_DISCOVER_H_


#include <stdint.h>
//haoyang: header defined
#include "net/mf_lite/mf_routing_table.h"

void linkList_init(void);

mf_routing_table_entry_t *mf_routing_table_append_entry(uint16_t guid, uint16_t nextHopGuid);
/*
int mf_routing_table_update_entry(uint16_t guid, uint16_t nextHopGuid);

void mf_routing_table_remove_entry(uint16_t guid);

uint16_t mf_routing_table_get_nextHopGuid(mf_routing_table_entry_t *ptr, uint16_t guid);
*/
void print_mf_routing_table(mf_routing_table_entry_t *ptr);

#endif
