#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int computeGrade(string s);
void calculateGrade(int index);

int main(void)
{
    // prompt the user for the text
    string text = get_string("Text: ");

    // compute the text grade based on the Coleman-Liau index
    int index = computeGrade(text);

    // print the grade
    calculateGrade(index);
}

int computeGrade(string s)
{
    int words = 0;
    int letters = 0;
    int sentences = 0;

    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        if (isspace(s[i]) || s[i] == '\0')
        {
            words++;
        }
        else if (isalpha(s[i]))
        {
            letters++;
        }
        else if ((s[i] == '.' || s[i] == '!' || s[i] == '?') &&
                 (i > 0 && s[i - 1] != '!' && s[i - 1] != '?'))
        {
            sentences++;
        }
    }

    float L = letters / (words / 100.0);
    float S = sentences / (words / 100.0);

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}

void calculateGrade(int index)
{
    if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
