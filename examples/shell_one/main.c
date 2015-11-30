#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"
#include "shell_commands.h"

#if FEATURE_PERIPH_RTC
#include "periph/rtc.h"
#endif

#ifdef MODULE_NETIF
#include "net/gnrc/pktdump.h"
#include "net/gnrc.h"
#endif

int main(void)
{
#ifdef FEATURE_PERIPH_RTC
    rtc_init();
#endif

#ifdef MODULE_NETIF
    gnrc_netreg_entry_t dump;
    dump.pid = gnrc_pktdump_getpid();
    dump.demux_ctx = GNRC_NETREG_DEMUX_CTX_ALL;
    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);
#endif
    (void) puts("Welcome to RIOT!");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
	//Haoyang   
	//(void) puts(line_buf);
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
