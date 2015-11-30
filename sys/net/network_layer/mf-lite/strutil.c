/*
* Description: This file is for providing utilities for string operation
* Author: Haoyang Yu <haoyang.yu@rutgers.edu>
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "net/mf-lite/strutil.h"

bool str_to_uint16(char *str, uint16_t *res){
	char *end;
	errno = 0;
	long val = strtol(str, &end, 10);
	if (errno == ERANGE || val < 0 || val > 0x10000 || end == str || *end != '\0'){
		return false;
	}
	*res = (uint16_t)val;
	return true;
}
