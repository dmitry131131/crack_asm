#include <stdio.h>

#include "crack.h"

int main()
{
    if (cracker("CRACKME.COM"))
    {
        printf("Error in hacking process!\n");
    }

    printf("Programm hacked!\n");

    return 0;
}