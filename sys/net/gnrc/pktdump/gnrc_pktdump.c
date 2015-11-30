/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     net_pktdump
 * @{
 *
 * @file
 * @brief       Generic module to dump packages received via netapi to STDOUT
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <inttypes.h>
#include <stdio.h>

#include <errno.h>
#include "byteorder.h"
#include "thread.h"
#include "msg.h"
#include "kernel.h"
#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"
#include "net/ipv6/addr.h"
#include "net/ipv6/hdr.h"
#include "net/udp.h"
#include "net/sixlowpan.h"
#include "od.h"

/*haoyang: header*/
#include "thread.h"
#include "net/gnrc/ipv6/netif.h"
#include "net/gnrc/netif.h"
#include "net/gnrc/netapi.h"
#include "net/netopt.h"
#include "net/gnrc/pkt.h"
#include "net/gnrc/pktbuf.h"
#include "net/gnrc/netif/hdr.h"
#include "net/gnrc/sixlowpan/netif.h"
/*haoyang: declaration*/
/**
 * @brief   The maximal expected link layer address length in byte
 */
#define MAX_ADDR_LEN            (8U)

int _netif_send_echo_(void);
void _ack_back(gnrc_netif_hdr_t *hdr);
/**
 * @brief   PID of the pktdump thread
 */
static kernel_pid_t _pid = KERNEL_PID_UNDEF;

/**
 * @brief   Stack for the pktdump thread
 */
static char _stack[GNRC_PKTDUMP_STACKSIZE];

static void _dump_snip(gnrc_pktsnip_t *pkt)
{
    switch (pkt->type) {
        case GNRC_NETTYPE_UNDEF:
            printf("NETTYPE_UNDEF (%i)\n", pkt->type);
            od_hex_dump(pkt->data, pkt->size, OD_WIDTH_DEFAULT);
            break;
#ifdef MODULE_GNRC_NETIF
        case GNRC_NETTYPE_NETIF:
            printf("NETTYPE_NETIF (%i)\n", pkt->type);
            gnrc_netif_hdr_print(pkt->data);
            break;
#endif
#ifdef MODULE_GNRC_SIXLOWPAN
        case GNRC_NETTYPE_SIXLOWPAN:
            printf("NETTYPE_SIXLOWPAN (%i)\n", pkt->type);
            sixlowpan_print(pkt->data, pkt->size);
            break;
#endif
#ifdef MODULE_GNRC_IPV6
        case GNRC_NETTYPE_IPV6:
            printf("NETTYPE_IPV6 (%i)\n", pkt->type);
            ipv6_hdr_print(pkt->data);
            break;
#endif
#ifdef MODULE_GNRC_ICMPV6
        case GNRC_NETTYPE_ICMPV6:
            printf("NETTYPE_ICMPV6 (%i)\n", pkt->type);
            break;
#endif
#ifdef MODULE_GNRC_TCP
        case GNRC_NETTYPE_TCP:
            printf("NETTYPE_TCP (%i)\n", pkt->type);
            break;
#endif
#ifdef MODULE_GNRC_UDP
        case GNRC_NETTYPE_UDP:
            printf("NETTYPE_UDP (%i)\n", pkt->type);
            udp_hdr_print(pkt->data);
            break;
#endif
#ifdef TEST_SUITES
        case GNRC_NETTYPE_TEST:
            printf("NETTYPE_TEST (%i)\n", pkt->type);
            od_hex_dump(pkt->data, pkt->size, OD_WIDTH_DEFAULT);
            break;
#endif
        default:
            printf("NETTYPE_UNKNOWN (%i)\n", pkt->type);
            od_hex_dump(pkt->data, pkt->size, OD_WIDTH_DEFAULT);
            break;
    }
}

static void _dump(gnrc_pktsnip_t *pkt)
{
    int snips = 0;
    int size = 0;
    gnrc_pktsnip_t *snip = pkt;
    
    while (snip != NULL) {
        printf("~~ SNIP %2i - size: %3u byte, type: ", snips,
               (unsigned int)snip->size);
        _dump_snip(snip);
        
        ++snips;
        size += snip->size;
        snip = snip->next;
    }

    printf("~~ PKT    - %2i snips, total size: %3i byte\n", snips, size);
    gnrc_pktbuf_release(pkt);
    
}

static void *_eventloop(void *arg)
{
    (void)arg;
    msg_t msg, reply;
    msg_t msg_queue[GNRC_PKTDUMP_MSG_QUEUE_SIZE];

    /* setup the message queue */
    msg_init_queue(msg_queue, GNRC_PKTDUMP_MSG_QUEUE_SIZE);

    reply.content.value = (uint32_t)(-ENOTSUP);
    reply.type = GNRC_NETAPI_MSG_TYPE_ACK;

    while (1) {
        msg_receive(&msg);

        switch (msg.type) {
            case GNRC_NETAPI_MSG_TYPE_RCV:
                puts("PKTDUMP: data received:");
                _dump((gnrc_pktsnip_t *)msg.content.ptr);
                break;
            case GNRC_NETAPI_MSG_TYPE_SND:
                puts("PKTDUMP: data to send:");
                _dump((gnrc_pktsnip_t *)msg.content.ptr);
                break;
            case GNRC_NETAPI_MSG_TYPE_GET:
            case GNRC_NETAPI_MSG_TYPE_SET:
                msg_reply(&msg, &reply);
                break;
            default:
                puts("PKTDUMP: received something unexpected");
                break;
        }
    }

    /* never reached */
    return NULL;
}

kernel_pid_t gnrc_pktdump_getpid(void)
{
    return _pid;
}

kernel_pid_t gnrc_pktdump_init(void)
{
    if (_pid == KERNEL_PID_UNDEF) {
        _pid = thread_create(_stack, sizeof(_stack), GNRC_PKTDUMP_PRIO,
                             CREATE_STACKTEST, _eventloop, NULL, "pktdump");
    }
    return _pid;
}


//haoyang: for send ack back
/* shell commands */
int _netif_send_echo_(void)
{
    //kernel_pid_t dev;
    uint8_t addr[MAX_ADDR_LEN];
    size_t addr_len;
    gnrc_pktsnip_t *pkt;
    gnrc_netif_hdr_t *nethdr;
    uint8_t flags = 0x00;
    //Broadcast
    flags |= GNRC_NETIF_HDR_FLAGS_BROADCAST;
    
    addr_len = 0;
    
    /* put packet together */
    pkt = gnrc_pktbuf_add(NULL, "ack", strlen("ack"), GNRC_NETTYPE_UNDEF);
    pkt = gnrc_pktbuf_add(pkt, NULL, sizeof(gnrc_netif_hdr_t) + addr_len,
                          GNRC_NETTYPE_NETIF);
    /* haoyang: get the header data of the packet -- the eth address*/
    nethdr = (gnrc_netif_hdr_t *)pkt->data;
    /* haoyang: Initialize the header and set the destination address*/
    gnrc_netif_hdr_init(nethdr, 0, addr_len);
    gnrc_netif_hdr_set_dst_addr(nethdr, addr, addr_len);
    nethdr->flags = flags;
    /* and send it */
    if (gnrc_netapi_send(4, pkt) < 1) {
        puts("error: unable to send\n");
        gnrc_pktbuf_release(pkt);
        return 1;
    }
    
    return 0;
}

/*haoyang: ack-back*/
void _ack_back(gnrc_netif_hdr_t *hdr){
    char addr_str[GNRC_NETIF_HDR_L2ADDR_MAX_LEN];
    char *source_address = NULL;
    if (hdr->src_l2addr_len > 0) {
        source_address = gnrc_netif_addr_to_str(addr_str, sizeof(addr_str),gnrc_netif_hdr_get_src_addr(hdr),(size_t)hdr->src_l2addr_len);
    }
    /*haoyang: send the acknowledge packet back*/
    gnrc_netif_hdr_t *nethdr;
    uint8_t addr[MAX_ADDR_LEN];
    size_t addr_len;
    uint8_t flags = 0x00;
    
    /* haoyang: parse the source address to get the destination address of ack*/
    /* haoyang: addr stores the host address*/
    addr_len = gnrc_netif_addr_from_str(addr, sizeof(addr), source_address);
    
    /*haoyang: form packet snip "ack" to send*/
    gnrc_pktsnip_t *_pkt;
    
    _pkt = gnrc_pktbuf_add(NULL, "ack", strlen("ack"), GNRC_NETTYPE_UNDEF);
    _pkt = gnrc_pktbuf_add(_pkt, NULL, sizeof(gnrc_netif_hdr_t) + addr_len,
                           GNRC_NETTYPE_NETIF);
    
    nethdr = (gnrc_netif_hdr_t *)_pkt->data;
    gnrc_netif_hdr_init(nethdr, 0, addr_len);
    gnrc_netif_hdr_set_dst_addr(nethdr, addr, addr_len);
    nethdr->flags = flags;
    /* and send it */
    if (gnrc_netapi_send(4, _pkt) < 1) {
        puts("error: unable to send\n");
        //gnrc_pktbuf_release(pkt);
    }

    
}
