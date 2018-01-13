/*------------------------------------------------------------------
 * test_fwprintf_s
 * File 'wchar/fwprintf_s.c'
 * Lines executed:82.35% of 17
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"
#include <unistd.h>

#define TMP   "tmpfwp"
#define LEN   ( 128 )

static FILE* out;
static wchar_t   wstr[LEN];
static char      str[LEN];

int test_fwprintf_s (void)
{
    errno_t rc;
    int32_t ind;
    int errs = 0;

    out = fopen(TMP, "w");

/*--------------------------------------------------*/

    rc = fwprintf_s(out, NULL, NULL);
    NEGERR(ESNULLP)

/*--------------------------------------------------*/

    wstr[0] = L'\0';
    rc = fwprintf_s(out, L"%s%n\n", wstr, &ind);
    NEGERR(EINVAL)

    if (!out) {
        printf("Failed to open file %s for write: %s\n",
               TMP, strerror(errno));
        return errs;
    }

/*--------------------------------------------------*/

    rc = fwprintf_s(out, L"%s%%n\n", wstr);
    ERR(3)

    rc = fwprintf_s(out, L"%%n\n");
    ERR(3);

/*--------------------------------------------------*/

    /* TODO
    rc = fwprintf_s(out, L"%s", NULL);
    NEGERR(ESNULLP)
    */

/*--------------------------------------------------*/

    wcscpy(wstr, L"12");
    strcpy(str, "34");

    rc = fwprintf_s(out, L"%ls%s", wstr, str);
    ERRWCHAR(4)

/*--------------------------------------------------*/
    fclose(out);
    unlink(TMP);

    return (errs);
}

#ifndef __KERNEL__
/* simple hack to get this to work for both userspace and Linux kernel,
   until a better solution can be created. */
int main (void)
{
    return (test_fwprintf_s());
}
#endif
