#include <cs50.h>
#include <stdio.h>

const int ALPHABETS_COUNT = 26;

int main(int argc, string argv[])
{
    int str_len;
    int i;
    int alphabets[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char n;

    // Error handling
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    for (i = 0; argv[1][i]; i++)
    {
        // Change keystring into uppercase and check are they only alphabets
        if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
        {
            argv[1][i] += 'A' - 'a';
        }
    }
    str_len = i;
    if (str_len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Check key
    for (i = 0; argv[1][i]; i++)
    {
        if (!(argv[1][i] >= 'A' && argv[1][i] <= 'Z'))
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        if (alphabets[argv[1][i] - 'A'] == 0)
        {
            alphabets[argv[1][i] - 'A'] = 1;
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    for (i = 0; i < ALPHABETS_COUNT; i++)
    {
        if (alphabets[i] == 0)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    // Get input words from both players
    string plain = get_string("plaintext:  ");

    // Encryption
    printf("ciphertext: ");
    for (i = 0; plain[i]; i++)
    {
        if (plain[i] >= 'a' && plain[i] <= 'z')
        {
            printf("%c", argv[1][plain[i] - 'a'] + ('a' - 'A'));
        }
        else if (plain[i] >= 'A' && plain[i] <= 'Z')
        {
            printf("%c", argv[1][plain[i] - 'A']);
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
    return 0;
}