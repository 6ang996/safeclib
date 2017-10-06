/*------------------------------------------------------------------
 * test_wcsupr_s
 * File 'wcsupr_s.c'
 * Lines executed:100.00% of 14
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )

int main()
{
    errno_t rc;
    rsize_t len;
    wchar_t str[LEN];
    int errs = 0;

/*--------------------------------------------------*/

    rc = wcsupr_s(NULL, 5);
    ERR(ESNULLP)

/*--------------------------------------------------*/

    wcscpy(str, L"test");
    rc = wcsupr_s(str, 0);
#ifdef HAVE_C11
    ERR(EOK);
#else
    ERR(ESZEROL)
#endif
    WEXPSTR(str, L"test");

/*--------------------------------------------------*/

    wcscpy(str, L"test");
    rc = wcsupr_s(str, 99999);
    ERR(ESLEMAX)
    WEXPSTR(str, L"test");

/*--------------------------------------------------*/

    wcscpy(str, L"n");
    len = wcslen(str);

    rc = wcsupr_s(str, len);
    ERR(EOK);
    WEXPSTR(str, L"N");

/*--------------------------------------------------*/

    wcscpy(str, L"N");
    len = wcslen(str);

    rc = wcsupr_s(str, len);
    ERR(EOK)
    WEXPSTR(str, L"N");

/*--------------------------------------------------*/

    wcscpy(str, L"nowisthetim3");

    rc = wcsupr_s(str, 25);
    ERR(EOK)
    WEXPSTR(str, L"NOWISTHETIM3");

/*--------------------------------------------------*/

    wcscpy(str, L"nowisthetime");
    len = wcslen(str);

    rc = wcsupr_s(str, len);
    ERR(EOK)
    WEXPSTR(str, L"NOWISTHETIME");

/*--------------------------------------------------*/

    wcscpy(str, L"qqeRo");
    len = wcslen(str);

    rc = wcsupr_s(str, len);
    ERR(EOK)
    WEXPSTR(str, L"QQERO");

/*--------------------------------------------------*/

    wcscpy(str, L"1234");
    len = wcslen(str);

    rc = wcsupr_s(str, 4);
    ERR(EOK)
    WEXPSTR(str, L"1234");

/*--------------------------------------------------*/

    return (errs);
}
