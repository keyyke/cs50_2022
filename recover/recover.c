#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    int n_img = 0;
    char filename[8];
    BYTE buffer[512];
    FILE *img;

    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (n_img == 0)
            {
                sprintf(filename, "%03i.jpg", n_img);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }
                fwrite(buffer, sizeof(BYTE), 512, img);
                n_img++;
            }
            else if (n_img > 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", n_img);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, img);
                n_img++;
            }

        }
        else if (n_img > 0)
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }

    // Close files
    fclose(file);
    fclose(img);
}