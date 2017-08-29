/*------------------------------------------------------------------
 * test_strispassword_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN 64


int main()
{
    bool rc;
    uint32_t len;
    char   str[LEN];
    int errs = 0;

/*--------------------------------------------------*/

    rc = strispassword_s(NULL, LEN);
    if (rc != false) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    rc = strispassword_s("", LEN);
    if (rc != false) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    rc = strispassword_s("Test4You&", 0);
    if (rc != false) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    rc = strispassword_s("Test4You&", 999);
    if (rc != false) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    rc = strispassword_s("", 9);
    if (rc != false) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy (str, "Test4You*123");
    len = 8;

    rc = strispassword_s(str, len);
    if (rc != false) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy (str, "Test4You*");
    len = strlen(str);

    rc = strispassword_s(str, len);
    if (rc != true) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy (str, "Test4You*Test4You*Test4You*");
    len = strlen(str);

    rc = strispassword_s(str, len);
    if (rc != true) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy (str, "Eest!22/");
    len = strlen(str);

    rc = strispassword_s(str, len);
    if (rc != false) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy (str, "pa$$W0rD");
    len = strlen(str);

    rc = strispassword_s(str, len);
    if (rc != true) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy (str, "Test");
    len = strlen(str);

    rc = strispassword_s(str, len);
    if (rc != false) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    return (errs);
}