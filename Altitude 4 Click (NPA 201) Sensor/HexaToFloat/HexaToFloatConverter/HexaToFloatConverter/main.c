#include <stdio.h>
#include "string.h"

int main() {

    FILE* filepoint;
    errno_t err;

    char fileName[] = "output.txt";

    char buff[9];
    int resultCounter = 0;

    float f = 0;
    char b[4];
    char hex[2];

    if ((err = fopen_s(&filepoint, fileName, "r")) != 0) {
        fprintf(stderr, "cannot open file '%s': %s\n", fileName, strerror(err));
    }
    else {
       
        while (fgets(buff, 9, (FILE*)filepoint)) {

            for (size_t i = 0; i < 4; i++)
            {
                hex[0] = buff[i * 2];
                hex[1] = buff[i * 2 + 1];

                b[i] = (char)strtol(hex, NULL, 16);
            }

            memcpy(&f, &b, sizeof(f));

            printf("%s %f\n", buff, f);

            resultCounter++;
        }

        fclose(filepoint);

        printf("\nBroj merenja: %d\n", resultCounter);
    }

    
    return 0;
}

/*
    Sustina sastavljanja floata iz 4 bajta:

    float f;
    char b[] = {0xA3, 0x6c, 0x79, 0x44};

    memcpy(&f, &b, sizeof(f));

    printf("%f", f);
*/