/*
* Description: This file is for providing the static routing functional features
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
//haoyang: header defined
#include "net/mf_lite/mf_static_routing.h"
#include "net/mf_lite/mf_routing_table.h"

mf_routing_table_entry_t *head;
mf_routing_table_entry_t *tail;

void linkList_init(void){
//	uint16_t macid;
	head = (mf_routing_table_entry_t *) malloc(sizeof(mf_routing_table_entry_t));
	tail = (mf_routing_table_entry_t *) malloc(sizeof(mf_routing_table_entry_t));
	head->next_entry = tail;
	tail->next_entry = tail;
}

mf_routing_table_entry_t *mf_routing_table_append_entry(uint16_t guid, uint16_t nextHopGuid){
	mf_routing_table_entry_t *entry;
	mf_routing_table_entry_t *cur;

	cur = head;
	//loop to the end of the link list
	while(cur->next_entry != tail){
		cur = cur->next_entry;
	}
	entry = (mf_routing_table_entry_t *) malloc(sizeof(mf_routing_table_entry_t));
	entry->dst_guid = guid;
	entry->nexthop_guid = nextHopGuid;
	entry->next_entry = tail;
	//move the pointer
	cur->next_entry = entry;

	return entry;
}

void print_mf_routing_table(mf_routing_table_entry_t *ptr){
	ptr = head->next_entry;
	printf("guid------------nexthopGuid\n");
	int counter = 0;
	while(ptr != tail){
		counter++;
		printf("%d\n", counter);
		printf("%" PRIu16 "------------%" PRIu16 "\n", ptr->dst_guid, ptr->nexthop_guid);
		ptr = ptr->next_entry;

	}
}
