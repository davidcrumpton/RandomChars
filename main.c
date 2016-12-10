#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#define DEFAULT_LENGTH "80"

int
main (int argc, char **argv)
{
    int aflag = 0;
    int bflag = 0;
    char *cvalue = DEFAULT_LENGTH;
    int index;
    int c,base;
    long length = 0;
    char *endptr;


    opterr = 0;

    while ((c = getopt (argc, argv, "ab:c:")) != -1)
        switch (c)
        {
        case 'a':
            aflag = 1;
            break;
        case 'b':
            bflag = 1;
            base = atoi(optarg);
            break;
        case 'c':
            cvalue = optarg;
            break;
        case '?':
            if (optopt == 'c')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (optopt == 'b')
                 fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
        }

    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);

    errno = 0;    /* To distinguish success/failure after call */
    length = strtol(cvalue, &endptr, base);

    if ((errno == ERANGE && (length == LONG_MAX || length == LONG_MIN))
            || (errno != 0 && length == 0))
    {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endptr == cvalue)
    {
        fprintf(stderr, "No digits were found\n");
        exit(EXIT_FAILURE);
    }

    /* Seed number for rand() */
    srand((unsigned int) time(0));

    /* ASCII characters 33 to 126 */
    while(length--)
    {
        putchar(rand() % 94 + 33);
    }

    printf("\n");

    return EXIT_SUCCESS;
}
