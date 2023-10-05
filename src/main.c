
#include <stdio.h>

#include "error.h"

int
main ( int ac, char **av)
{
    (void)av;
    if (ac != 2)
    {
        show_usage("invalid number of argument.");
        return (1);
    }
    return (0);
}
