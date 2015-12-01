#ifndef MF_LITE_ROUTE_H_
#define MF_LITE_ROUTE_H_

#include "net/mf_lite/mf_lite_config.h"
#include "net/mf_lite/linked_list.h"
//#include "kernel_types.h"
//#include "mutex.h"

// Container descriptor for a MF_ROUTING_ENTRY
typedef struct mf_lite_routing_table_entry {
	// short global unique id for destination
	mf_lite_short_guid_t dst_guid;
	// short global unique id for source
	mf_lite_short_guid_t nexthop_guid;
	//linked list for next entry
	list_head_t list;
	//leave for the future use
	//......
} mf_lite_routing_table_entry_t;

typedef mf_lite_routing_table_entry_t* mf_lite_routing_table_entry_p;

extern list_head_p mf_lite_routing_table_p;

//Insert entry into the list
//TODO: also modify the name to match the naming scheme
//void mf_lite_route_add(mf_lite_short_guid_t dst_guid, mf_lite_short_guid_t nexthop_guid);

//Find the mac address specified by guid
//TODO: also modify the name to match the naming scheme
//nexthop_guid: pointer to the space for next hop guid storage
//return: 1 if found, 0 otherwise
//int mf_lite_route_find(mf_lite_short_guid_t dst_guid, mf_lite_short_guid_t *nexthop_guid);



#endif
