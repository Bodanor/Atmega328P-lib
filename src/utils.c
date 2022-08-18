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

int itoa(unsigned long val, char *buffer)
{
    int i = 0;
    while ((val % 10) != 0)
    {
        buffer[i++] = (val%10) + 48;
        val /= 10;
    }
    buffer[i] = '\0';
    reverse(buffer);

}