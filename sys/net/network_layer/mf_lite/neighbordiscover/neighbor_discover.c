/*
* Description: This file is the actual implementation of neighbor_discover service
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/


#define ENABLE_DEBUG (0)
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include "thread.h"
#include "mutex.h"
#include "msg.h"
#include "xtimer.h"

#include "net/mf-lite/neighbordiscovery/neighbor_discover.h"
#include "net/mf-lite/neighbordiscovery/neighbor_table.h"

static int nbd_table_find_entry(){

}

int neighbor_table_add_entry(nbd_table_t *table, kernel_pid_t iface_id, 
 							uint16_t guid, uint64_t gHWaddr, uint32_t lifetime){
	mutex_lock(&(table->mtx_access));
	size_t count = 1;
	nbd_table_entry_t *entry[count];

	//check if the entry is there or not
	//search the table to find the entry is there or not
	int ret = nbd_table_find_entry();

	if(ret == 1){
		//update the existing entry
	}else{
		//create a new entry
	}

	mutex_unlock(&(table->mtx_access));
	return ret;
}

uint64_t neighbor_table_get_gHWaddr(nbd_table_t *table, kernel_pid_t *iface_id,
                     uint16_t guid){
	int ret = nbd_table_find_entry()
}