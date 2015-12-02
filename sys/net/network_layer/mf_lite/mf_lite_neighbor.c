/*
* Description: This file is for implementing the neighbor-related functionality
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/

#include "net/mf_lite/mf_lite_neighbor.h"
#include <stdlib.h> //for malloc
#include <stdio.h>
#include <inttypes.h> //for PRIu16

list_head_p mf_lite_neighbor_table_p;

void mf_lite_neighbor_add_tail(mf_lite_short_guid_t guid, short_macaddr_t macaddr){
  mf_lite_neighbor_table_entry_p tmp;
  //allocate the neighbor list for the 4 lists
  tmp = (mf_lite_neighbor_table_entry_p) malloc(sizeof(mf_lite_neighbor_table_entry_t));
  //set the value of the neighbor entry
  tmp->guid = guid;
  tmp->macaddr = macaddr;

  list_add_tail(&tmp->list, mf_lite_neighbor_table_p);
}

int mf_lite_neighbor_find(mf_lite_short_guid_t guid, short_macaddr_t *macaddr) {
  int ret = 0;
  mf_lite_neighbor_table_entry_p entry;
  list_head_p pos;

  list_for_each(pos, mf_lite_neighbor_table_p) {
    entry = list_entry(pos, mf_lite_neighbor_table_entry_t, list);
    if (entry->guid == guid) {
      *macaddr = entry->macaddr;
      ret = 1;
      break;
    }
  }

  return ret;
}

void mf_lite_neighbor_printf(list_head_p head){
  list_head_p pos;
  mf_lite_neighbor_table_entry_p entry;

  printf("guid----------------macaddr\n");
  list_for_each(pos, head){
    entry = list_entry(pos, mf_lite_neighbor_table_entry_t, list);
    printf("%d----------------%d\n", entry->guid, entry->macaddr);
  }
}

//extern list_head_t neighbor_list_1;

void print_table(void) {
  printf("%p\n", mf_lite_neighbor_table_p);
//  printf(">>>>>>> %p, %p\n", &neighbor_list_1, mf_lite_neighbor_table_p);
}
