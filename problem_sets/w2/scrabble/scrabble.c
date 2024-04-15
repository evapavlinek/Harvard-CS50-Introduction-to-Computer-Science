#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string inputWord(int player);
int calculateScore(string s);

int main(void)
{
    // aks the players for their words
    string p1 = inputWord(1);
    string p2 = inputWord(2);

    // calculate the scores of the words
    int s1 = calculateScore(p1);
    int s2 = calculateScore(p2);

    // compare the scores and determine the winner/tie
    if (s1 > s2)
    {
        printf("Player 1 wins!\n");
    }
    else if (s2 > s1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

string inputWord(int player)
{
    string word = get_string("Player %i: ", player);
    return word;
}

int calculateScore(string s)
{
    int score = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        int letter = toupper(s[i]);
        if (letter >= 'A' && letter <= 'Z')
        {
            if (letter == 'D' || letter == 'G')
            {
                score += 2;
            }
            else if (letter == 'B' || letter == 'C' || letter == 'M' || letter == 'P')
            {
                score += 3;
            }
            else if (letter == 'F' || letter == 'H' || letter == 'V' || letter == 'W' ||
                     letter == 'Y')
            {
                score += 4;
            }
            else if (letter == 'K')
            {
                score += 5;
            }
            else if (letter == 'J' || letter == 'X')
            {
                score += 8;
            }
            else if (letter == 'Q' || letter == 'Z')
            {
                score += 10;
            }
            else
            {
                score += 1;
            }
        }
    }

    return score;
}
