#include <stdio.h>

int
main(void)
{
    char buf[24];

    fgets(buf, 24, stdin);

    printf("Got: \"%s\"", buf);
}