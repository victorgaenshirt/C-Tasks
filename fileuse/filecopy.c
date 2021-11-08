#define _POSIX_C_SOURCE 1

#include <stdio.h> // fprintf, printf, stderr
#include <stdlib.h> // malloc, free
#include <stdint.h> // uint8_t, uintmax_t
#include <unistd.h> // read, write, close
#include <errno.h> // errno
#include <string.h> // strerror
#include <locale.h> // setlocale
#include <fcntl.h> // mode_t, O_RDONLY, O_WRONLY, O_CREAT, O_EXCL
#include <sys/stat.h> // struct stat, stat, S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH

int main(int argc, char *argv[])
{
    if (setlocale(LC_MESSAGES, "de_DE.UTF-8") == NULL)
    {
        fprintf(stderr, "Sprache fuer Systemmeldungen kann nicht auf Deutsch gesetzt werden\n");
        return 1;
    }

    if (argc != 3)
    {
        fprintf(stderr, "Aufruf: %s Quelle Ziel\n", argv[0]);
        return 1;
    }

    int in = open(argv[1], O_RDONLY);
    if (in == -1)
    {
        fprintf(stderr,
                "Quelle %s kann nicht geoeffnet werden (errno %d: %s)\n",
                argv[1], errno, strerror(errno));
        return 1;
    }

    const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int out = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, mode);
    if (out == -1)
    {
        fprintf(stderr,
                "Ziel %s kann nicht erzeugt werden (errno %d: %s)\n",
                argv[2], errno, strerror(errno));
        return 1;
    }

    struct stat sb = {0};
    if (fstat(in, &sb) == -1)
    {
        fprintf(stderr,
                "Attribute der Datei %s koennen nicht gelesen werden (errno %d: %s)\n",
                argv[1], errno, strerror(errno));

        return 1;
    };

    int bytesTotal = sb.st_size;
    unsigned char *buffer = malloc(sizeof(unsigned char) * bytesTotal);
    // uint8_t *buffer = malloc(sizeof(uint8_t) * bytesTotal);
    if (buffer == NULL)
    {
        fprintf(stderr, "Eingabepuffer kann nicht angelegt werden (errno %d: %s)\n", errno, strerror(errno));
        return 1;
    }

    int bytesToRead = bytesTotal;
    while (bytesToRead > 0)
    {
        int n = read(in, &buffer[bytesTotal - bytesToRead], bytesToRead);
        if (n < 0)
        {
            fprintf(stderr, "Lesefehler (errno %d: %s)\n", errno, strerror(errno));
            return 1;
        }
        bytesToRead -= n;
    }

    int bytesToWrite = bytesTotal;
    while (bytesToWrite > 0)
    {
        int m = write(out, &buffer[bytesTotal - bytesToWrite], bytesToWrite);
        if (m < 0)
        {
            fprintf(stderr, "Schreibfehler (errno %d: %s)\n", errno, strerror(errno));
            return 1;
        }
        bytesToWrite -= m;
    }

    free(buffer);
    close(out);
    close(in);

    return 0;
}
