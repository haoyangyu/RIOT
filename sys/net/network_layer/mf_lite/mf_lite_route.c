/*
* Description: This file is for implementing the route-related functionality
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/

#include "net/mf_lite/mf_lite_route.h"
#include <stdlib.h> //for malloc
#include <inttypes.h> //for PRIu16
#include <stdio.h> //for printf

list_head_p mf_lite_routing_table_p;

void mf_lite_route_add_tail(mf_lite_short_guid_t dst_guid, mf_lite_short_guid_t nexthop_guid){
  mf_lite_routing_table_entry_p tmp;
  tmp = (mf_lite_routing_table_entry_p)malloc(sizeof(mf_lite_routing_table_entry_t));
  //set the value to the new allocated memory space
  tmp->dst_guid = dst_guid;
  tmp->nexthop_guid = nexthop_guid;

  list_add_tail(&tmp->list, mf_lite_routing_table_p);
}

int mf_lite_route_find(mf_lite_short_guid_t dst_guid, mf_lite_short_guid_t *nexthop_guid){
  list_head_p pos;
  mf_lite_routing_table_entry_p entry;
  int ret = 0;

  list_for_each(pos, mf_lite_routing_table_p){
    entry = list_entry(pos, mf_lite_routing_table_entry_t, list);
    if(entry->dst_guid == dst_guid){
      *nexthop_guid = entry->nexthop_guid;
      ret = 1;
    }
  }

  return ret;
}

void mf_lite_route_printf(list_head_p head){
  list_head_p pos;
  mf_lite_routing_table_entry_p entry;

  printf("dst_guid----------------nexthop_guid\n");
  list_for_each(pos, head){
    entry = list_entry(pos, mf_lite_routing_table_entry_t, list);
    printf("%" PRIu16 "----------------%" PRIu16 "\n", entry->dst_guid, entry->nexthop_guid);
  }
}
