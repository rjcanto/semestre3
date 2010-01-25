#include <stdio.h>
#include <string.h>
#include "myLib.h"

char *trim(char *str)
{
    int len = 0;
    char *frontp = str - 1;
    char *endp = NULL;

    if( str == NULL )
            return NULL;

    if( str[0] == '\0' )
            return str;

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address
     * the first non-whitespace characters from
     * each end.
     */
	while(*(++frontp)==' ');
	while(*(--endp)==' ' && endp!=frontp);

    if( str + len - 1 != endp )
            *(endp + 1) = '\0';
    else if( frontp != str &&  endp == frontp )
            *str = '\0';

    /* Shift the string so that it starts at str so
     * that if it's dynamically allocated, we can
     * still free it on the returned pointer.  Note
     * the reuse of endp to mean the front of the
     * string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) *endp++ = *frontp++;
            *endp = '\0';
    }


    return str;
}

int main(int argc, char *argv[])
{
    char *sample_strings[] =
    {
            "nothing to trim",
            "    trim the front",
            "trim the back     ",
            " trim one char front and back ",
            " trim one char front",
            "trim one char back ",
            "                   ",
            " ",
            "a",
            "",
            NULL
    };
    char test_buffer[64];
    int index;

    for( index = 0; sample_strings[index] != NULL; ++index )
    {
            strcpy( test_buffer, sample_strings[index] );
            printf("[%s] -> [%s]\n", sample_strings[index],
                                     trim(test_buffer));
    }

    /* The test prints the following:
    [nothing to trim] -> [nothing to trim]
    [    trim the front] -> [trim the front]
    [trim the back     ] -> [trim the back]
    [ trim one char front and back ] -> [trim one char front and back]
    [ trim one char front] -> [trim one char front]
    [trim one char back ] -> [trim one char back]
    [                   ] -> []
    [ ] -> []
    [a] -> [a]
    [] -> []
    */

    return 0;
}
