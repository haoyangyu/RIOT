/*
* Description: This file is for initial a process(thread)
* that
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "thread.h"
//#include "msg.h"
#include "kernel.h"

#include "net/mf_lite/mf_lite_neighbor.h"
#include "net/mf_lite/mf_lite_route.h"
#include "net/mf_lite/mf_lite_static_route.h"

// PID of the mf_lite_static_route id
static kernel_pid_t _pid = KERNEL_PID_UNDEF;
// stack for the pktdump thread
static char _stack[MF_STATIC_ROUTE_STACKSIZE];

//mf_neighor_table_entry_t neighbor_list;
list_head_t neighbor_list_1;
list_head_t neighbor_list_2;
list_head_t neighbor_list_3;
list_head_t neighbor_list_4;

//initial the mf_neighbor table for every node
static void _mf_lite_static_routing_neigbor_table_init(void){
  //mf_neighor_table_entry_t *tmp;

  INIT_LIST_HEAD(&neighbor_list_1);
  INIT_LIST_HEAD(&neighbor_list_2);
  INIT_LIST_HEAD(&neighbor_list_3);
  INIT_LIST_HEAD(&neighbor_list_4);

  mf_lite_neighbor_table_p = &neighbor_list_1;
  mf_lite_neighbor_add(0x0002, 0x190e);

  mf_lite_neighbor_table_p = &neighbor_list_2;
  mf_lite_neighbor_add(0x0001, 0x190e);
  mf_lite_neighbor_add(0x0003, 0x190e);

  mf_lite_neighbor_table_p = &neighbor_list_3;
  mf_lite_neighbor_add(0x0002, 0x190e);
  mf_lite_neighbor_add(0x0004, 0x190e);

  mf_lite_neighbor_table_p = &neighbor_list_4;
  mf_lite_neighbor_add(0x0003, 0x190e);
  //allocate the neighbor list for the 4 lists
  //tmp = (mf_neighor_table_entry_t *) malloc(sizeof(mf_neighor_table_entry_t));
  //set the value of the neighbor entry
  //tmp->guid = 0x0002;
  //tmp->macaddr = 0x190e;

  //add entry into the neighbor Table
  //list_add_tail(&tmp->list, &neighbor_list_1);

  //if switch based on the mac address
  //TODO
  mf_lite_neighbor_table_p = &neighbor_list_1;
}

static void * _mf_lite_static_route_table_form(void *arg){
  //forming the neighbor_table
  _mf_lite_static_routing_neigbor_table_init();
  //TODO
  //_mf_lite_static_routing_routing_table_init();
  return NULL;
}

kernel_pid_t mf_lite_static_route_init(void){
  if (_pid == KERNEL_PID_UNDEF) {
    _pid = thread_create(_stack, sizeof(_stack), MF_STATIC_ROUTE_PRIO,
                          CREATE_STACKTEST, _mf_lite_static_route_table_form, NULL, "mf_static_route");
  }

  return _pid;
}

kernel_pid_t mf_lite_static_route_getpid(void){
  return _pid;
}
