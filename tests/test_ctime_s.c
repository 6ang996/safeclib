/*------------------------------------------------------------------
 * test_ctime_s
 * File 'os/ctime_s.c'
 * Lines executed:67.50% of 40
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_lib.h"

#if defined(_WIN32) && defined(HAVE_CTIME_S)
# define USE_MSVCRT
#endif

#ifdef USE_MSVCRT
#define ERR_MSVC(n, winerr)                        \
    if (rc != (winerr)) {                          \
        debug_printf("%s %u  Error rc=%d \n",      \
                     __FUNCTION__, __LINE__,  (int)rc); \
        errs++;                                    \
    }
#else
#define ERR_MSVC(n, winerr)                        \
    if (rc != (n)) {                               \
        debug_printf("%s %u  Error rc=%d \n",      \
                     __FUNCTION__, __LINE__,  (int)rc); \
        errs++;                                    \
    }
#endif

#define LEN   ( 128 )

static char   str1[LEN];

int test_ctime_s (void)
{
    errno_t rc;
    int errs = 0;
    time_t timer;

    timer = time(NULL);

/*--------------------------------------------------*/

    rc = ctime_s(NULL, 0, &timer);
    ERR_MSVC(ESNULLP,EINVAL);

    rc = ctime_s(str1, LEN, NULL);
    ERR_MSVC(ESNULLP,EINVAL);

/*--------------------------------------------------*/

    rc = ctime_s(str1, 25, &timer);
    ERR_MSVC(ESLEMIN,EINVAL);

    rc = ctime_s(str1, RSIZE_MAX_STR+1, &timer);
    ERR_MSVC(ESLEMAX,0);

/*--------------------------------------------------*/

    timer = 0;
    rc = ctime_s(str1, LEN, &timer);
    ERR(EOK);

    timer = -1;
    rc = ctime_s(str1, LEN, &timer);
    ERR_MSVC(ESLEMIN,EINVAL);

    {
        struct tm *tm = gmtime(&timer);
        memset(tm, 0, sizeof(struct tm));
#if SIZEOF_TIME_T < 8
        /* year 10000, ie 313392063599L would overflow on 32bit */
        timer = MAX_TIME_T_STR;
#else
        tm->tm_year = 10000;
        timer = mktime(tm);
        debug_printf("year 10000 = %ld\n", timer);
        timer++;
#endif
    }

    /* eg. 313360441200L */
    rc = ctime_s(str1, LEN, &timer);
#ifndef __MINGW32__
    ERR(ESLEMAX);
#else
    ERR(0);
#endif

/*--------------------------------------------------*/

    return (errs);
}

#ifndef __KERNEL__
/* simple hack to get this to work for both userspace and Linux kernel,
   until a better solution can be created. */
int main (void)
{
    return (test_ctime_s());
}
#endif
