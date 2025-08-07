#include "delay.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* get system time */
void itimeofday(long *sec, long *usec)
{
#if defined(__unix)
    struct timeval time;
    gettimeofday(&time, NULL);
    if (sec)
        *sec = time.tv_sec;
    if (usec)
        *usec = time.tv_usec;
#else
    static long mode = 0, addsec = 0;
    int retval;
    static int64_t freq = 1;
    int64_t qpc;
    if (mode == 0)
    {
        retval = QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
        freq   = (freq == 0) ? 1 : freq;
        retval = QueryPerformanceCounter((LARGE_INTEGER *)&qpc);
        addsec = (long)time(NULL);
        addsec = addsec - (long)((qpc / freq) & 0x7fffffff);
        mode   = 1;
    }
    retval = QueryPerformanceCounter((LARGE_INTEGER *)&qpc);
    retval = retval * 2;
    if (sec)
        *sec = (long)(qpc / freq) + addsec;
    if (usec)
        *usec = (long)((qpc % freq) * 1000000 / freq);
#endif
}

/* get clock in millisecond 64 */
int64_t iclock64(void)
{
    long s, u;
    int64_t value;
    itimeofday(&s, &u);
    value = ((int64_t)s) * 1000 + (u / 1000);
    return value;
}

uint32_t iclock()
{
    return (uint32_t)(iclock64() & 0xfffffffful);
}

inline t_delay_obj *delay_new()
{
    t_delay_obj *obj = (t_delay_obj *)malloc(sizeof(t_delay_obj));
    if (!obj)
    {
        return NULL;
    }
    obj->seqno     = 0;
    obj->send_time = 0;
    obj->recv_time = 0;
    return obj;
}
