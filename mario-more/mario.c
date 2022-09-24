#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number_of_spaces;
    int number_of_hashes;
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        number_of_spaces = height - i - 1;
        number_of_hashes = height - number_of_spaces;
        for (int j = 0; j < number_of_spaces; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < number_of_hashes; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < number_of_hashes; j++)
        {
            printf("#");
        }
        printf("\n");
    }

}