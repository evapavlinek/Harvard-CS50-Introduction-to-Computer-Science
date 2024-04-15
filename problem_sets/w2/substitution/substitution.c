#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool keyArgumentCalled(int argc);
bool keyValidation(string key);
void textEncryption(string text, string key);

int main(int argc, string argv[])
{
    // check whether the program was executed with only the key argument
    if (!keyArgumentCalled(argc))
    {
        return 1;
    }

    // check whether the key is valid (case-insensitive)
    string key = argv[1];
    if (!keyValidation(key))
    {
        return 1;
    }

    // promt the user for the plain text
    const string text = get_string("plaintext: ");

    // encrypt and print the text
    textEncryption(text, key);
}

bool keyArgumentCalled(int argc)
{
    if (argc == 1)
    {
        printf("Missing command-line argument 'key'!\n");
        return false;
    }
    else if (argc > 2)
    {
        printf("Execute the program only with the key argument containing 26 characters!\n");
        return false;
    }
    return true;
}

bool keyValidation(string key)
{
    if (strlen(key) != 26)
    {
        printf("The key should contain exactly 26 characters!\n");
        return false;
    }
    for (int currentLetter = 0; currentLetter < 26; currentLetter++)
    {
        if (!isalpha(key[currentLetter]))
        {
            printf("All key characters should be alphabetic characters!\n");
            return false;
        }
        for (int previousLetters = 0; currentLetter > 0 && previousLetters < currentLetter;
             previousLetters++)
        {
            if (key[currentLetter] == key[previousLetters])
            {
                printf("All key characters should be unique characters!\n");
                return false;
            }
        }
    }
    return true;
}

void textEncryption(string text, string key)
{
    printf("ciphertext: ");
    for (int textCharIndex = 0, textLen = strlen(text); textCharIndex < textLen; textCharIndex++)
    {
        if ((text[textCharIndex] >= 'A' && text[textCharIndex] <= 'Z') ||
            (text[textCharIndex] >= 'a' && text[textCharIndex] <= 'z'))
        {
            if (isupper(text[textCharIndex]))
            {
                printf("%c", toupper(key[text[textCharIndex] - 65]));
            }
            else
            {
                printf("%c", tolower(key[text[textCharIndex] - 97]));
            }
        }
        else
        {
            printf("%c", text[textCharIndex]);
        }
    }
    printf("\n");
}
