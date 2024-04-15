// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string s);

int main(int argc, string argv[])
{
    // validate that the program was executed correctly
    if (argc != 2)
    {
        printf("Execute the program with a single word that should be converted as an argument!\n");
        return 1;
    }

    // replace the vowels in the input and print the converted output
    printf("%s\n", replace(argv[1]));
}

string replace(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        switch (s[i])
        {
            case 'a':
                s[i] = '6';
                break;

            case 'e':
                s[i] = '3';
                break;

            case 'i':
                s[i] = '1';
                break;

            case 'o':
                s[i] = '0';
                break;
        }
    }
    return s;
}
