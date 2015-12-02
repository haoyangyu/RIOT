/*
* Description: This file is for mf_static_route header file
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/

#ifndef MF_LITE_NEIGHBOR_H_
#define MF_LITE_NEIGHBOR_H_

#include "net/mf_lite/mf_lite_config.h"
#include "net/mf_lite/linked_list.h"


// Container descriptor for a MF_NEIGHBOR_ENTRY
typedef struct mf_lite_neighbor_table_entry {
  // short global guid
  mf_lite_short_guid_t guid;
  // short 15.4 hardware address
  short_macaddr_t macaddr;
  //linked list for next entry
  list_head_t list;
  //leave for the future use
  //......
} mf_lite_neighbor_table_entry_t;

typedef mf_lite_neighbor_table_entry_t* mf_lite_neighbor_table_entry_p;

extern list_head_p mf_lite_neighbor_table_p;


//Insert entry into the list
void mf_lite_neighbor_add_tail(mf_lite_short_guid_t guid, short_macaddr_t macaddr);

//Find the mac address specified by guid
//macaddr: pointer to the space for mac address storage
//return: 1 if found, 0 otherwise
int mf_lite_neighbor_find(mf_lite_short_guid_t guid, short_macaddr_t *macaddr);

//print the neighbor table out
void mf_lite_neighbor_printf(list_head_p head);

void print_table(void);

#endif
