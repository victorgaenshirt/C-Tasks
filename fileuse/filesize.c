#define _POSIX_C_SOURCE 1

#include <stdio.h> // fprintf, printf, stderr
#include <stdint.h> // uint8_t, uintmax_t
#include <inttypes.h> // PRIuMAX
#include <unistd.h> // read, STDIN_FILENO
#include <errno.h> // errno
#include <string.h> // strerror
#include <locale.h> // setlocale
#include <sys/stat.h> // struct stat, stat

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    if (argc < 2)
    {
        // unsigned chat buffer = 0;
        uint8_t buffer = 0;
        uintmax_t size = 0;
        int n;

        while ((n = read(STDIN_FILENO, &buffer, 1)) > 0)
        {
            size++;
        }

        if (n == -1)
        {
            fprintf(stderr,
                    "Fehler beim Einlesen der Eingabe (errno %d: %s)\n", errno, strerror(errno));
            return 1;
        }
        else
        {
            printf("Standardeingabe: %"PRIuMAX" Byte\n", size);
        }
    }
    else
    {
        struct stat sb = {0};

        for (int i = 1; i < argc; ++i)
        {
            if (stat(argv[i], &sb) == -1)
            {
                fprintf(stderr,
                        "Attribute der Datei %s koennen nicht gelesen werden (errno %d: %s)\n",
                        argv[i], errno, strerror(errno));
                continue;
            }
            else
            {
                printf("%s: %"PRIuMAX" Byte\n", argv[i], sb.st_size);
            }
        }
    }

    return 0;
}
