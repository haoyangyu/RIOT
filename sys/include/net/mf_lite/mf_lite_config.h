
#ifndef MF_LITE_CONFIG_H_
#define MF_LITE_CONFIG_H_

#include <stdint.h>

typedef uint16_t mf_lite_short_guid_t;

typedef struct {
  char content[20];
} mf_lite_long_guid_t;

typedef uint16_t short_macaddr_t;
typedef uint64_t long_macaddr_t;

#endif
