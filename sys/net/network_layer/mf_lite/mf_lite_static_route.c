/*
* Description: This file is for initial a process(thread) for static routing
* that
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
* Revised: Jiachen Chen <jiachen@winlab.rutgers.edu>
*/
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "thread.h"
//#include "msg.h"
#include "kernel.h"

//for NETIF
#include "net/gnrc/netif.h"
#include "net/gnrc/netapi.h"
#include "net/gnrc/netif/hdr.h"
#include "net/netopt.h"

#include "net/mf_lite/mf_lite_neighbor.h"
#include "net/mf_lite/mf_lite_route.h"
#include "net/mf_lite/mf_lite_static_route.h"

// PID of the mf_lite_static_route id
static kernel_pid_t _pid = KERNEL_PID_UNDEF;
// stack for the pktdump thread
static char _stack[MF_STATIC_ROUTE_STACKSIZE];

#define MAX_ADDR_LEN            (8U)

//mf_neighor_table_entry_t neighbor_list;
list_head_t neighbor_list_1;
list_head_t neighbor_list_2;
list_head_t neighbor_list_3;
list_head_t neighbor_list_4;

list_head_t routing_list_1;
list_head_t routing_list_2;
list_head_t routing_list_3;
list_head_t routing_list_4;

//static function to get the default mac address of the board
static short_macaddr_t _get_default_macaddr(void){
  kernel_pid_t ifs[GNRC_NETIF_NUMOF];
  short_macaddr_t macaddr = 0;
  //ifs get the kernel pid of ALL interfaces
  //number should be 1, ifs[0] contains the kpid of 15.4 network interface
  size_t number = gnrc_netif_get(ifs);
  if (number == 1) {
    uint8_t hwaddr[MAX_ADDR_LEN];
    int res = gnrc_netapi_get(ifs[0], NETOPT_ADDRESS, 0, hwaddr, sizeof(hwaddr));
    //res = value returned by the GNRC_NETAPI_MSG_TYPE_ACK message
    //GNRC_NETAPI_MSG_TYPE_ACK message: get and set option messages
    //res == 2
    if (res >= 0) {
      macaddr = hwaddr[0] << 8 | hwaddr[1];
    }
  }
  return macaddr;
}

//initial the mf_neighbor table for every node
static void _mf_lite_static_routing_neigbor_table_init(void){
  //initial the static 4 neighbor lists
  INIT_LIST_HEAD(&neighbor_list_1);
  INIT_LIST_HEAD(&neighbor_list_2);
  INIT_LIST_HEAD(&neighbor_list_3);
  INIT_LIST_HEAD(&neighbor_list_4);

  mf_lite_neighbor_table_p = &neighbor_list_1;
  mf_lite_neighbor_add_tail(0x0002, 0x190e);

  mf_lite_neighbor_table_p = &neighbor_list_2;
  mf_lite_neighbor_add_tail(0x0001, 0x3ca2);
  mf_lite_neighbor_add_tail(0x0003, 0x9cda);

  mf_lite_neighbor_table_p = &neighbor_list_3;
  mf_lite_neighbor_add_tail(0x0002, 0x190e);
  mf_lite_neighbor_add_tail(0x0004, 0x2fb2);

  mf_lite_neighbor_table_p = &neighbor_list_4;
  mf_lite_neighbor_add_tail(0x0003, 0x9cda);

  //if switch based on the mac address
  short_macaddr_t macaddr = _get_default_macaddr();
  switch(macaddr){
    case 0x3ca2:
      mf_lite_neighbor_table_p = &neighbor_list_1;
      break;
    case 0x190e:
      mf_lite_neighbor_table_p = &neighbor_list_2;
      break;
    case 0x9cda:
      mf_lite_neighbor_table_p = &neighbor_list_3;
      break;
    case 0x2fb6:
      mf_lite_neighbor_table_p = &neighbor_list_4;
      break;
    default:
      break;
  }
}

static void _mf_lite_static_routing_routing_table_init(void){
  //initial the static 4 routing lists
  INIT_LIST_HEAD(&routing_list_1);
  INIT_LIST_HEAD(&routing_list_2);
  INIT_LIST_HEAD(&routing_list_3);
  INIT_LIST_HEAD(&routing_list_4);

  mf_lite_routing_table_p = &routing_list_1;
  mf_lite_route_add_tail(2,2);
  mf_lite_route_add_tail(3,2);
  mf_lite_route_add_tail(4,2);

  mf_lite_routing_table_p = &routing_list_2;
  mf_lite_route_add_tail(1,1);
  mf_lite_route_add_tail(3,3);
  mf_lite_route_add_tail(4,3);

  mf_lite_routing_table_p = &routing_list_3;
  mf_lite_route_add_tail(1,2);
  mf_lite_route_add_tail(2,2);
  mf_lite_route_add_tail(4,4);

  mf_lite_routing_table_p = &routing_list_4;
  mf_lite_route_add_tail(1,3);
  mf_lite_route_add_tail(2,3);
  mf_lite_route_add_tail(3,3);

  //Based on mac for the board to choose which list to follow
  short_macaddr_t macaddr = _get_default_macaddr();
  switch(macaddr){
    case 0x3ca2:
      mf_lite_routing_table_p = &routing_list_1;
      break;
    case 0x190e:
      mf_lite_routing_table_p = &routing_list_2;
      break;
    case 0x9cda:
      mf_lite_routing_table_p = &routing_list_3;
      break;
    case 0x2fb6:
      mf_lite_routing_table_p = &routing_list_4;
      break;
    default:
      break;
  }
}

static void * _mf_lite_static_route_table_form(void *arg){
  //forming the neighbor table
  _mf_lite_static_routing_neigbor_table_init();
  //forming the routing table
  _mf_lite_static_routing_routing_table_init();
  return NULL;
}

kernel_pid_t mf_lite_static_route_init(void){
  _mf_lite_static_routing_neigbor_table_init();
  _mf_lite_static_routing_routing_table_init();
 if (_pid != KERNEL_PID_UNDEF) {
    _pid = thread_create(_stack, sizeof(_stack), MF_STATIC_ROUTE_PRIO,
                          CREATE_STACKTEST, _mf_lite_static_route_table_form, NULL, "mf_static_route");
  }
  return _pid;
}

kernel_pid_t mf_lite_static_route_getpid(void){
  return _pid;
}
