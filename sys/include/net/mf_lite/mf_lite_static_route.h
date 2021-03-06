/*
* Description: This file is for header file for static routing
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
* Revised: Jiachen Chen <jiachen@winlab.rutgers.edu>
*/

#ifndef MF_LITE_STATIC_ROUTE_H
#define MF_LITE_STATIC_ROUTE_H

#include "kernel.h"
/**
 * @brief   Priority of the pktdump thread
 */
#define MF_STATIC_ROUTE_PRIO               (THREAD_PRIORITY_MAIN - 1)

/**
 * @brief   Stack size used for the pktdump thread
 */
#define MF_STATIC_ROUTE_STACKSIZE          (THREAD_STACKSIZE_MAIN)

//Get the PID of the static_route thread
kernel_pid_t mf_lite_static_route_getpid(void);

//start the static route & neighbor table initialization
//kernel_pid_t mf_lite_static_route_init(void);
void mf_lite_static_route_init(void);

#endif
