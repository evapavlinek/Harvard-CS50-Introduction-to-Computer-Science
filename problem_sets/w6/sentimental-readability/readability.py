from cs50 import get_string


text = get_string("Text: ")

letters = 0
words = 0
sentences = 0


# Count the number of letters and sentences
for c in text:
    if c.isalpha():
        letters += 1
    elif c in [".", "!", "?"]:
        sentences += 1

# Count the number of words
for word in text.split():
    words += 1


# Calculate the Coleman-Liau index
# L is the average number of letters per 100 words in the text
L = 100 * letters / words

# S is the average number of sentences per 100 words in the text
S = sentences / (words / 100)

CLindex = round(0.0588 * L - 0.296 * S - 15.8)

# Print the grade level
if CLindex < 0:
    print("Before Grade 1")
elif CLindex >= 16:
    print("Grade 16+")
else:
    print(f"Grade {CLindex}")
