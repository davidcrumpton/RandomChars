#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#define DEFAULT_LENGTH "80"
#define VERSION "1.1.0"

void printUsage(char *s)
{
        fprintf(stderr,"usage %s -b baseValue NumOfRandChars\n",s);
        fprintf(stderr,"usage %s -b 16 a\n",s);
        fprintf(stderr,"usage %s 100\n",s);
        fprintf(stderr,"    default number of random characters is %s\n", DEFAULT_LENGTH);
}

int
main (int argc, char **argv)
{
    char *cvalue = DEFAULT_LENGTH;
    int index;
    int getOptRetVal,base=0;
    long length = 0;
    char *endptr;


    opterr = 0;

    while ((getOptRetVal = getopt (argc, argv, "ab:")) != -1)
        switch (getOptRetVal)
        {
        case 'a':
            break;
        case 'b':
            base = atoi(optarg);
            break;
        case '?':
            if (optopt == 'b')
                 fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            printUsage(argv[0]);
            return 1;
        default:
            printUsage(argv[0]);
            abort ();
        }

    if(++optind == argc) {
	cvalue = argv[argc-1];
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
