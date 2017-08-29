/*------------------------------------------------------------------
 * test_strzero_s
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )


int main()
{
    errno_t rc;
    rsize_t max_len;
    char   str1[LEN];
    uint32_t i;
    int errs = 0;

/*--------------------------------------------------*/

    rc = strzero_s(NULL, 5);
    if (rc != ESNULLP) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    rc = strzero_s(str1, 0);
    if (rc != ESZEROL) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    rc = strzero_s(str1, RSIZE_MAX_STR+1);
    if (rc != ESLEMAX) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
/*--------------------------------------------------*/

    max_len = 1;
    rc = strzero_s(str1, max_len);
    if (rc != EOK) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
    for (i=0; i<max_len; i++) {
       if (str1[i] != '\0') {
           debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
           errs++;
       }
    }

/*--------------------------------------------------*/

    max_len = 2;
    rc = strzero_s(str1, max_len);
    if (rc != EOK) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
    for (i=0; i<max_len; i++) {
       if (str1[i] != '\0') {
           debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
           errs++;
       }
    }

/*--------------------------------------------------*/

    max_len = 3;
    rc = strzero_s(str1, max_len);
    if (rc != EOK) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
    for (i=0; i<max_len; i++) {
       if (str1[i] != '\0') {
           debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
           errs++;
       }
    }

/*--------------------------------------------------*/

    max_len = LEN;
    rc = strzero_s(str1, max_len);
    if (rc != EOK) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
    for (i=0; i<max_len; i++) {
       if (str1[i] != '\0') {
           debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
           errs++;
       }
    }

/*--------------------------------------------------*/

    strcpy(str1, "Now is the time for all data to be zeroed");
    max_len = strlen("Now is the ");

    rc = strzero_s(str1, max_len);
    if (rc != EOK) {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
    if (strcmp(&str1[max_len], "time for all data to be zeroed") ) {
        debug_printf("%s %u ERROR  --%s-- \n",
               __FUNCTION__, __LINE__,
               &str1[max_len]);
        errs++;
    }
/*--------------------------------------------------*/


    return (errs);
}