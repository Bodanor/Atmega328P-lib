#include "../include/utils.h"


static int strtest(char *s)
{
    int i = 0;
    while (*s++ != '\0')
        i++;
    return i;
}

static void reverse(char *s)
{
    int i, j;
    char c;
 
    for (i = 0, j = strtest(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }

}

void itoa(unsigned int n, char *s)
 {
     int i;
     i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
     s[i] = '\0';
    reverse(s);
 }