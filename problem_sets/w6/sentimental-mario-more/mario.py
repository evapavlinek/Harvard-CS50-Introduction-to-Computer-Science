from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

spaces = 2 * " "

for i in range(1, height + 1):
    alignmentSpaces = (height - i) * " "
    blocks = i * "#"
    print(f"{alignmentSpaces}{blocks}{spaces}{blocks}")
