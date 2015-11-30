/*
* Description: This file is the packet format of neighbor discovery advertisement packet
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/

#ifndef NEIGHBORDISCOVERY_NBD_ADV_HDR_H_
#define NEIGHBORDISCOVERY_NBD_ADV_HDR_H_
#endif

#include <stdint.h>
#include <timex.h>

/**
* @brief define the neighbor discovery advertisement header
*/
typedef struct __attribute__((packed)) {
	uint8_t versionType;
	uint16_t guid;
	timex_t lifetime;
	bool isnew;
} mf_nbd_adv_hdr_t;

//set version of neighbor discovery advertisement packet
static inline void mf_nbd_adv_hdr_setVersion(mf_nbd_adv_hdr_t *hdr, uint8_t version){
	//get the version out
	uint8_t type = hdr->versionType & 0x0f;
	version <<= 4;
	hdr->versionType = version | type;
}

//get version of neighbor discovery advertisement packet
static inline uint8_t mf_nbd_adv_hdr_getVersion(mf_nbd_adv_hdr_t *hdr){
	return hdr->versionType >> 4;
}

//set type of neighbor discovery advertisement packet
static inline void mf_nbd_adv_hdr_setType(mf_nbd_adv_hdr_t *hdr, uint8_t type){
	hdr->versionType &= 0xf0;
	hdr->versionType |= type;
}

//get type of neighbor discovery advertisement packet
static inline uint8_t mf_nbd_adv_hdr_getType(mf_nbd_adv_hdr_t *hdr){
	return hdr->versionType &= 0x0f;
}

static inline void mf_nbd_adv_hdr_init(mf_nbd_adv_hdr_t *hdr, uint8_t version, uint8_t type, uint16_t guid){
	timex_t time;
	mf_nbd_adv_hdr_setVersion(hdr, version);
	mf_nbd_adv_hdr_setType(hdr, type);
	hdr->guid = guid;
	hdr->lifetime = time;
	hdr->isnew = 1;
}

