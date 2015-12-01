
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

//Start the packet dump thread and listening for incoming packets
kernel_pid_t mf_lite_static_route_init(void);



#endif
