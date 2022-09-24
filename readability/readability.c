#include <cs50.h>
#include <stdio.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    int cl;
    int cw;
    int cs;
    int score;
    double L;
    double S;
    double index;

    string text = get_string("TEXT:  ");
    cl = count_letters(text);
    cw = count_words(text);
    cs = count_sentences(text);

    L = 1.0 * cl / cw * 100;
    S = 1.0 * cs / cw * 100;
    index = 0.0588 * L - 0.296 * S - 15.8;
    score = (int) round(index);
    if (score < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (score < 16)
    {
        printf("Grade %d\n", score);
    }
    else
    {
        printf("Grade 16+\n");
    }
    return 0;
}

int count_letters(string text)
{
    int i;
    int n;

    n = 0;
    for (i = 0; text[i]; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            n++;
        }
    }
    return n;
}

int count_words(string text)
{
    int i;
    int n;

    n = 0;
    for (i = 0; text[i]; i++)
    {
        if (text[i] == ' ')
        {
            n++;
        }
    }
    n++;
    return n;
}

int count_sentences(string text)
{
    int i;
    int n;

    n = 0;
    for (i = 0; text[i]; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            n++;
        }
    }
    return n;
}